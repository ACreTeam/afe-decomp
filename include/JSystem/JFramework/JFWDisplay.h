#ifndef _JSYSTEM_JFW_JFWDISPLAY_H
#define _JSYSTEM_JFW_JFWDISPLAY_H

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTDirectPrint.h"
#include "JSystem/JUtility/JUTFader.h"
#include "JSystem/JUtility/JUTProcBar.h"
#include "JSystem/JUtility/JUTVideo.h"
#include "JSystem/JUtility/JUTXfb.h"
#include "JSystem/JUtility/TColor.h"
#include "types.h"

typedef void (*JFWDisplayUnkFunc)(void);

extern GC_Mtx e_mtx;

class JFWAlarm : public OSAlarm { // everything here seems to be auto inlined or unused
  public:
    // Contructor and Destructor are both present in map but unused, not sure if it belongs here
    JFWAlarm() : mLink(this) {
    }
    ~JFWAlarm() {
    }
    void createAlarm() {
        OSCreateAlarm(this);
    }
    void cancelAlarm() {
        OSCancelAlarm(this);
    }
    void removeLink() {
        sList.remove(&mLink);
    }
    void appendLink() {
        sList.append(&mLink);
    }

    OSThread* getThread() const {
        return mThread;
    }
    void setThread(OSThread* thread) {
        mThread = thread;
    }

    static JSUList<JFWAlarm> sList; //

  public:
    /* 0x28 */ OSThread* mThread;
    /* 0x2C */ JSULink<JFWAlarm> mLink;
};

class JFWDisplay {
  public:
    enum EDrawDone {
        /* 0x0 */ UNK_METHOD_0 = 0,
        /* 0x1 */ UNK_METHOD_1 = 1
    };

    static JFWDisplay* createManager(const _GXRenderModeObj*, JKRHeap*, JUTXfb::EXfbNumber, bool); // 0x80015bfc
    static JFWDisplay* createManager(JKRHeap* heap, JUTXfb::EXfbNumber xfbNum, bool enableAlpha) {
        return createManager(nullptr, heap, xfbNum, enableAlpha);
    }
    void waitBlanking(int);                                                                        // 0x8001684c
    void threadSleep(s64);                                                                         // 0x800169fc
    void clearEfb_init();                                                                          // 0x80016ab8
    void clearEfb();                                                                               // 0x80016b2c
    void clearEfb(_GXColor);                                                                       // 0x80016b58
    void clearEfb(int, int, int, int, _GXColor);                                                   // 0x80016b9c
    void calcCombinationRatio();                                                                   // 0x80016f0c

    void ctor_subroutine(bool);
    JFWDisplay(JKRHeap*, JUTXfb::EXfbNumber, bool);

    static void destroyManager();
    void prepareCopyDisp();
    void drawendXfb_single();
    void exchangeXfb_double();
    void exchangeXfb_triple();
    void copyXfb_triple();
    void preGX();
    void endGX();
    void* changeToSingleXfb(int);
    void* changeToDoubleXfb();

    // UNUSED
    JFWDisplay(void*, bool);
    JFWDisplay(void*, void*, bool);
    JFWDisplay(void*, void*, void*, bool);
    void createManager(const _GXRenderModeObj*, void*, bool);
    void createManager(const _GXRenderModeObj*, void*, void*, bool);
    void createManager(const _GXRenderModeObj*, void*, void*, void*, bool);
    void deleteToSingleXfb(int);
    void deleteToSingleXfb(void*);
    void addToDoubleXfb(void*, bool);
    void addToDoubleXfb(JKRHeap*);
    void clearAllXfb();
    s32 frameToTick(float);
    static void setForOSResetSystem();

    // Virtual functions
    virtual void beginRender(); // 0x80015e0c
    virtual void endRender();   // 0x8001633c
    virtual void endFrame();    // 0x8001669c
    virtual ~JFWDisplay();      // 0x80015b80

    static JFWDisplay* getManager() {
        return sManager;
    }

    const GXRenderModeObj* getRenderMode() const {
        return JUTVideo::getManager()->getRenderMode();
    }

    int getEfbHeight() const {
        return (u16)JUTVideo::getManager()->getEfbHeight();
    }

    int getEfbWidth() const {
        return JUTVideo::getManager()->getFbWidth();
    }

    JUTFader* getFader() const {
        return mFader;
    }
    void setFader(JUTFader* fader) {
        mFader = fader;
    }

    bool startFadeOut(int duration) {
        if (mFader != nullptr) {
            return mFader->startFadeOut(duration);
        }
        return true;
    }

    bool startFadeIn(int duration) {
        if (mFader != nullptr) {
            return mFader->startFadeIn(duration);
        }
        return true;
    }

    void setTickRate(u32 rate) {
        mTickRate = rate;
        mFrameRate = 0;
    }
    JUtility::TColor getClearColor() const {
        return mClearColor;
    }

    void setClearColor(u8 r, u8 g, u8 b, u8 a) {
        mClearColor.set(r, g, b, a);
    }

    void setClearColor(JUtility::TColor color) {
        mClearColor = color;
    }

    void setFBAlpha(bool enable) {
        mEnableAlpha = enable;
    }

    bool getFBAlpha() {
        return mEnableAlpha;
    }

    void setGamma(GXGamma gamma) {
        mGamma = gamma;
    }

    void setFrameRate(u16 framerate) {
        mFrameRate = framerate;
        mTickRate = 0;
    }

    static JFWDisplay* sManager; // 0x80415718

  private:
    JUTFader* mFader;                // 04
    JUtility::TColor mClearColor;    // 08
    u32 mZClear;                     // 0c
    JUTXfb* mXfb;                    // 10
    u16 mGamma;                      // 14
    EDrawDone mDrawDoneMethod;       // 18
    u16 mFrameRate;                  // 1c
    u32 mTickRate;                   // 20
    bool mEnableAlpha;               // 24
    u16 mClamp;                      // 26
    f32 mCombinationRatio;           // 28
    u32 mStartTick;                  // 2c, tick of when the frame starts rendering
    u32 mFrameTime;                  // 30, time it took to render a frame/amount of ticks beginRender took
    u32 mVideoFrameTime;             // 34
    int mDrawInterval;               // 38
    int mDrawCount;                  // 3c
    bool mIsDrawFrame;               // 40
    JFWDisplayUnkFunc mPreCopyDispFunc; // 44
    s16 mDrawingXfbNo;               // 48
    bool mIsSingleXfb;               // 4a
};

#endif
