#include "GBA2/gba2.h"

#include "JSystem/JUtility/JUTGba.h"
#include "dolphin/si.h"
#include "boot.h"
#include "_mem.h"

typedef struct mGcgba_work_s {
  /* 0x00 */ JUTGba* gba;
  /* 0x04 */ u8* buf_p;
  /* 0x08 */ int size;
  /* 0x0C */ int timer;
  /* 0x10 */ u32 cmd;
  /* 0x14 */ u32 cmd2;
  /* 0x18 */ u32 checksum;
  /* 0x1C */ u32 block_checksum;
  /* 0x20 */ u32 send_data;
  /* 0x24 */ u32 recv_data;
  /* 0x28 */ u8 state;
  /* 0x29 */ u8 step;
  /* 0x2A */ u8 busy;
  /* 0x2B */ s8 result;
  /* 0x2C */ u8 block_count;
} mGcgba_work_c;

#define JUTGBA_RESULT_BUSY -2

mGcgba_work_c g_Joy_wrk;
int g_port;

static u32 mJOYSIO_ConvData(u8* data) {
  u8 conv_buf[sizeof(u32)];

  conv_buf[0] = data[3];
  conv_buf[1] = data[2];
  conv_buf[2] = data[1];
  conv_buf[3] = data[0];

  return *(u32*)conv_buf;
}

extern "C" void mGcgba_Init() { }

extern "C" void mGcgba_Finish() {
  g_port = -1;
  g_Joy_wrk.busy = FALSE;
}

extern "C" void mGcgba_InitVar() {
  static JUTGba mGcgba_work_for_JUTGba;

  memset(&g_Joy_wrk, 0, sizeof(g_Joy_wrk));
  g_Joy_wrk.gba = JUTGba::getManager();
  if (g_Joy_wrk.gba == NULL) {
    memset(&mGcgba_work_for_JUTGba, 0, sizeof(mGcgba_work_for_JUTGba));
    SoftResetEnable = FALSE;
    g_Joy_wrk.gba = JUTGba::create(&mGcgba_work_for_JUTGba);
    SoftResetEnable = TRUE;
  }
}

extern "C" void mGcgba_EndComm() {
  g_port = -1;
}

extern "C" int mGcgba_ConnectEnabled() {
  int ret = GBA2_GBA_STATE_TRANSMITTING;
  int i;

  if (g_Joy_wrk.state == 0) {
    for (i = 0; i < GBA_MAX_CHAN; i++) {
      g_Joy_wrk.gba->doInitProbe(i, NULL, NULL);
    }

    g_port = -1;
    g_Joy_wrk.timer = 0;
    g_Joy_wrk.state++;
  }
  else {
    BOOL done = TRUE;

    g_port = -1;
    for (i = 0; i < GBA_MAX_CHAN; i++) {
      u32 type;
      s32 res = g_Joy_wrk.gba->resultInitProbe(i, &type);

      if (res == GBA_READY && type == SI_GBA && g_port == -1) {
        g_port = i;
      }

      if (res == JUTGBA_RESULT_BUSY) {
        done = FALSE;
      }
    }

    if (done && g_port != -1) {
      g_Joy_wrk.state = 0;
      ret = GBA2_GBA_STATE_SUCCESS;
    }

    if (ret == GBA2_GBA_STATE_TRANSMITTING && ++g_Joy_wrk.timer > GBA2_DEFAULT_TRIES) {
      ret = GBA2_GBA_STATE_ERROR;
      g_port = -1;
      g_Joy_wrk.state = 0;
    }
  }

  return ret;
}

extern "C" int mGcgba_Boot(u8* data_buf, size_t buf_size) {
  int ret = GBA2_GBA_STATE_TRANSMITTING;

  if (g_Joy_wrk.state == 0) {
    if (g_port > 0 && g_port < GBA_MAX_CHAN) {
      g_Joy_wrk.gba->doJoyBoot(g_port, 3, -1, data_buf, buf_size, NULL, NULL);
      g_Joy_wrk.timer = 0;
      g_Joy_wrk.state++;
    }
    else {
      ret = GBA2_GBA_STATE_ERROR;
    }
  }
  else {
    u8 status;
    s32 res = g_Joy_wrk.gba->resultJoyBoot(g_port, &status);

    if (res == GBA_READY) {
      g_Joy_wrk.state = 0;
      ret = GBA2_GBA_STATE_SUCCESS;
    }
    else if (res != JUTGBA_RESULT_BUSY) {
      g_Joy_wrk.state = 0;
      ret = GBA2_GBA_STATE_ERROR;
    }

    if (ret == GBA2_GBA_STATE_TRANSMITTING && ++g_Joy_wrk.timer > 1000) {
      g_Joy_wrk.state = 0;
      ret = GBA2_GBA_STATE_ERROR;
    }
  }

  return ret;
}

static void CallBack_Connection(JUTGbaParam* param, void* arg) {
  u8 status;

  if (g_Joy_wrk.busy == TRUE) {
    switch (g_Joy_wrk.step) {
      case 0:
        if (g_Joy_wrk.gba->resultReset(g_port, &status) == GBA_READY) {
          g_Joy_wrk.step++;
          g_Joy_wrk.recv_data = 0;
          g_Joy_wrk.gba->doRead(g_port, (u8*)&g_Joy_wrk.recv_data, &CallBack_Connection, arg);
          return;
        }
        break;
      case 1:
        if (g_Joy_wrk.gba->resultRead(g_port, &status) == GBA_READY) {
          if (g_Joy_wrk.recv_data == *(u32*)"gaej") {
            g_Joy_wrk.step++;
            g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)"GAEJ");
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Connection, arg);
          }
          else {
            g_Joy_wrk.step--;
            g_Joy_wrk.gba->doReset(g_port, &CallBack_Connection, arg);
          }
          return;
        }
        break;
      case 2:
        if (g_Joy_wrk.gba->resultWrite(g_port, &status) == GBA_READY) {
          g_Joy_wrk.result = 1;
          g_Joy_wrk.busy = FALSE;
          g_Joy_wrk.step = 0;
          return;
        }
        break;
    }
  }

  g_Joy_wrk.result = -1;
  g_Joy_wrk.busy = FALSE;
  g_Joy_wrk.step = 0;
}

static void CallBack_TypeCheck(JUTGbaParam* param, void* arg) {
  u8 status;
  u32 data;

  if (g_Joy_wrk.busy == TRUE) {
    switch (g_Joy_wrk.step) {
      case 0:
        if (g_Joy_wrk.gba->resultGetStatus(g_port, &status) == GBA_READY) {
          if ((status & GBA_JSTAT_RECV) == 0) {
            g_Joy_wrk.step++;
            data = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GC, 5);
            g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&data);
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_TypeCheck, arg);
          }
          else {
            g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_TypeCheck, arg);
          }
          return;
        }
        break;
      case 1:
        if (g_Joy_wrk.gba->resultWrite(g_port, &status) == GBA_READY) {
          g_Joy_wrk.step++;
          g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_TypeCheck, arg);
          return;
        }
        break;
      case 2:
        if (g_Joy_wrk.gba->resultGetStatus(g_port, &status) == GBA_READY) {
          if ((status & GBA_JSTAT_SEND) != 0) {
            g_Joy_wrk.step++;
            g_Joy_wrk.recv_data = 0;
            g_Joy_wrk.gba->doRead(g_port, (u8*)&g_Joy_wrk.recv_data, &CallBack_TypeCheck, arg);
          }
          else {
            g_Joy_wrk.step--;
            data = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GC, 5);
            g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&data);
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_TypeCheck, arg);
          }
          return;
        }
        break;
      case 3:
        if (g_Joy_wrk.gba->resultRead(g_port, &status) == GBA_READY) {
          data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv_data);
          if (data == g_Joy_wrk.cmd) {
            g_Joy_wrk.result = 1;
          }
          else if (data == g_Joy_wrk.cmd2) {
            g_Joy_wrk.result = 0;
          }
          else {
            break;
          }

          g_Joy_wrk.busy = FALSE;
          g_Joy_wrk.step = 0;
          return;
        }
        break;
    }
  }

  g_Joy_wrk.result = -1;
  g_Joy_wrk.busy = FALSE;
  g_Joy_wrk.step = 0;
}

extern "C" int mGcgba_IsEditor() {
  int ret = GBA2_GBA_STATE_TRANSMITTING;

  switch (g_Joy_wrk.state) {
    case 0:
      if (g_port > 0 && g_port < GBA_MAX_CHAN) {
        g_Joy_wrk.step = 0;
        g_Joy_wrk.busy = TRUE;
        g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
        g_Joy_wrk.timer = 0;
        g_Joy_wrk.state++;
        g_Joy_wrk.gba->doReset(g_port, &CallBack_Connection, NULL);
      }
      else {
        ret = GBA2_GBA_STATE_ERROR;
      }
      break;
    case 1:
      if (g_Joy_wrk.busy == FALSE) {
        if (g_Joy_wrk.result == 1) {
          g_Joy_wrk.cmd = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 6);
          g_Joy_wrk.cmd2 = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 11);
          g_Joy_wrk.step = 0;
          g_Joy_wrk.busy = TRUE;
          g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
          g_Joy_wrk.timer = 0;
          g_Joy_wrk.state++;
          g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_TypeCheck, NULL);
        }
        else {
          g_Joy_wrk.state = 0;
          ret = GBA2_GBA_STATE_ERROR;
        }
      }
      break;
    case 2:
      if (g_Joy_wrk.busy == FALSE) {
        ret = g_Joy_wrk.result;
        g_Joy_wrk.state = 0;
      }
      break;
  }

  if (ret == GBA2_GBA_STATE_TRANSMITTING && ++g_Joy_wrk.timer > 30) {
    ret = GBA2_GBA_STATE_ERROR;
    g_Joy_wrk.busy = FALSE;
    g_Joy_wrk.state = 0;
  }

  return ret;
}

extern "C" int mGcgba_IsGame() {
  int ret = GBA2_GBA_STATE_TRANSMITTING;

  switch (g_Joy_wrk.state) {
    case 0:
      if (g_port > 0 && g_port < GBA_MAX_CHAN) {
        g_Joy_wrk.step = 0;
        g_Joy_wrk.busy = TRUE;
        g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
        g_Joy_wrk.timer = 0;
        g_Joy_wrk.state++;
        g_Joy_wrk.gba->doReset(g_port, &CallBack_Connection, NULL);
      }
      else {
        ret = GBA2_GBA_STATE_ERROR;
      }
      break;
    case 1:
      if (g_Joy_wrk.busy == FALSE) {
        if (g_Joy_wrk.result == 1) {
          g_Joy_wrk.cmd = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 11);
          g_Joy_wrk.cmd2 = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 6);
          g_Joy_wrk.step = 0;
          g_Joy_wrk.busy = TRUE;
          g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
          g_Joy_wrk.timer = 0;
          g_Joy_wrk.state++;
          g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_TypeCheck, NULL);
        }
        else {
          g_Joy_wrk.state = 0;
          ret = GBA2_GBA_STATE_ERROR;
        }
      }
      break;
    case 2:
      if (g_Joy_wrk.busy == FALSE) {
        ret = g_Joy_wrk.result;
        g_Joy_wrk.state = 0;
      }
      break;
  }

  if (ret == GBA2_GBA_STATE_TRANSMITTING && ++g_Joy_wrk.timer > 30) {
    ret = GBA2_GBA_STATE_ERROR;
    g_Joy_wrk.busy = FALSE;
    g_Joy_wrk.state = 0;
  }

  return ret;
}

static void CallBack_Recv(JUTGbaParam* param, void* arg);

static void CallBack_CardScan(JUTGbaParam* param, void* arg) {
  u8 status;

  if (g_Joy_wrk.busy == TRUE) {
    switch (g_Joy_wrk.step) {
      case 0:
      case 3:
        if (g_Joy_wrk.gba->resultWrite(g_port, &status) == GBA_READY) {
          g_Joy_wrk.step++;
          g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_CardScan, arg);
          return;
        }
        break;
      case 1:
      case 4:
        if (g_Joy_wrk.gba->resultGetStatus(g_port, &status) == GBA_READY) {
          if ((status & GBA_JSTAT_SEND) != 0) {
            g_Joy_wrk.step++;
            g_Joy_wrk.recv_data = 0;
            g_Joy_wrk.gba->doRead(g_port, (u8*)&g_Joy_wrk.recv_data, &CallBack_CardScan, arg);
          }
          else {
            g_Joy_wrk.step--;
            g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.cmd);
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_CardScan, arg);
          }
          return;
        }
        break;
      case 2:
        if (g_Joy_wrk.gba->resultRead(g_port, &status) == GBA_READY) {
          u32 data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv_data);

          if (data == GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 8)) {
            g_Joy_wrk.step++;
            g_Joy_wrk.cmd = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GC, 9);
          }
          else if (data == GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 10)) {
            g_Joy_wrk.step = 0;
          }
          else {
            break;
          }

          g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.cmd);
          g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_CardScan, arg);
          return;
        }
        break;
      case 5:
        if (g_Joy_wrk.gba->resultRead(g_port, &status) == GBA_READY) {
          u32 data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv_data);

          if (data == GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 8)) {
            g_Joy_wrk.cmd = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GC, 10);
            g_Joy_wrk.step = 0;
            g_Joy_wrk.timer = -GBA2_READ_TRIES;
            g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.cmd);
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Recv, NULL);
            return;
          }
          else if (data == GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 10)) {
            g_Joy_wrk.step = 3;
            g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.cmd);
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_CardScan, arg);
            return;
          }
        }
        break;
    }
  }

  g_Joy_wrk.result = -1;
  g_Joy_wrk.busy = FALSE;
  g_Joy_wrk.step = 0;
}

static void CallBack_Recv(JUTGbaParam* param, void* arg) {
  u8 status;
  u32 data;

  if (g_Joy_wrk.busy == TRUE) {
    switch (g_Joy_wrk.step) {
      case 0:
      case 3:
      case 6:
        if (g_Joy_wrk.gba->resultWrite(g_port, &status) == GBA_READY) {
          g_Joy_wrk.step++;
          g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_Recv, arg);
          return;
        }
        break;
      case 1:
      case 4:
      case 7:
        if (g_Joy_wrk.gba->resultGetStatus(g_port, &status) == GBA_READY) {
          if ((status & GBA_JSTAT_SEND) != 0) {
            g_Joy_wrk.step++;
            g_Joy_wrk.recv_data = 0;
            g_Joy_wrk.gba->doRead(g_port, (u8*)&g_Joy_wrk.recv_data, &CallBack_Recv, arg);
          }
          else {
            g_Joy_wrk.step--;
            g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.cmd);
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Recv, arg);
          }
          return;
        }
        break;
      case 2:
        if (g_Joy_wrk.gba->resultRead(g_port, &status) == GBA_READY) {
          if (mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv_data) == GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 4)) {
            g_Joy_wrk.step++;
            g_Joy_wrk.checksum = 0;
            g_Joy_wrk.block_checksum = 0;
            g_Joy_wrk.block_count = 0;
          }
          else {
            g_Joy_wrk.step = 0;
          }

          g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.cmd);
          g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Recv, arg);
          return;
        }
        break;
      case 5:
        if (g_Joy_wrk.gba->resultRead(g_port, &status) == GBA_READY) {
          if (g_Joy_wrk.size <= 0) {
            g_Joy_wrk.step++;
            data = g_Joy_wrk.checksum + mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv_data) == 0xFFFFFFFF
                     ? GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GC, 6)
                     : GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GC, 7);
            g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&data);
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Recv, arg);
            return;
          }

          if (g_Joy_wrk.block_count == 0xFF) {
            if (g_Joy_wrk.block_checksum + mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv_data) != 0xFFFFFFFF) {
              break;
            }

            g_Joy_wrk.block_checksum = 0;
          }
          else {
            *(u32*)g_Joy_wrk.buf_p = g_Joy_wrk.recv_data;
            g_Joy_wrk.buf_p += sizeof(u32);
            g_Joy_wrk.size -= sizeof(u32);
            g_Joy_wrk.checksum += mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv_data);
            g_Joy_wrk.block_checksum += mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv_data);
          }

          g_Joy_wrk.block_count++;
          g_Joy_wrk.step--;
          g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_Recv, arg);
          return;
        }
        break;
      case 8:
        if (g_Joy_wrk.gba->resultRead(g_port, &status) == GBA_READY) {
          if (mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv_data) == GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 8)) {
            g_Joy_wrk.result = 1;
            g_Joy_wrk.busy = FALSE;
            g_Joy_wrk.step = 0;
            return;
          }

          if (mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv_data) != GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 9)) {
            g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_Recv, arg);
            return;
          }
        }
        break;
    }
  }

  g_Joy_wrk.result = -1;
  g_Joy_wrk.busy = FALSE;
  g_Joy_wrk.step = 0;
}

extern "C" int mGcgba_Recv(u8* recv_bufp, size_t recv_buf_size) {
  int ret = GBA2_GBA_STATE_TRANSMITTING;

  switch (g_Joy_wrk.state) {
    case 0:
      if (g_port > 0 && g_port < GBA_MAX_CHAN) {
        g_Joy_wrk.step = 0;
        g_Joy_wrk.busy = TRUE;
        g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
        g_Joy_wrk.timer = 0;
        g_Joy_wrk.state++;
        g_Joy_wrk.gba->doReset(g_port, &CallBack_Connection, NULL);
      }
      else {
        ret = GBA2_GBA_STATE_ERROR;
      }
      break;
    case 1:
      if (g_Joy_wrk.busy == FALSE) {
        if (g_Joy_wrk.result == 1) {
          g_Joy_wrk.buf_p = recv_bufp;
          g_Joy_wrk.size = recv_buf_size;
          g_Joy_wrk.cmd = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GC, 2);
          g_Joy_wrk.step = 0;
          g_Joy_wrk.busy = TRUE;
          g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
          g_Joy_wrk.timer = 0;
          g_Joy_wrk.state++;
          g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.cmd);
          g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Recv, NULL);
        }
        else {
          g_Joy_wrk.state = 0;
          ret = GBA2_GBA_STATE_ERROR;
        }
      }
      break;
    case 2:
      if (g_Joy_wrk.busy == FALSE) {
        ret = g_Joy_wrk.result;
        g_Joy_wrk.state = 0;
      }
      break;
  }

  if (ret == GBA2_GBA_STATE_TRANSMITTING && ++g_Joy_wrk.timer > GBA2_DEFAULT_TRIES) {
    ret = GBA2_GBA_STATE_ERROR;
    g_Joy_wrk.busy = FALSE;
    g_Joy_wrk.state = 0;
  }

  return ret;
}

extern "C" int mGcgba_Read(u8* read_buf, size_t read_buf_size, u8 prog_type) {
  int ret = GBA2_GBA_STATE_TRANSMITTING;

  switch (g_Joy_wrk.state) {
    case 0:
      if (g_port > 0 && g_port < GBA_MAX_CHAN) {
        g_Joy_wrk.step = 0;
        g_Joy_wrk.busy = TRUE;
        g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
        g_Joy_wrk.timer = 0;
        g_Joy_wrk.state++;
        g_Joy_wrk.gba->doReset(g_port, &CallBack_Connection, NULL);
      }
      else {
        ret = GBA2_GBA_STATE_ERROR;
      }
      break;
    case 1:
      if (g_Joy_wrk.busy == FALSE) {
        if (g_Joy_wrk.result == 1) {
          g_Joy_wrk.buf_p = read_buf;
          g_Joy_wrk.size = read_buf_size;

          switch (prog_type) {
            case GBA2_EAPPLI_TYPE_NEEDLEWORK:
              g_Joy_wrk.cmd = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GC, 8);
              break;
            case GBA2_EAPPLI_TYPE_MUSICSCORE:
              g_Joy_wrk.cmd = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GC, 11);
              break;
            case GBA2_EAPPLI_TYPE_PTERMINAL:
              g_Joy_wrk.cmd = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GC, 12);
              break;
            default:
              g_Joy_wrk.cmd = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GC, 13);
              break;
          }

          g_Joy_wrk.step = 0;
          g_Joy_wrk.busy = TRUE;
          g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
          g_Joy_wrk.timer = -GBA2_READ_TRIES;
          g_Joy_wrk.state++;
          g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.cmd);
          g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_CardScan, NULL);
        }
        else {
          g_Joy_wrk.state = 0;
          ret = GBA2_GBA_STATE_ERROR;
        }
      }
      break;
    case 2:
      if (g_Joy_wrk.busy == FALSE) {
        ret = g_Joy_wrk.result;
        g_Joy_wrk.state = 0;
      }
      break;
  }

  if (ret == GBA2_GBA_STATE_TRANSMITTING && ++g_Joy_wrk.timer > GBA2_DEFAULT_TRIES) {
    ret = GBA2_GBA_STATE_ERROR;
    g_Joy_wrk.busy = FALSE;
    g_Joy_wrk.state = 0;
  }

  return ret;
}

static void CallBack_Send(JUTGbaParam* param, void* arg) {
  u8 status;
  u32 data;

  if (g_Joy_wrk.busy == TRUE) {
    switch (g_Joy_wrk.step) {
      case 0:
      case 10:
        if (g_Joy_wrk.gba->resultWrite(g_port, &status) == GBA_READY) {
          g_Joy_wrk.step++;
          g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_Send, arg);
          return;
        }
        break;
      case 1:
        if (g_Joy_wrk.gba->resultGetStatus(g_port, &status) == GBA_READY) {
          if ((status & GBA_JSTAT_SEND) != 0) {
            g_Joy_wrk.step++;
            g_Joy_wrk.recv_data = 0;
            g_Joy_wrk.gba->doRead(g_port, (u8*)&g_Joy_wrk.recv_data, &CallBack_Send, arg);
          }
          else {
            g_Joy_wrk.step--;
            data = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 2);
            g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&data);
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Send, arg);
          }
          return;
        }
        break;
      case 2:
        if (g_Joy_wrk.gba->resultRead(g_port, &status) == GBA_READY) {
          if (mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv_data) == GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GC, 4)) {
            g_Joy_wrk.step += 2;
            g_Joy_wrk.checksum = 0;
            g_Joy_wrk.block_checksum = 0;
            g_Joy_wrk.block_count = 0;
            g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_Send, arg);
          }
          else {
            g_Joy_wrk.step = 0;
            data = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 2);
            g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&data);
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Send, arg);
          }
          return;
        }
        break;
      case 3:
      case 5:
      case 7:
      case 13:
      case 15:
      case 17:
      case 19:
        if (g_Joy_wrk.gba->resultWrite(g_port, &status) == GBA_READY) {
          g_Joy_wrk.step++;
          g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_Send, arg);
          return;
        }
        break;
      case 4:
      case 16:
        if (g_Joy_wrk.gba->resultGetStatus(g_port, &status) == GBA_READY) {
          if ((status & GBA_JSTAT_RECV) == 0) {
            if (g_Joy_wrk.size <= 0) {
              g_Joy_wrk.step++;
              g_Joy_wrk.send_data = ~g_Joy_wrk.checksum;
            }
            else if (g_Joy_wrk.block_count == 0xFF) {
              g_Joy_wrk.step--;
              g_Joy_wrk.send_data = ~g_Joy_wrk.block_checksum;
              g_Joy_wrk.block_checksum = 0;
              g_Joy_wrk.block_count++;
            }
            else {
              g_Joy_wrk.step--;
              g_Joy_wrk.send_data = *(u32*)g_Joy_wrk.buf_p;
              g_Joy_wrk.buf_p += sizeof(u32);
              g_Joy_wrk.size -= sizeof(u32);
              g_Joy_wrk.checksum += g_Joy_wrk.send_data;
              g_Joy_wrk.block_checksum += g_Joy_wrk.send_data;
              g_Joy_wrk.block_count++;
            }

            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Send, arg);
          }
          else {
            g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_Send, arg);
          }
          return;
        }
        break;
      case 6:
      case 18:
        if (g_Joy_wrk.gba->resultGetStatus(g_port, &status) == GBA_READY) {
          if ((status & GBA_JSTAT_RECV) == 0) {
            g_Joy_wrk.step++;
            data = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 2);
            g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&data);
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Send, arg);
          }
          return;
        }
        break;
      case 8:
      case 20:
        if (g_Joy_wrk.gba->resultGetStatus(g_port, &status) == GBA_READY) {
          if ((status & GBA_JSTAT_SEND) != 0) {
            g_Joy_wrk.step++;
            g_Joy_wrk.recv_data = 0;
            g_Joy_wrk.gba->doRead(g_port, (u8*)&g_Joy_wrk.recv_data, &CallBack_Send, arg);
          }
          else {
            g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_Send, arg);
          }
          return;
        }
        break;
      case 9:
      case 21:
        if (g_Joy_wrk.gba->resultRead(g_port, &status) == GBA_READY) {
          if (mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv_data) == GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 8)) {
            g_Joy_wrk.result = 1;
            g_Joy_wrk.busy = FALSE;
            g_Joy_wrk.step = 0;
            return;
          }
        }
        break;
      case 11:
        if (g_Joy_wrk.gba->resultGetStatus(g_port, &status) == GBA_READY) {
          if ((status & GBA_JSTAT_SEND) != 0) {
            g_Joy_wrk.step++;
            g_Joy_wrk.recv_data = 0;
            g_Joy_wrk.gba->doRead(g_port, (u8*)&g_Joy_wrk.recv_data, &CallBack_Send, arg);
          }
          else {
            g_Joy_wrk.step--;
            data = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 12);
            g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&data);
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Send, arg);
          }
          return;
        }
        break;
      case 12:
        if (g_Joy_wrk.gba->resultRead(g_port, &status) == GBA_READY) {
          if (mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv_data) == GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GC, 4)) {
            g_Joy_wrk.step += 2;
            g_Joy_wrk.checksum = 0;
            g_Joy_wrk.block_checksum = 0;
            g_Joy_wrk.block_count = 0;
            g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_Send, arg);
          }
          else {
            g_Joy_wrk.step = 10;
            data = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 12);
            g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&data);
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Send, arg);
          }
          return;
        }
        break;
      case 14:
        if (g_Joy_wrk.gba->resultGetStatus(g_port, &status) == GBA_READY) {
          if ((status & GBA_JSTAT_RECV) == 0) {
            g_Joy_wrk.step++;
            g_Joy_wrk.send_data = g_Joy_wrk.cmd;
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Send, arg);
          }
          else {
            g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_Send, arg);
          }
          return;
        }
        break;
    }
  }

  g_Joy_wrk.result = -1;
  g_Joy_wrk.busy = FALSE;
  g_Joy_wrk.step = 0;
}

extern "C" int mGcgba_Send(u8* send_bufp, size_t send_buf_size) {
  int ret = GBA2_GBA_STATE_TRANSMITTING;
  u32 data;

  switch (g_Joy_wrk.state) {
    case 0:
      if (g_port > 0 && g_port < GBA_MAX_CHAN) {
        g_Joy_wrk.step = 0;
        g_Joy_wrk.busy = TRUE;
        g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
        g_Joy_wrk.timer = 0;
        g_Joy_wrk.state++;
        g_Joy_wrk.gba->doReset(g_port, &CallBack_Connection, NULL);
      }
      else {
        ret = GBA2_GBA_STATE_ERROR;
      }
      break;
    case 1:
      if (g_Joy_wrk.busy == FALSE) {
        if (g_Joy_wrk.result == 1) {
          g_Joy_wrk.buf_p = send_bufp;
          g_Joy_wrk.size = send_buf_size;
          g_Joy_wrk.step = 0;
          g_Joy_wrk.busy = TRUE;
          g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
          g_Joy_wrk.timer = -GBA2_READ_TRIES;
          g_Joy_wrk.state++;
          data = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 2);
          g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&data);
          g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Send, NULL);
        }
        else {
          g_Joy_wrk.state = 0;
          ret = GBA2_GBA_STATE_ERROR;
        }
      }
      break;
    case 2:
      if (g_Joy_wrk.busy == FALSE) {
        ret = g_Joy_wrk.result;
        g_Joy_wrk.state = 0;
      }
      break;
  }

  if (ret == GBA2_GBA_STATE_TRANSMITTING && ++g_Joy_wrk.timer > GBA2_DEFAULT_TRIES) {
    ret = GBA2_GBA_STATE_ERROR;
    g_Joy_wrk.busy = FALSE;
    g_Joy_wrk.state = 0;
  }

  return ret;
}

extern "C" int mGcgba_SendGame(u8* send_bufp, size_t send_buf_size, u8 game_type) {
  int ret = GBA2_GBA_STATE_TRANSMITTING;
  static int test = 0;
  u32 data;

  if (++test < 20) {
    return GBA2_GBA_STATE_TRANSMITTING;
  }

  switch (g_Joy_wrk.state) {
    case 0:
      if (g_port > 0 && g_port < GBA_MAX_CHAN) {
        g_Joy_wrk.step = 0;
        g_Joy_wrk.busy = TRUE;
        g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
        g_Joy_wrk.timer = 0;
        g_Joy_wrk.state++;
        g_Joy_wrk.gba->doReset(g_port, &CallBack_Connection, NULL);
      }
      else {
        ret = GBA2_GBA_STATE_ERROR;
      }
      break;
    case 1:
      if (g_Joy_wrk.busy == FALSE) {
        if (g_Joy_wrk.result == 1) {
          g_Joy_wrk.buf_p = send_bufp;
          g_Joy_wrk.size = send_buf_size;
          g_Joy_wrk.cmd = game_type;
          g_Joy_wrk.step = 10;
          g_Joy_wrk.busy = TRUE;
          g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
          g_Joy_wrk.timer = -GBA2_READ_TRIES;
          g_Joy_wrk.state++;
          data = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 12);
          g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&data);
          g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_Send, NULL);
        }
        else {
          g_Joy_wrk.state = 0;
          ret = GBA2_GBA_STATE_ERROR;
        }
      }
      break;
    case 2:
      if (g_Joy_wrk.busy == FALSE) {
        ret = g_Joy_wrk.result;
        g_Joy_wrk.state = 0;
      }
      break;
  }

  if (ret == GBA2_GBA_STATE_TRANSMITTING) {
    if (++g_Joy_wrk.timer > GBA2_READ_TRIES) {
      ret = GBA2_GBA_STATE_ERROR;
      g_Joy_wrk.busy = FALSE;
      g_Joy_wrk.state = 0;
    }
  }
  else {
    test = 0;
  }

  return ret;
}

static void CallBack_SendEAppri(JUTGbaParam* param, void* arg) {
  u8 status;

  if (g_Joy_wrk.busy == TRUE) {
    switch (g_Joy_wrk.step) {
      case 0:
        if (g_Joy_wrk.gba->resultReset(g_port, &status) == GBA_READY) {
          if ((status & GBA_JSTAT_SEND) != 0 && (status & GBA_JSTAT_PSF1) != 0) {
            g_Joy_wrk.step++;
            g_Joy_wrk.recv_data = 0;
            g_Joy_wrk.gba->doRead(g_port, (u8*)&g_Joy_wrk.recv_data, &CallBack_SendEAppri, arg);
          }
          else {
            g_Joy_wrk.gba->doReset(g_port, &CallBack_SendEAppri, arg);
          }
          return;
        }
        break;
      case 1:
        if (g_Joy_wrk.gba->resultRead(g_port, &status) == GBA_READY) {
          if (g_Joy_wrk.recv_data == *(u32*)"PSAJ") {
            g_Joy_wrk.step++;
            g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_SendEAppri, arg);
          }
          else {
            g_Joy_wrk.step--;
            g_Joy_wrk.gba->doReset(g_port, &CallBack_SendEAppri, arg);
          }
          return;
        }
        break;
      case 2:
        if (g_Joy_wrk.gba->resultGetStatus(g_port, &status) == GBA_READY) {
          if (status == GBA_JSTAT_PSF1) {
            g_Joy_wrk.step++;
            g_Joy_wrk.send_data = *(u32*)"PSAJ";
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_SendEAppri, arg);
          }
          else {
            g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_SendEAppri, arg);
          }
          return;
        }
        break;
      case 3:
      case 5:
        if (g_Joy_wrk.gba->resultWrite(g_port, &status) == GBA_READY) {
          g_Joy_wrk.step++;
          g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_SendEAppri, arg);
          return;
        }
        break;
      case 4:
        if (g_Joy_wrk.gba->resultGetStatus(g_port, &status) == GBA_READY) {
          if (status == (GBA_JSTAT_PSF1 | GBA_JSTAT_PSF0)) {
            g_Joy_wrk.step++;
            g_Joy_wrk.send_data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.size);
            g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_SendEAppri, arg);
          }
          else {
            g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_SendEAppri, arg);
          }
          return;
        }
        break;
      case 6:
        if (g_Joy_wrk.gba->resultGetStatus(g_port, &status) == GBA_READY) {
          if ((status & GBA_JSTAT_SEND) != 0) {
            g_Joy_wrk.step++;
            g_Joy_wrk.recv_data = 0;
            g_Joy_wrk.gba->doRead(g_port, (u8*)&g_Joy_wrk.recv_data, &CallBack_SendEAppri, arg);
          }
          else {
            g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_SendEAppri, arg);
          }
          return;
        }
        break;
      case 7:
        if (g_Joy_wrk.gba->resultRead(g_port, &status) == GBA_READY) {
          if (g_Joy_wrk.size == mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv_data)) {
            g_Joy_wrk.step++;
          }
          else {
            g_Joy_wrk.step--;
          }

          g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_SendEAppri, arg);
          return;
        }
        break;
      case 8:
        if (g_Joy_wrk.gba->resultGetStatus(g_port, &status) == GBA_READY) {
          if ((status & GBA_JSTAT_PSF0) != 0 && (status & GBA_JSTAT_PSF1) != 0) {
            if ((status & GBA_JSTAT_RECV) == 0) {
              g_Joy_wrk.timer = 0;
              g_Joy_wrk.step++;
              g_Joy_wrk.send_data = *(u32*)g_Joy_wrk.buf_p;
              g_Joy_wrk.buf_p += sizeof(u32);
              g_Joy_wrk.size -= sizeof(u32);
              g_Joy_wrk.gba->doWrite(g_port, (u8*)&g_Joy_wrk.send_data, &CallBack_SendEAppri, arg);
            }
            else {
              g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_SendEAppri, arg);
            }
            return;
          }
        }
        break;
      case 9:
        if (g_Joy_wrk.gba->resultWrite(g_port, &status) == GBA_READY) {
          if (g_Joy_wrk.size <= 0) {
            g_Joy_wrk.result = 1;
            g_Joy_wrk.busy = FALSE;
            g_Joy_wrk.step = 0;
          }
          else {
            g_Joy_wrk.step--;
            g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_SendEAppri, arg);
          }
          return;
        }
        break;
    }
  }

  g_Joy_wrk.result = -1;
  g_Joy_wrk.busy = FALSE;
  g_Joy_wrk.step = 0;
}

extern "C" int mGcgba_send_eAppri(u8* eappli_p, size_t eappli_size) {
  int ret = GBA2_EAPPLI_TRANSMITTING;

  switch (g_Joy_wrk.state) {
    case 0:
      if (g_port > 0 && g_port < GBA_MAX_CHAN) {
        g_Joy_wrk.buf_p = eappli_p;
        g_Joy_wrk.size = eappli_size;
        g_Joy_wrk.step = 0;
        g_Joy_wrk.busy = TRUE;
        g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
        g_Joy_wrk.timer = 0;
        g_Joy_wrk.state++;
        g_Joy_wrk.gba->doReset(g_port, &CallBack_SendEAppri, NULL);
      }
      else {
        ret = GBA2_EAPPLI_FAILURE_NO_GBA;
      }
      break;
    case 1:
      if (g_Joy_wrk.busy == FALSE) {
        if (g_Joy_wrk.result == 1) {
          g_Joy_wrk.state++;
        }
        else {
          g_Joy_wrk.state = 0;
          ret = GBA2_EAPPLI_FAILURE_NO_GBA;
        }
      }
      break;
    case 2:
      g_Joy_wrk.step = 0;
      g_Joy_wrk.busy = TRUE;
      g_Joy_wrk.result = -1;
      g_Joy_wrk.timer = -GBA2_READ_TRIES;
      g_Joy_wrk.state++;
      g_Joy_wrk.gba->doReset(g_port, &CallBack_Connection, NULL);
      break;
    case 3:
      if (g_Joy_wrk.busy == FALSE) {
        if (g_Joy_wrk.result == 1) {
          g_Joy_wrk.cmd = GBA2_MAKE_ACKNOWLEDGE_CODE(GBA2_DEVICE_GBA, 10);
          g_Joy_wrk.step = 0;
          g_Joy_wrk.busy = TRUE;
          g_Joy_wrk.result = -1;
          g_Joy_wrk.timer = 0;
          g_Joy_wrk.state++;
          g_Joy_wrk.gba->doGetStatus(g_port, &CallBack_TypeCheck, NULL);
        }
        else {
          g_Joy_wrk.state = 0;
          ret = GBA2_EAPPLI_FAILURE_NO_GBA;
        }
      }
      break;
    case 4:
      if (g_Joy_wrk.busy == FALSE) {
        g_Joy_wrk.state = 0;
        if (g_Joy_wrk.result == 1) {
          ret = GBA2_EAPPLI_SUCCESS;
        }
        else {
          ret = GBA2_EAPPLI_FAILURE_NO_GBA;
        }
      }
      break;
  }

  if (ret == GBA2_EAPPLI_TRANSMITTING && ++g_Joy_wrk.timer > GBA2_DEFAULT_TRIES) {
    ret = GBA2_EAPPLI_FAILURE_NO_GBA;
    g_Joy_wrk.busy = FALSE;
    g_Joy_wrk.state = 0;
  }

  return ret;
}
