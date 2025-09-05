#ifndef FS_H
#define FS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JSystem/JUtility/fs_cardrst.h"
#include "JSystem/JUtility/fs_chdr.h"
#include "JSystem/JUtility/fs_cldr.h"
#include "JSystem/JUtility/fs_close.h"
#include "JSystem/JUtility/fs_dele.h"
#include "JSystem/JUtility/fs_drv.h"
#include "JSystem/JUtility/fs_drvsel.h"
#include "JSystem/JUtility/fs_form.h"
#include "JSystem/JUtility/fs_getps.h"
#include "JSystem/JUtility/fs_init.h"
#include "JSystem/JUtility/fs_mkdr.h"
#include "JSystem/JUtility/fs_mount.h"
#include "JSystem/JUtility/fs_opdr.h"
#include "JSystem/JUtility/fs_open.h"
#include "JSystem/JUtility/fs_rddr.h"
#include "JSystem/JUtility/fs_read.h"
#include "JSystem/JUtility/fs_renm.h"
#include "JSystem/JUtility/fs_seek.h"
#include "JSystem/JUtility/fs_subd.h"
#include "JSystem/JUtility/fs_sync.h"
#include "JSystem/JUtility/fs_umount.h"
#include "JSystem/JUtility/fs_write.h"

extern unsigned char FS_drv_ctl[0x4BC90];

#ifdef __cplusplus
};
#endif

#endif
