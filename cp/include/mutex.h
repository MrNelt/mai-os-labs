#ifndef SHARED_MUTEX_H
#define SHARED_MUTEX_H
#include <pthread.h>
struct TCommonMutex {
    pthread_mutex_t *ptr;  // Pointer to the pthread mutex and shared memory segment
    int shm_fd;            // Descriptor of shared memory object
    char *name;            // Name of the mutex and associated shared memory object
    int created;           // 1 if created new mutex, 0 if mutex was retrieved from memory
};
// If mutex with name exists it will be loaded, otherwise mutex will be created
TCommonMutex SharedMutexInit(const char *name);
// Close and destroy shared mutex and returns 0 in case of success, otherwise returns -1
int SharedMutexDestroy(TCommonMutex mutex);
#endif