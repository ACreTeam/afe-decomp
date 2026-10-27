#include <dolphin.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/os.h>
#include <macros.h>

#include "../src/static/GAEJ01_01/dolphin/os/__os.h"

#define IsSuspended(suspend) (suspend > 0)

#define ENQUEUE_THREAD(thread, queue, link)                                    \
	do {                                                                       \
		OSThread* __prev = (queue)->tail;                                      \
		if (__prev == NULL) {                                                  \
			(queue)->head = (thread);                                          \
		} else {                                                               \
			__prev->link.next = (thread);                                      \
		}                                                                      \
		(thread)->link.prev = __prev;                                          \
		(thread)->link.next = 0;                                               \
		(queue)->tail       = (thread);                                        \
	} while (0);

#define DEQUEUE_THREAD(thread, queue, link)                                    \
	do {                                                                       \
		OSThread* __next = (thread)->link.next;                                \
		OSThread* __prev = (thread)->link.prev;                                \
		if (__next == NULL) {                                                  \
			(queue)->tail = __prev;                                            \
		} else {                                                               \
			__next->link.prev = __prev;                                        \
		}                                                                      \
		if (__prev == NULL) {                                                  \
			(queue)->head = __next;                                            \
		} else {                                                               \
			__prev->link.next = __next;                                        \
		}                                                                      \
	} while (0);

#define ENQUEUE_THREAD_PRIO(thread, queue, link)                               \
	do {                                                                       \
		OSThread* __prev;                                                      \
		OSThread* __next;                                                      \
		for (__next = (queue)->head;                                           \
		     __next && (__next->priority <= (thread)->priority);               \
		     __next = __next->link.next)                                       \
			;                                                                  \
                                                                               \
		if (__next == NULL) {                                                  \
			ENQUEUE_THREAD(thread, queue, link);                               \
		} else {                                                               \
			(thread)->link.next = __next;                                      \
			__prev              = __next->link.prev;                           \
			__next->link.prev   = (thread);                                    \
			(thread)->link.prev = __prev;                                      \
			if (__prev == NULL) {                                              \
				(queue)->head = (thread);                                      \
			} else {                                                           \
				__prev->link.next = (thread);                                  \
			}                                                                  \
		}                                                                      \
	} while (0);

#define DEQUEUE_HEAD(thread, queue, link)                                      \
	do {                                                                       \
		OSThread* __next = thread->link.next;                                  \
		if (__next == NULL) {                                                  \
			(queue)->tail = 0;                                                 \
		} else {                                                               \
			__next->link.prev = 0;                                             \
		}                                                                      \
		(queue)->head = __next;                                                \
	} while (0);

// which header should these go in?
extern unsigned char _stack_end[];
extern char _stack_addr[];

// .bss
static OSThreadQueue RunQueue[32];
static OSThread IdleThread;
static OSThread DefaultThread;
static struct OSContext IdleContext;
static volatile unsigned long RunQueueBits;
static volatile int RunQueueHint;
static long Reschedule;

#define ALIGN4(val) (((val) + 0x3) & ~0x3)
#define ALIGN8(val) (((val) + 0x7) & ~0x7)

// functions
static void OSInitMutexQueue(struct OSMutexQueue* queue);
static void __OSSwitchThread(OSThread* nextThread);
static int __OSIsThreadActive(OSThread* thread);
static void SetRun(OSThread* thread);
static void UnsetRun(OSThread* thread);
static OSThread* SetEffectivePriority(OSThread* thread, long priority);
static void UpdatePriority(OSThread* thread);
static OSThread* SelectThread(int yield);

typedef void (*OSSwitchThreadCallback)(OSThread* from, OSThread* to);

static void DefaultSwitchThreadCallback(OSThread* from, OSThread* to);
static OSSwitchThreadCallback SwitchThreadCallback = DefaultSwitchThreadCallback;

void OSClearStack(u8 val);

static inline void InitMutexQueue(struct OSMutexQueue* queue)
{
	queue->head = queue->tail = NULL;
}

static inline void SetCurrentThread(OSThread* thread)
{
	SwitchThreadCallback(__gCurrentThread, thread);
	__gCurrentThread = thread;
}

static void DefaultSwitchThreadCallback(OSThread* from, OSThread* to) { }

void __OSThreadInit()
{
	OSThread* thread = &DefaultThread;
	int prio;

	thread->state    = OS_THREAD_STATE_RUNNING;
	thread->attr     = OS_THREAD_ATTR_DETACH;
	thread->priority = thread->base = 16;
	thread->suspend                 = 0;
	thread->val                     = (void*)-1;
	thread->mutex                   = NULL;
	OSInitThreadQueue(&thread->queueJoin);
	InitMutexQueue(&thread->queueMutex);

	__gUnkThread1 = thread;

	OSClearContext(&thread->context);
	OSSetCurrentContext(&thread->context);
	thread->stackBase   = (void*)_stack_addr;
	thread->stackEnd    = (void*)_stack_end;
	*(thread->stackEnd) = OS_THREAD_STACK_MAGIC;

	SetCurrentThread(thread);
	OSClearStack(0);

	RunQueueBits = 0;
	RunQueueHint = FALSE;
	for (prio = OS_PRIORITY_MIN; prio <= OS_PRIORITY_MAX; ++prio) {
		OSInitThreadQueue(&RunQueue[prio]);
	}

	OSInitThreadQueue(&__OSActiveThreadQueue);
	ENQUEUE_THREAD(thread, &__OSActiveThreadQueue, linkActive);
	OSClearContext(&IdleContext);
	Reschedule = 0;
}

void OSInitThreadQueue(OSThreadQueue* queue) { queue->head = queue->tail = 0; }

OSThread* OSGetCurrentThread() { return __gCurrentThread; }

static void __OSSwitchThread(OSThread* nextThread)
{
	SwitchThreadCallback(__gCurrentThread, nextThread);
	__gCurrentThread = nextThread;
	OSSetCurrentContext(&nextThread->context);
	OSLoadContext(&nextThread->context);
}

int OSIsThreadTerminated(OSThread* thread)
{
	return (thread->state == 8 || thread->state == 0) ? 1 : 0;
}

static int __OSIsThreadActive(OSThread* thread)
{
	OSThread* active;

	if (thread->state == 0) {
		return 0;
	}

	for (active = __OSActiveThreadQueue.head; active;
	     active = active->linkActive.next) {
		if (thread == active) {
			return 1;
		}
	}
	return 0;
}

s32 OSDisableScheduler(void)
{
	register int enabled;
	long count;

	enabled    = OSDisableInterrupts();
	count      = Reschedule;
	Reschedule = count + 1;
	OSRestoreInterrupts(enabled);
	return count;
}

s32 OSEnableScheduler(void)
{
	register int enabled;
	long count;

	enabled    = OSDisableInterrupts();
	count      = Reschedule;
	Reschedule = count - 1;
	OSRestoreInterrupts(enabled);
	return count;
}

static void SetRun(OSThread* thread)
{
	ASSERTLINE(469, !IsSuspended(thread->suspend));
	ASSERTLINE(470, thread->state == OS_THREAD_STATE_READY);

	ASSERTLINE(472, OS_PRIORITY_MIN <= thread->priority
	                    && thread->priority <= OS_PRIORITY_MAX);

	thread->queue = &RunQueue[thread->priority];

	ENQUEUE_THREAD(thread, thread->queue, link);

	RunQueueBits |= 1 << (0x1F - thread->priority);
	RunQueueHint = 1;
}

static void UnsetRun(OSThread* thread)
{
	OSThreadQueue* queue;

	ASSERTLINE(0x1ED, thread->state == OS_THREAD_STATE_READY);

	ASSERTLINE(0x1EF, OS_PRIORITY_MIN <= thread->priority
	                      && thread->priority <= OS_PRIORITY_MAX);
	ASSERTLINE(0x1F0, thread->queue == &RunQueue[thread->priority]);

	queue = thread->queue;

	DEQUEUE_THREAD(thread, queue, link);

	if (!queue->head) {
		RunQueueBits &= ~(1 << (0x1F - thread->priority));
	}
	thread->queue = NULL;
}

long __OSGetEffectivePriority(OSThread* thread)
{
	long priority = thread->base;
	struct OSMutex* mutex;

	for (mutex = thread->queueMutex.head; mutex; mutex = mutex->link.next) {
		OSThread* blocked = mutex->queue.head;
		if (blocked && blocked->priority < priority) {
			priority = blocked->priority;
		}
	}
	return priority;
}

static OSThread* SetEffectivePriority(OSThread* thread, long priority)
{
	ASSERTLINE(547, !IsSuspended(thread->suspend));

	switch (thread->state) {
	case 1:
		UnsetRun(thread);
		thread->priority = priority;
		SetRun(thread);
		break;
	case 4:
		DEQUEUE_THREAD(thread, thread->queue, link);
		thread->priority = priority;

		ENQUEUE_THREAD_PRIO(thread, thread->queue, link);

		if (thread->mutex) {
			ASSERTLINE(0x232, thread->mutex->thread);
			return thread->mutex->thread;
		}
		break;
	case 2:
		RunQueueHint     = 1;
		thread->priority = priority;
		break;
	}
	return 0;
}

static void UpdatePriority(OSThread* thread)
{
	long priority;

	while (1) {
		if (thread->suspend > 0) {
			break;
		}
		priority = __OSGetEffectivePriority(thread);
		if (thread->priority == priority) {
			break;
		}
		thread = SetEffectivePriority(thread, priority);
		if (thread == 0) {
			break;
		}
	}
}

void __OSPromoteThread(OSThread* thread, long priority)
{
	while (1) {
		if (thread->suspend > 0 || thread->priority <= priority) {
			break;
		}
		thread = SetEffectivePriority(thread, priority);
		if (thread == 0) {
			break;
		}
	}
}

static OSThread* SelectThread(int yield)
{
	struct OSContext* currentContext;
	OSThread* currentThread;
	OSThread* nextThread;
	long priority;
	OSThreadQueue* queue;

	if (Reschedule > 0) {
		return NULL;
	}

	currentContext = OSGetCurrentContext();
	currentThread  = OSGetCurrentThread();

	if (currentContext != &currentThread->context) {
		return NULL;
	}

	if (currentThread) {
		if (currentThread->state == 2) {
			if (yield == 0) {
				priority = __cntlzw(RunQueueBits);
				if (currentThread->priority <= priority)
					return NULL;
			}
			currentThread->state = 1;
			SetRun(currentThread);
		}
		if (!(currentThread->context.state & 2)
		    && (OSSaveContext(&currentThread->context) != 0)) {
			return NULL;
		}
	}

	if (RunQueueBits == 0) {
		SwitchThreadCallback(__gCurrentThread, NULL);
		__gCurrentThread = NULL;
		OSSetCurrentContext(&IdleContext);
		do {
			OSEnableInterrupts();
			while (RunQueueBits == 0)
				;
			OSDisableInterrupts();
		} while (RunQueueBits == 0);
		OSClearContext(&IdleContext);
	}

	RunQueueHint = 0;
	priority     = __cntlzw(RunQueueBits);

	ASSERTLINE(0x2C6,
	           OS_PRIORITY_MIN <= priority && priority <= OS_PRIORITY_MAX);

	queue      = &RunQueue[priority];
	nextThread = queue->head;

	DEQUEUE_HEAD(nextThread, queue, link);

	ASSERTLINE(0x2C9, nextThread->priority == priority);

	if (!queue->head) {
		RunQueueBits &= ~(1 << (0x1F - priority));
	}
	nextThread->queue = 0;
	nextThread->state = 2;
	__OSSwitchThread(nextThread);
	return nextThread;
}

void __OSReschedule(void)
{
	if (RunQueueHint != 0) {
		SelectThread(0);
	}
}

void OSYieldThread(void)
{
	int enabled = OSDisableInterrupts();

	SelectThread(1);
	OSRestoreInterrupts(enabled);
}

int OSCreateThread(OSThread* thread, void* (*func)(void*), void* param,
                   void* stack, unsigned long stackSize, long priority,
                   unsigned short attr)
{
	BOOL enable;
	u32 sp;
	int i;

	if (priority < OS_PRIORITY_MIN || priority > OS_PRIORITY_MAX) {
		return FALSE;
	}

	sp               = ((u32)stack & 0xFFFFFFF8);
	thread->state    = OS_THREAD_STATE_READY;
	thread->attr     = attr & OS_THREAD_ATTR_DETACH;
	thread->base     = priority;
	thread->priority = priority;
	thread->suspend  = 1;
	thread->val      = (void*)-1;
	thread->mutex    = NULL;
	OSInitThreadQueue(&thread->queueJoin);
	InitMutexQueue(&thread->queueMutex);
	*(u32*)(sp - 8) = 0;
	*(u32*)(sp - 4) = 0;

	OSInitContext(&thread->context, (u32)func, (u32)(sp - 8));

	thread->context.lr     = (u32)&OSExitThread;
	thread->context.gpr[3] = (u32)param;
	thread->stackBase      = stack;
	thread->stackEnd       = (u32*)((u32)stack - stackSize);
	*(thread->stackEnd)    = OS_THREAD_STACK_MAGIC;
	thread->error          = 0;
	for (i = 0; i < 2; i++) {
		thread->specific[i] = NULL;
	}

	enable = OSDisableInterrupts();

	if (__OSErrorTable[OS_ERROR_FPE] != NULL) {
		thread->context.srr1 |= 0x900;
		thread->context.state |= OS_CONTEXT_STATE_FPSAVED;
		thread->context.fpscr = (__OSFpscrEnableBits & 0xF8) | 0x4;

		for (i = 0; i < 32; i++) {
			*(u64*)&thread->context.fpr[i] = -1;
			*(u64*)&thread->context.psf[i] = -1;
		}
	}

	ENQUEUE_THREAD(thread, &__OSActiveThreadQueue, linkActive);
	OSRestoreInterrupts(enable);
	return TRUE;
}

void OSExitThread(void* val)
{
	int enabled             = OSDisableInterrupts();
	OSThread* currentThread = OSGetCurrentThread();

	ASSERTMSGLINE(0x354, currentThread,
	              "OSExitThread(): current thread does not exist.");
	ASSERTMSGLINE(0x356, currentThread->state == 2,
	              "OSExitThread(): current thread is not running.");
	ASSERTMSGLINE(0x358, __OSIsThreadActive(currentThread) != 0,
	              "OSExitThread(): current thread is not active.");

	OSClearContext(&currentThread->context);
	if (currentThread->attr & 1) {
		DEQUEUE_THREAD(currentThread, &__OSActiveThreadQueue, linkActive);
		currentThread->state = 0;
	} else {
		currentThread->state = 8;
		currentThread->val   = val;
	}
	__OSUnlockAllMutex(currentThread);
	OSWakeupThread(&currentThread->queueJoin);
	RunQueueHint = 1;

	if (RunQueueHint != 0) {
		SelectThread(0);
	}

	OSRestoreInterrupts(enabled);
}

void OSCancelThread(OSThread* thread)
{
	int enabled = OSDisableInterrupts();

	ASSERTMSG1LINE(0x37E, __OSIsThreadActive(thread) != 0,
	               "OSExitThread(): thread %p is not active.", thread);

	switch (thread->state) {
	case 1:
		if (thread->suspend <= 0) {
			UnsetRun(thread);
		}
		break;
	case 2:
		RunQueueHint = 1;
		break;
	case 4:
		DEQUEUE_THREAD(thread, thread->queue, link);
		thread->queue = 0;
		if ((thread->suspend <= 0) && (thread->mutex)) {
			ASSERTLINE(0x391, thread->mutex->thread);
			UpdatePriority(thread->mutex->thread);
		}
		break;
	default:
		OSRestoreInterrupts(enabled);
		return;
	}
	OSClearContext(&thread->context);
	if (thread->attr & 1) {
		DEQUEUE_THREAD(thread, &__OSActiveThreadQueue, linkActive);
		thread->state = 0;
	} else {
		thread->state = 8;
	}
	__OSUnlockAllMutex(thread);
	OSWakeupThread(&thread->queueJoin);
	__OSReschedule();
	OSRestoreInterrupts(enabled);
}

int OSJoinThread(OSThread* thread, void** val)
{
	int enabled = OSDisableInterrupts();

	ASSERTMSG1LINE(0x3CA, __OSIsThreadActive(thread) != 0,
	               "OSJoinThread(): thread %p is not active.", thread);

	if (!(thread->attr & 1) && (thread->state != 8)
	    && (thread->queueJoin.head == NULL)) {
		OSSleepThread(&thread->queueJoin);
		if (__OSIsThreadActive(thread) == 0) {
			OSRestoreInterrupts(enabled);
			return 0;
		}
	}
	if (thread->state == 8) {
		if (val) {
			*val = thread->val;
		}
		DEQUEUE_THREAD(thread, &__OSActiveThreadQueue, linkActive);
		thread->state = 0;
		OSRestoreInterrupts(enabled);
		return 1;
	}
	OSRestoreInterrupts(enabled);
	return 0;
}

void OSDetachThread(OSThread* thread)
{
	int enabled = OSDisableInterrupts();

	ASSERTMSG1LINE(0x3FC, __OSIsThreadActive(thread) != 0,
	               "OSDetachThread(): thread %p is not active.", thread);

	thread->attr |= 1;
	if (thread->state == 8) {
		DEQUEUE_THREAD(thread, &__OSActiveThreadQueue, linkActive);
		thread->state = 0;
	}
	OSWakeupThread(&thread->queueJoin);
	OSRestoreInterrupts(enabled);
}

long OSResumeThread(OSThread* thread)
{
	int enabled = OSDisableInterrupts();
	long suspendCount;

	ASSERTMSG1LINE(0x419, __OSIsThreadActive(thread) != 0,
	               "OSResumeThread(): thread %p is not active.", thread);
	ASSERTMSG1LINE(0x41B, thread->state != 8,
	               "OSResumeThread(): thread %p is terminated.", thread);

	suspendCount = thread->suspend--;
	if (thread->suspend < 0) {
		thread->suspend = 0;
	} else if (thread->suspend == 0) {
		switch (thread->state) {
		case 1:
			thread->priority = __OSGetEffectivePriority(thread);
			SetRun(thread);
			break;
		case 4:
			ASSERTLINE(0x42A, thread->queue);
			DEQUEUE_THREAD(thread, thread->queue, link);
			thread->priority = __OSGetEffectivePriority(thread);
			ENQUEUE_THREAD_PRIO(thread, thread->queue, link);
			if (thread->mutex) {
				UpdatePriority(thread->mutex->thread);
			}
		}
		__OSReschedule();
	}
	OSRestoreInterrupts(enabled);
	return suspendCount;
}

long OSSuspendThread(OSThread* thread)
{
	int enabled = OSDisableInterrupts();
	long suspendCount;

	ASSERTMSG1LINE(0x44C, __OSIsThreadActive(thread) != 0,
	               "OSSuspendThread(): thread %p is not active.", thread);
	ASSERTMSG1LINE(0x44E, thread->state != 8,
	               "OSSuspendThread(): thread %p is terminated.", thread);

	suspendCount = thread->suspend++;
	if (suspendCount == 0) {
		switch (thread->state) {
		case 2:
			RunQueueHint  = 1;
			thread->state = 1;
			break;
		case 1:
			UnsetRun(thread);
			break;
		case 4:
			DEQUEUE_THREAD(thread, thread->queue, link);
			thread->priority = 0x20;
			ENQUEUE_THREAD(thread, thread->queue, link);
			if (thread->mutex) {
				ASSERTLINE(0x463, thread->mutex->thread);
				UpdatePriority(thread->mutex->thread);
			}
			break;
		}
		__OSReschedule();
	}
	OSRestoreInterrupts(enabled);
	return suspendCount;
}

void OSSleepThread(OSThreadQueue* queue)
{
	int enabled             = OSDisableInterrupts();
	OSThread* currentThread = OSGetCurrentThread();

	ASSERTMSGLINE(0x484, currentThread,
	              "OSSleepThread(): current thread does not exist.");
	ASSERTMSG1LINE(0x486, __OSIsThreadActive(currentThread) != 0,
	               "OSSleepThread(): current thread %p is not active.",
	               currentThread);
	ASSERTMSG1LINE(0x488, currentThread->state == 2,
	               "OSSleepThread(): current thread %p is not running.",
	               currentThread);
	ASSERTMSG1LINE(0x48A, currentThread->suspend <= 0,
	               "OSSleepThread(): current thread %p is suspended.",
	               currentThread);

	currentThread->state = 4;
	currentThread->queue = queue;
	ENQUEUE_THREAD_PRIO(currentThread, queue, link);
	RunQueueHint = 1;
	__OSReschedule();
	OSRestoreInterrupts(enabled);
}

void OSWakeupThread(OSThreadQueue* queue)
{
	int enabled = OSDisableInterrupts();

	while (queue->head) {
		OSThread* thread = queue->head;

		DEQUEUE_HEAD(thread, queue, link);

		ASSERTLINE(0x4A7, __OSIsThreadActive(thread));
		ASSERTLINE(0x4A8, thread->state != OS_THREAD_STATE_MORIBUND);
		ASSERTLINE(0x4A9, thread->queue == queue);
		thread->state = 1;
		if (thread->suspend <= 0) {
			SetRun(thread);
		}
	}
	__OSReschedule();
	OSRestoreInterrupts(enabled);
}

int OSSetThreadPriority(struct OSThread * thread, long priority) {
    int enabled;

    ASSERTMSGLINE(0x4C3, (priority >= 0) && (priority <= 0x1F), "OSSetThreadPriority(): priority out of range (0 <= priority <= 31).");

    if ((priority < 0) || (priority > 0x1F)) {
        return 0;
    }
    enabled = OSDisableInterrupts();

    ASSERTMSG1LINE(0x4CA, __OSIsThreadActive(thread) != 0, "OSSetThreadPriority(): thread %p is not active.", thread);
    ASSERTMSG1LINE(0x4CC, thread->state != 8, "OSSetThreadPriority(): thread %p is terminated.", thread);

    if (thread->base != priority) {
        thread->base = priority;
        UpdatePriority(thread);
        __OSReschedule();
    }
    OSRestoreInterrupts(enabled);
    return 1;
}

long OSGetThreadPriority(OSThread* thread) { return thread->base; }


static int CheckThreadQueue(struct OSThreadQueue * queue) {
    struct OSThread * thread;

    if ((queue->head != NULL) && (queue->head->link.prev != NULL)) {
        return 0;
    }
    if ((queue->tail != NULL) && (queue->tail->link.next != NULL)) {
        return 0;
    }
    thread = queue->head;
    while(thread) {
        if ((thread->link.next != NULL) && (thread != thread->link.next->link.prev)) {
            return 0;
        }
        if ((thread->link.prev != NULL) && (thread != thread->link.prev->link.next)) {
            return 0;
        }
        thread = thread->link.next;
    }
    return 1;
}

static int IsMember(struct OSThreadQueue * queue, struct OSThread * thread) {
    struct OSThread * member = queue->head;

    while(member) {
        if (thread == member) {
            return 1;
        }
        member = member->link.next;
    }
    return 0;
}

#define ASSERTREPORT(line, cond) \
    if (!(cond)) { \
        OSReport("OSCheckActiveThreads: Failed " #cond " in %d\n", line); \
        OSPanic(__FILE__, line, ""); \
    }

long OSCheckActiveThreads() {
    struct OSThread * thread;
    long prio;
    long cThread;
    int enabled;

    cThread = 0;
    enabled = OSDisableInterrupts();
    
    for(prio = 0; prio <= 0x1F; prio++) {
        if (RunQueueBits & (1 << (0x1F - prio))) {
            ASSERTREPORT(0x5C1, RunQueue[prio].head != NULL && RunQueue[prio].tail != NULL);
        } else {
            ASSERTREPORT(0x5C6, RunQueue[prio].head == NULL && RunQueue[prio].tail == NULL);
        }
        ASSERTREPORT(0x5C8, CheckThreadQueue(&RunQueue[prio]));
    }

    ASSERTREPORT(0x5CD, __OSActiveThreadQueue.head == NULL || __OSActiveThreadQueue.head->linkActive.prev == NULL);
    ASSERTREPORT(0x5CF, __OSActiveThreadQueue.tail == NULL || __OSActiveThreadQueue.tail->linkActive.next == NULL);

    thread = __OSActiveThreadQueue.head;
    while(thread) {
        cThread++;
        ASSERTREPORT(0x5D7, thread->linkActive.next == NULL || thread == thread->linkActive.next->linkActive.prev);
        ASSERTREPORT(0x5D9, thread->linkActive.prev == NULL || thread == thread->linkActive.prev->linkActive.next);
        ASSERTREPORT(0x5DC, *(thread->stackEnd) == OS_THREAD_STACK_MAGIC);
        ASSERTREPORT(0x5DF, OS_PRIORITY_MIN <= thread->priority && thread->priority <= OS_PRIORITY_MAX+1);
        ASSERTREPORT(0x5E0, 0 <= thread->suspend);
        ASSERTREPORT(0x5E1, CheckThreadQueue(&thread->queueJoin));

        switch(thread->state) {
            case 1:
                if (thread->suspend <= 0) {
                    ASSERTREPORT(0x5E7, thread->queue == &RunQueue[thread->priority]);
                    ASSERTREPORT(0x5E8, IsMember(&RunQueue[thread->priority], thread));
                    ASSERTREPORT(0x5E9, thread->priority == __OSGetEffectivePriority(thread));
                }
                break;
            case 2:
                ASSERTREPORT(0x5ED, !IsSuspended(thread->suspend));
                ASSERTREPORT(0x5EE, thread->queue == NULL);
                ASSERTREPORT(0x5EF, thread->priority == __OSGetEffectivePriority(thread));
                break;
            case 4:
                ASSERTREPORT(0x5F2, thread->queue != NULL);
                ASSERTREPORT(0x5F3, CheckThreadQueue(thread->queue));
                ASSERTREPORT(0x5F4, IsMember(thread->queue, thread));
                if (thread->suspend <= 0) {
                    ASSERTREPORT(0x5F7, thread->priority == __OSGetEffectivePriority(thread));
                } else {
                    ASSERTREPORT(0x5FB, thread->priority == 32);
                }
                ASSERTREPORT(0x5FD, !__OSCheckDeadLock(thread));
                break;
            case 8:
                ASSERTREPORT(0x601, thread->queueMutex.head == NULL && thread->queueMutex.tail == NULL);
                break;
            default:
                OSReport("OSCheckActiveThreads: Failed. unkown thread state (%d) of thread %p\n", thread->state, thread);
                OSPanic("OSThread.c", 0x607, "");
        }
        ASSERTREPORT(0x60C, __OSCheckMutexes(thread));
        thread = thread->linkActive.next;
    }
    OSRestoreInterrupts(enabled);
    return cThread;
}

void OSClearStack(u8 val)
{
	register u32 sp;
	register u32* p;
	register u32 pattern;

	pattern = ((u32)val << 24) | ((u32)val << 16) | ((u32)val << 8) | (u32)val;
	sp      = OSGetStackPointer();
	for (p = __gCurrentThread->stackEnd + 1; p < (u32*)sp; ++p) {
		*p = pattern;
	}
}
