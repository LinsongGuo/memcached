#pragma once

#if 0
#include <base/lock.h>
#include <base/log.h>
#include <base/tcache.h>
#include <base/thread.h>

#include <net/ip.h>

#include <runtime/rculist.h>
#include <runtime/runtime.h>
#include <runtime/sync.h>
#include <runtime/tcp.h>
#include <runtime/thread.h>
#include <runtime/timer.h>
#include <runtime/udp.h>

#undef assert
#define assert(x) BUG_ON(!(x))
#endif

// #ifndef _GNU_SOURCE
// #error
// #endif
// #include <sched.h>

#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

       #include <sys/syscall.h>   /* For SYS_xxx definitions */

#undef abort
#define abort()                                                                \
  {do {                                                                         \
    fprintf(stderr, "%s:%d %s aborting\n", __FILE__, __LINE__, __func__);        \
    exit(-1);\
  } while (0); }

#define CACHE_LINE_SIZE 64

typedef pthread_mutex_t mutex_t;
#define mutex_lock pthread_mutex_lock
#define mutex_unlock pthread_mutex_unlock
#define mutex_init(x) pthread_mutex_init(x, NULL)

typedef pthread_mutex_t spinlock_t;
#define spin_lock_np mutex_lock
#define spin_lock mutex_lock
#define spin_unlock_np mutex_unlock
#define spin_unlock mutex_unlock
#define spin_lock_init mutex_init

static inline int mutex_try_lock(pthread_mutex_t *mtx)
{
    int ret = pthread_mutex_trylock(mtx);
    return ret == 0;
}


typedef pthread_cond_t condvar_t;
#define condvar_init(x) pthread_cond_init(x, NULL)
#define condvar_wait pthread_cond_wait
#define condvar_signal pthread_cond_signal


// #define unlikely(x)

static inline void timer_sleep(uint64_t micros) {
  struct timespec s;
  s.tv_sec = micros / 1000000UL;
  s.tv_nsec = 1000UL * (micros % 1000000UL);
  nanosleep(&s, NULL);
}

#define BUG() abort()
#define BUG_ON(x)                                                              \
  do {                                                                         \
    if (x)                                                                     \
      abort();                                                                 \
  } while (0);
