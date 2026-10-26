#include "JSystem/JKernel/JKRMacro.h"
#include "JSystem/JKernel/JKRThread.h"
#include "JSystem/JKernel/JKRHeap.h"

JSUList<JKRThread> JKRThread::sThreadList(false);
JSUList<JKRTask> JKRTask::sTaskList;
u8 JKRTask::sEndMesgQueue[32];

JKRThread::JKRThread(u32 stackSize, int msgCount, int threadPrio) : mLink(this) {
    JKRHeap* heap = JKRHeap::findFromRoot(this);
    if (heap == nullptr) {
        heap = JKRHeap::getSystemHeap();
    }

    setCommon_heapSpecified(heap, stackSize, threadPrio);
    setCommon_mesgQueue(mHeap, msgCount);
}

JKRThread::JKRThread(OSThread* threadRecord, int msgCount) : mLink(this) {
    mHeap = nullptr;
    mThreadRecord = threadRecord;
    mStackSize = (u32)threadRecord->stackEnd - (u32)threadRecord->stackBase;
    mStackMemory = threadRecord->stackBase;

    setCommon_mesgQueue(JKRHeap::getSystemHeap(), msgCount);
}

JKRThread::~JKRThread() {
    sThreadList.remove(&mLink);

    if (mHeap != nullptr) {
        if (!OSIsThreadTerminated(mThreadRecord)) {
            OSDetachThread(mThreadRecord);
            OSCancelThread(mThreadRecord);
        }

        JKRFreeToHeap(mHeap, mStackMemory);
        JKRFreeToHeap(mHeap, mThreadRecord);
    }

    JKRFree(mMesgBuffer);
}

void JKRThread::setCommon_mesgQueue(JKRHeap* heap, int msgCount) {
    mMesgCount = msgCount;
    mMesgBuffer = (OSMessage*)JKRHeap::alloc(mMesgCount * sizeof(OSMessage), 0, heap);

    OSInitMessageQueue(&mMesgQueue, mMesgBuffer, mMesgCount);
    sThreadList.append(&mLink);
    mCurrentHeap = nullptr;
    mCurrentHeapError = 0;
}

BOOL JKRThread::setCommon_heapSpecified(JKRHeap* heap, u32 stackSize, int threadPrio) {
    mHeap = heap;
    mStackSize = JKR_ALIGN32(stackSize);
    mStackMemory = JKRHeap::alloc(mStackSize, 32, mHeap);
    mThreadRecord = (OSThread*)JKRHeap::alloc(sizeof(OSThread), 32, mHeap);
    return OSCreateThread(mThreadRecord, &JKRThread::start, this, (void*)((u32)mStackMemory + mStackSize), mStackSize,
                          threadPrio, OS_THREAD_ATTR_DETACH);
}

void* JKRThread::start(void* thread) {
    return static_cast<JKRThread*>(thread)->run();
}

void* JKRThread::run() {
    return nullptr;
}

JKRTask::JKRTask() : JKRThread(0x4000, 4, 31) {
}

JKRTask::~JKRTask() {
}

JKRTask* JKRTask::create() {
    return new JKRTask();
}

void JKRTask::destroy() {
    delete this;
}

void* JKRTask::run() {
    Request* req;
    while (true) {
        req = (Request*)waitMessageBlock();
        if (req->mCb) {
            req->mCb(req->mArg);
            if (mTaskMsgQueue) {
                OSSendMessage(mTaskMsgQueue, req->mMsg, OS_MESSAGE_NOBLOCK);
            }
        }
        req->mCb = nullptr;
    }
}

bool JKRTask::request(RequestCallback callback, void* arg, void* msg) {
    Request* req = searchBlank();
    if (req == nullptr) {
        return false;
    }
    req->mCb = callback;
    req->mArg = arg;
    req->mMsg = msg;
    bool sendResult = OSSendMessage(&mMesgQueue, req, OS_MESSAGE_NOBLOCK);
    if (!sendResult) {
        req->mCb = nullptr;
    }
    return sendResult;
}
