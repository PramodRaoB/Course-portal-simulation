#ifndef PARALLELISM_WRAPPER_H
#define PARALLELISM_WRAPPER_H

#include <pthread.h>

int Pthread_mutex_lock(pthread_mutex_t *p);
int Pthread_mutex_unlock(pthread_mutex_t *p);
int Pthread_mutex_init(pthread_mutex_t *p, void *ptr);
int Pthread_cond_init(pthread_cond_t *p, void *ptr);
int Pthread_cond_signal(pthread_cond_t *p);
int Pthread_cond_broadcast(pthread_cond_t *p);
int Pthread_cond_wait(pthread_cond_t *p, pthread_mutex_t *x);

#endif //PARALLELISM_WRAPPER_H
