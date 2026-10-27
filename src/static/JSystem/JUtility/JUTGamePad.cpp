#include "JSystem/JUtility/JUTGamePad.h"

#include <dolphin/pad.h>
#include "MSL_C/w_math.h"
#include "MSL_C/math.h"

extern "C" void PADClampCircle(PADStatus* status);

inline int __fpclassifyf(f32 x) {
    switch ((*(s32*)&x) & 0x7F800000) {
        case 0x7F800000: {
            if ((*(s32*)&x) & 0x007FFFFF)
                return FP_QNAN;
            else
                return FP_INFINITE;
            break;
        }
        case 0: {
            if ((*(s32*)&x) & 0x007FFFFF)
                return FP_SUBNORMAL;
            else
                return FP_ZERO;
            break;
        }
    }
    return FP_NORMAL;
}

namespace std {
inline float sqrtf(float x) {
    const double _half = .5;
    const double _three = 3.0;

    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        return (float)(x * guess);
    } else if (x < 0.0) {
        return NAN;
    } else if (isnan(x)) {
        return NAN;
    }

    return x;
}
} // namespace std

u32 JUTGamePad::CRumble::sChannelMask[PAD_MAX_CONTROLLERS] = {
    0x80000000 >> 0,
    0x80000000 >> 1,
    0x80000000 >> 2,
    0x80000000 >> 3,
};

static u32 channel_mask[PAD_MAX_CONTROLLERS] = {
    0x80000000 >> 0,
    0x80000000 >> 1,
    0x80000000 >> 2,
    0x80000000 >> 3,
};

JUTGamePad::EStickMode JUTGamePad::sStickMode = Clamped;
JUTGamePad::EClampMode JUTGamePad::sClampMode = Clamp;
f32 JUTGamePad::CStick::sPressPoint = 0.5f;
f32 JUTGamePad::CStick::sReleasePoint = 0.25f;
u32 JUTGamePad::C3ButtonReset::sResetPattern = START | X | B;
u32 JUTGamePad::C3ButtonReset::sResetMaskPattern = 0xFFFF;

JSUList<JUTGamePad> JUTGamePad::mPadList(false);
PADStatus JUTGamePad::mPadStatus[PAD_MAX_CONTROLLERS];
JUTGamePad::CButton JUTGamePad::mPadButton[PAD_MAX_CONTROLLERS];
JUTGamePad::CStick JUTGamePad::mPadMStick[PAD_MAX_CONTROLLERS];
JUTGamePad::CStick JUTGamePad::mPadSStick[PAD_MAX_CONTROLLERS];

bool JUTGamePad::mListInitialized = false;
u8 JUTGamePad::mPadAssign[PAD_MAX_CONTROLLERS];
u32 JUTGamePad::sSuppressPadReset = 0;
u32 JUTGamePad::sAnalogMode = 0;
u32 JUTGamePad::sRumbleSupported = 0;
u8 JUTGamePad::CRumble::mStatus[PAD_MAX_CONTROLLERS];
u32 JUTGamePad::CRumble::mEnabled = 0;
JUTResetBtnCb JUTGamePad::C3ButtonReset::sCallback = nullptr;
void* JUTGamePad::C3ButtonReset::sCallbackArg = nullptr;
OSTime JUTGamePad::C3ButtonReset::sThreshold = (OSTime)(OS_TIMER_CLOCK / 60) * 30;
bool JUTGamePad::C3ButtonReset::sResetSwitchPushing = false;
bool JUTGamePad::C3ButtonReset::sResetOccurred = false;
s32 JUTGamePad::C3ButtonReset::sResetOccurredPort = 0;

JUTGamePad::JUTGamePad(EPadPort port)
    : mButtons(), mMainStick(), mSubStick(), mRumble(this), mLink(this), mButtonReset() {
    mPortNum = port;
    if (mPortNum >= 0) {
        mPadAssign[port]++;
    }
    initList();
    JUTGamePad::mPadList.append(&mLink);
    update();
    mPadRecord = nullptr;
    mPadReplay = nullptr;
    clear();
}

JUTGamePad::JUTGamePad() : mButtons(), mMainStick(), mSubStick(), mRumble(this), mLink(this), mButtonReset() {
    mPortNum = -1;
    initList();
    JUTGamePad::mPadList.append(&mLink);
    mPadRecord = nullptr;
    mPadReplay = nullptr;
    clear();
}

JUTGamePad::~JUTGamePad() {
    if (mPortNum >= 0) {
        mPadAssign[mPortNum]--;
        mPortNum = -1;
    }

    JUTGamePad::mPadList.remove(&mLink);
}

void JUTGamePad::initList() {
    if (!JUTGamePad::mListInitialized) {
        JUTGamePad::mPadList.initiate();
        JUTGamePad::mListInitialized = true;
    }
}

void JUTGamePad::init() {
    PADSetSpec(5);
    JUTGamePad::sAnalogMode = 3;
    PADSetAnalogMode(3);
    PADInit();
}

void JUTGamePad::clear() {
    mButtonReset.mReset = false;
    mResetEnabled = true;
}

u32 JUTGamePad::read() {
    sRumbleSupported = PADRead(mPadStatus);

    switch (sClampMode) {
        case Clamp:
            PADClamp(mPadStatus);
            break;
        case ClampCircle:
            PADClampCircle(mPadStatus);
            break;
    }

    u32 mask;
    u32 resetControllerMask = 0;

    for (int i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        mask = 0x80000000 >> i;

        if (mPadStatus[i].err == PAD_ERR_NONE) {
            PADStatus* status = &mPadStatus[i];
            u32 buttons;

            buttons = mPadMStick[i].update(status->stickX, status->stickY, sStickMode, WhichStick_MainStick,
                                           mPadButton[i].mButton)
                      << 24;
            buttons |= mPadSStick[i].update(status->substickX, status->substickY, sStickMode, WhichStick_SubStick,
                                            mPadButton[i].mButton)
                       << 16;
            mPadButton[i].update(status, buttons);
        } else if (mPadStatus[i].err == PAD_ERR_NO_CONTROLLER) {
            mPadMStick[i].update(0, 0, sStickMode, WhichStick_MainStick, 0);
            mPadSStick[i].update(0, 0, sStickMode, WhichStick_SubStick, 0);
            mPadButton[i].update(nullptr, 0);

            if ((sSuppressPadReset & mask) == 0) {
                resetControllerMask |= mask;
            }
        } else {
            mPadButton[i].mTrigger = 0;
            mPadButton[i].mRelease = 0;
            mPadButton[i].mRepeat = 0;
        }
    }

    JSUListIterator<JUTGamePad> it;
    for (it = mPadList.getFirst(); it != mPadList.getEnd(); ++it) {
        if (it->getPadReplay() != nullptr && it->getPadReplay()->isActive()) {
            PADStatus status;
            u32 buttons;

            it->getPadReplay()->read(&status);
            buttons = it->mMainStick.update(status.stickX, status.stickY, sStickMode, WhichStick_MainStick,
                                            it->mButtons.mButton)
                      << 24;
            buttons |= it->mSubStick.update(status.substickX, status.substickY, sStickMode, WhichStick_SubStick,
                                            it->mButtons.mButton)
                       << 16;
            it->mButtons.update(&status, buttons);
        } else {
            if (it->mPortNum == -1) {
                it->assign();
            }

            it->update();
        }

        if (it->getPadRecord() != nullptr && it->getPadRecord()->isActive()) {
            if (it->mPortNum >= 0) {
                int port = it->mPortNum;
                if (mPadStatus[port].err == PAD_ERR_NONE) {
                    it->getPadRecord()->write(&mPadStatus[port]);
                }
            }
        }
    }

    if (resetControllerMask != 0) {
        PADReset(resetControllerMask);
    }

    checkResetSwitch();
    return sRumbleSupported;
}

void JUTGamePad::assign() {
    for (s32 i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        if (JUTGamePad::mPadStatus[i].err == PAD_ERR_NONE && JUTGamePad::mPadAssign[i] == 0) {
            mPortNum = i;
            JUTGamePad::mPadAssign[i] = 1;
            JUTGamePad::mPadButton[i].setRepeat(mButtons.mRepeatMask, mButtons.mRepeatDelay, mButtons.mRepeatFrequency);
            mRumble.clear(this);
            break;
        }
    }
}

void JUTGamePad::checkResetCallback(OSTime time) {
    if (time >= JUTGamePad::C3ButtonReset::sThreshold) {
        JUTGamePad::C3ButtonReset::sResetOccurred = true;
        JUTGamePad::C3ButtonReset::sResetOccurredPort = mPortNum;

        if (JUTGamePad::C3ButtonReset::sCallback != nullptr) {
            (*JUTGamePad::C3ButtonReset::sCallback)(mPortNum, JUTGamePad::C3ButtonReset::sCallbackArg);
        }
    }
}

void JUTGamePad::update() {
    if (mPortNum != -1) {
        if (mPortNum >= 0 && mPortNum < PAD_MAX_CONTROLLERS) {
            mButtons = JUTGamePad::mPadButton[mPortNum];
            mMainStick = JUTGamePad::mPadMStick[mPortNum];
            mSubStick = JUTGamePad::mPadSStick[mPortNum];
            mErrorStatus = JUTGamePad::mPadStatus[mPortNum].err;
        }

        if (!mResetEnabled || JUTGamePad::C3ButtonReset::sResetPattern !=
                                  (mButtons.mButton & JUTGamePad::C3ButtonReset::sResetMaskPattern)) {
            mButtonReset.mReset = false;
        } else if (JUTGamePad::C3ButtonReset::sResetOccurred == false) {
            if (mButtonReset.mReset == true) {
                checkResetCallback(OSGetTime() - mResetTime);
            } else {
                mButtonReset.mReset = true;
                mResetTime = OSGetTime();
            }
        }

        JSUListIterator<JUTGamePadLongPress> pad = JUTGamePadLongPress::sPatternList.getFirst();
        for (; pad != JUTGamePadLongPress::sPatternList.getEnd(); ++pad) {
            if (pad->isValid()) {
                if (mPortNum >= 0 && mPortNum < PAD_MAX_CONTROLLERS) {
                    if ((mButtons.mButton & pad->getMaskPattern()) == pad->getPattern()) {
                        if (pad->_20[mPortNum] == true) {
                            s64 diff = OSGetTime() - pad->mTimer[mPortNum];
                            pad->checkCallback(mPortNum, diff);
                            continue;
                        }

                        pad->_20[mPortNum] = true;
                        pad->mTimer[mPortNum] = OSGetTime();
                        continue;
                    }

                    pad->_20[mPortNum] = false;
                }
            }
        }

        if (mPortNum >= 0 && mPortNum < PAD_MAX_CONTROLLERS) {
            mRumble.update(mPortNum);
        }
    }
}

void JUTGamePad::checkResetSwitch() {
    if (!JUTGamePad::C3ButtonReset::sResetOccurred) {
        if (OSGetResetSwitchState() != 0) {
            JUTGamePad::C3ButtonReset::sResetSwitchPushing = true;
        } else {
            if (JUTGamePad::C3ButtonReset::sResetSwitchPushing == true) {
                JUTGamePad::C3ButtonReset::sResetOccurred = true;
                JUTGamePad::C3ButtonReset::sResetOccurredPort = -1;

                if (*JUTGamePad::C3ButtonReset::sCallback != nullptr) {
                    (*JUTGamePad::C3ButtonReset::sCallback)(-1, JUTGamePad::C3ButtonReset::sCallbackArg);
                }
            }

            JUTGamePad::C3ButtonReset::sResetSwitchPushing = false;
        }
    }
}

void JUTGamePad::CButton::clear() {
    mButton = 0;
    mTrigger = 0;
    mRelease = 0;
    mRepeat = 0;
    mAnalogA = 0;
    mAnalogB = 0;
    mAnalogL = 0;
    mAnalogR = 0;
    mRepeatTimer = 0;
    mRepeatLastButton = 0;
    mRepeatMask = 0;
    mRepeatDelay = 0;
    mRepeatFrequency = 0;
}

void JUTGamePad::CButton::update(const PADStatus* padStatus, u32 stick_buttons) {
    u32 tempButtons;
    u32 buttons;

    if (padStatus != nullptr) {
        tempButtons = padStatus->button;
    } else {
        tempButtons = 0;
    }

    buttons = stick_buttons | tempButtons;
    mRepeat = 0;

    if (mRepeatDelay != 0) {
        if (mRepeatMask != 0) {
            u32 repeatButtons = buttons & mRepeatMask;
            mRepeat = 0;

            if (repeatButtons == 0) {
                mRepeatLastButton = 0;
                mRepeatTimer = 0;
            } else if (mRepeatLastButton == repeatButtons) {
                mRepeatTimer++;
                if (mRepeatTimer == mRepeatDelay ||
                    (mRepeatTimer > mRepeatDelay && ((mRepeatTimer - mRepeatDelay) % mRepeatFrequency) == 0)) {
                    mRepeat = repeatButtons;
                }
            } else {
                mRepeat = repeatButtons & (mRepeatLastButton ^ 0xFFFFFFFF);
                mRepeatLastButton = repeatButtons;
                mRepeatTimer = 0;
            }
        }
    }

    mTrigger = buttons & (buttons ^ mButton);
    mRelease = mButton & (buttons ^ mButton);
    mButton = buttons;
    mRepeat |= (mRepeatMask ^ 0xFFFFFFFF) & mTrigger;

    if (padStatus != nullptr) {
        mAnalogA = padStatus->analogA;
        mAnalogB = padStatus->analogB;
        mAnalogL = padStatus->triggerLeft;
        mAnalogR = padStatus->triggerRight;
    } else {
        mAnalogA = 0;
        mAnalogB = 0;
        mAnalogL = 0;
        mAnalogR = 0;
    }

    mAnalogLf = (f32)(int)mAnalogL / 150.0f;
    mAnalogRf = (f32)(int)mAnalogR / 150.0f;
}

void JUTGamePad::CStick::clear() {
    mX = 0.0f;
    mY = 0.0f;
    mValue = 0.0f;
    mAngle = 0;
}

u32 JUTGamePad::CStick::update(s8 x, s8 y, EStickMode stickMode, EWhichStick whichStick, u32 mask) {
    s32 clamp;
    switch (getClampMode()) {
        case Clamp:
            clamp = whichStick == WhichStick_MainStick ? 54 : 42;
            break;
        case ClampCircle:
            clamp = whichStick == WhichStick_MainStick ? 38 : 29;
            break;
        default:
            clamp = whichStick == WhichStick_MainStick ? 69 : 57;
            break;
    }

    mAnalogX = x;
    mAnalogY = y;
    mX = (f32)x / clamp;
    mY = (f32)y / clamp;
    mValue = std::sqrtf(mX * mX + mY * mY);

    if (mValue > 1.0f) {
        if (stickMode == Clamped) {
            mX /= mValue;
            mY /= mValue;
        }

        mValue = 1.0f;
    }

    if (mValue > 0.0f) {
        if (mY == 0.0f) {
            if (mX > 0.0f) {
                mAngle = 0x4000;
            } else {
                mAngle = -0x4000;
            }
        } else {
            f32 angle = atan2(mX, -mY);
            mAngle = angle * 10430.379f; //((f32)0x8000 / F_PI);
        }
    }

    return getButton(mask >> (whichStick == WhichStick_MainStick ? 24 : 16));
}

u32 JUTGamePad::CStick::getButton(u32 mask) {
    u32 button = mask & 0xF;

    if (-sReleasePoint < mX && mX < sReleasePoint) {
        button &= ~(DPAD_LEFT | DPAD_RIGHT);
    } else if (mX <= -sPressPoint) {
        button &= ~DPAD_RIGHT;
        button |= DPAD_LEFT;
    } else if (mX >= sPressPoint) {
        button &= ~DPAD_LEFT;
        button |= DPAD_RIGHT;
    }

    if (-sReleasePoint < mY && mY < sReleasePoint) {
        button &= ~(DPAD_DOWN | DPAD_UP);
    } else if (mY <= -sPressPoint) {
        button &= ~DPAD_UP;
        button |= DPAD_DOWN;
    } else if (mY >= sPressPoint) {
        button &= ~DPAD_DOWN;
        button |= DPAD_UP;
    }

    return button;
}

void JUTGamePad::CRumble::clear() {
    mFrame = 0;
    mLength = 0;
    mData = nullptr;
    mFrameCount = 0;
    mHardStopData = nullptr;
    JUTGamePad::CRumble::mEnabled = 0xF0000000;
}

void JUTGamePad::CRumble::clear(JUTGamePad* gamePad) {
    if (0 <= gamePad->getPortNum() && gamePad->getPortNum() < PAD_MAX_CONTROLLERS) {
        JUTGamePad::CRumble::mStatus[gamePad->getPortNum()] = 0;
        gamePad->stopMotorHard();
    }

    clear();
}

void JUTGamePad::CRumble::startMotor(int port) {
    if (JUTGamePad::CRumble::isEnabledPort(port)) {
        PADControlMotor(port, PAD_MOTOR_RUMBLE);
        JUTGamePad::CRumble::mStatus[port] = 1;
    }
}

void JUTGamePad::CRumble::stopMotor(int port, bool hard) {
    if (JUTGamePad::CRumble::isEnabledPort(port)) {
        PADControlMotor(port, (u8)(hard ? PAD_MOTOR_STOP_HARD : PAD_MOTOR_STOP));
        JUTGamePad::CRumble::mStatus[port] = 0;
    }
}

static bool getNumBit(u8* data, int bit) {
    u8 numBit = (0x80 >> (bit & 7)) & data[bit >> 3];
    return numBit != 0;
}

void JUTGamePad::CRumble::update(s16 port) {
    if (!JUTGamePad::CRumble::isEnabledPort(port)) {
        mFrame = 0;
        mLength = 0;
        mData = nullptr;
        mFrameCount = 0;
        mHardStopData = nullptr;
    }

    if (mLength != 0) {
        if (mFrame >= mLength) {
            JUTGamePad::CRumble::stopMotorHard(port);
            mLength = 0;
        } else {
            if (mFrameCount == 0) {
                if (JUTGamePad::CRumble::mStatus[port] == 0) {
                    JUTGamePad::CRumble::startMotor(port);
                }

                return;
            }

            bool enable = getNumBit(mData, mFrame % mFrameCount);
            bool status = JUTGamePad::CRumble::mStatus[port];
            if (enable && !status) {
                JUTGamePad::CRumble::startMotor(port);
            } else if (!enable) {
                bool hardStop = false;
                if (mHardStopData != nullptr) {
                    hardStop = getNumBit(mHardStopData, mFrame % mFrameCount);
                }

                if (status) {
                    JUTGamePad::CRumble::stopMotor(port, hardStop);
                } else if (hardStop) {
                    JUTGamePad::CRumble::stopMotorHard(port);
                }
            }
        }

        mFrame++;
    }
}

void JUTGamePad::CButton::setRepeat(u32 repeatMask, u32 repeatDelay, u32 repeatFreq) {
    mRepeatLastButton = 0;
    mRepeatTimer = 0;
    mRepeatMask = repeatMask;
    mRepeatDelay = repeatDelay;
    mRepeatFrequency = repeatFreq;
}

bool JUTGamePad::recalibrate(u32 channels) {
    for (int i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        if ((JUTGamePad::sSuppressPadReset & channel_mask[i]) != 0) {
            channels &= channel_mask[i] ^ 0xFFFFFFFF;
        }
    }

    BOOL res = PADRecalibrate(channels);
    return res;
}

JSUList<JUTGamePadLongPress> JUTGamePadLongPress::sPatternList(false);

void JUTGamePadLongPress::checkCallback(int port, u32 timer) {
    if (port >= 0) {
        if (timer >= _1C) {
            _11 = true;
            _48[port] = true;
            if (mCallback != nullptr) {
                mCallback(port, this, _50);
            }
        }
    }
}
