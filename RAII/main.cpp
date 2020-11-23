#include "mutexlock.h"
#include <unistd.h>
#include <iostream>

#define    NUM_THREADS     10

int num=0;
Mutex mutex;

void *count(void *args) {
    MutexLock lock(&mutex);
    num++;
    std::cout<< "the num is:" << num <<std::endl;
}


int main(int argv, char *argc[]) {
    int t;
    pthread_t thread[NUM_THREADS];

    for( t = 0; t < NUM_THREADS; t++) {
        int ret = pthread_create(&thread[t], NULL, count, NULL);
        if(ret) {
            return -1;
        }
    }

    for( t = 0; t < NUM_THREADS; t++)
        pthread_join(thread[t], NULL);
    std::cout << num << std::endl;
    return 0;
}
