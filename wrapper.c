#include <assert.h>
#include "wrapper.h"

int Pthread_mutex_lock(pthread_mutex_t *p) {
    int rc = pthread_mutex_lock(p);
    assert(rc == 0);
    return 0;
}

int Pthread_mutex_unlock(pthread_mutex_t *p) {
    int rc = pthread_mutex_unlock(p);
    assert(rc == 0);
    return 0;
}

int Pthread_mutex_init(pthread_mutex_t *p, void *ptr) {
    int rc = pthread_mutex_init(p, ptr);
    assert(rc == 0);
    return 0;
}

int Pthread_cond_init(pthread_cond_t *p, void *ptr) {
    int rc = pthread_cond_init(p, ptr);
    assert(rc == 0);
    return 0;
}

int Pthread_cond_signal(pthread_cond_t *p) {
    int rc = pthread_cond_signal(p);
    assert(rc == 0);
    return 0;
}
