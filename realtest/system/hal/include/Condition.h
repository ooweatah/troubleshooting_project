
/* This code refers from android framework */

#ifndef _LIBS_UTILS_CONDITION_H
#define _LIBS_UTILS_CONDITION_H

#include <stdint.h>
#include <sys/types.h>
#include <time.h>

#include <pthread.h>

#include <Mutex.h>
#include <Timers.h>

/*
 * Condition variable class.  The implementation is system-dependent.
 *
 * Condition variables are paired up with mutexes.  Lock the mutex,
 * call wait(), then either re-wait() if things aren't quite what you want,
 * or unlock the mutex and continue.  All threads calling wait() must
 * use the same mutex for a given Condition.
 */
class Condition {
public:
    enum {
        PRIVATE = 0,
        SHARED = 1
    };

    Condition();
    Condition(int type);
    ~Condition();
    // Wait on the condition variable.  Lock the mutex before calling.
    status_t wait(Mutex& mutex);
    // same with relative timeout
    status_t waitRelative(Mutex& mutex, nsecs_t reltime);
    // Signal the condition variable, allowing one thread to continue.
    void signal();
    // Signal the condition variable, allowing all threads to continue.
    void broadcast();

private:
    pthread_cond_t mCond;
};

// ---------------------------------------------------------------------------


inline Condition::Condition() {
    pthread_cond_init(&mCond, NULL);
}
inline Condition::Condition(int type) {
    if (type == SHARED) {
        pthread_condattr_t attr;
        pthread_condattr_init(&attr);
        pthread_condattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
        pthread_cond_init(&mCond, &attr);
        pthread_condattr_destroy(&attr);
    } else {
        pthread_cond_init(&mCond, NULL);
    }
}
inline Condition::~Condition() {
    pthread_cond_destroy(&mCond);
}
inline status_t Condition::wait(Mutex& mutex) {
    return -pthread_cond_wait(&mCond, &mutex.mMutex);
}
inline status_t Condition::waitRelative(Mutex& mutex, nsecs_t reltime) {
#if defined(HAVE_PTHREAD_COND_TIMEDWAIT_RELATIVE)
    struct timespec ts;
    ts.tv_sec  = reltime/1000000000;
    ts.tv_nsec = reltime%1000000000;
    return -pthread_cond_timedwait_relative_np(&mCond, &mutex.mMutex, &ts);
#else // HAVE_PTHREAD_COND_TIMEDWAIT_RELATIVE
    struct timespec ts;
#if defined(HAVE_POSIX_CLOCKS)
    clock_gettime(CLOCK_REALTIME, &ts);
#else // HAVE_POSIX_CLOCKS
    // we don't support the clocks here.
    struct timeval t;
    gettimeofday(&t, NULL);
    ts.tv_sec = t.tv_sec;
    ts.tv_nsec= t.tv_usec*1000;
#endif // HAVE_POSIX_CLOCKS
    ts.tv_sec += reltime/1000000000;
    ts.tv_nsec+= reltime%1000000000;
    if (ts.tv_nsec >= 1000000000) {
        ts.tv_nsec -= 1000000000;
        ts.tv_sec  += 1;
    }
    return -pthread_cond_timedwait(&mCond, &mutex.mMutex, &ts);
#endif // HAVE_PTHREAD_COND_TIMEDWAIT_RELATIVE
}
inline void Condition::signal() {
    pthread_cond_signal(&mCond);
}
inline void Condition::broadcast() {
    pthread_cond_broadcast(&mCond);
}

#endif // _LIBS_UTILS_CONDITON_H
