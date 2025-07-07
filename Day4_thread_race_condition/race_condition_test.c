#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 1
#define INCREMENT_CNT 1000000

long long shared_var = 0;

void* thread_func(void* arg){
    for(int i=0; i<INCREMENT_CNT; i++){
        // critical section
        shared_var++;
    }
    return NULL;
}

int main(){
    pthread_t thread_id[NUM_THREADS];

    for(int i=0; i<NUM_THREADS; i++){
        if(pthread_create(&thread_id[i], NULL, thread_func, NULL)!=0){
            perror("pthread_create error");
            return 1;
        }
    }
    for(int i=0; i<NUM_THREADS; i++){
        pthread_join(thread_id[i], NULL);
    }

    printf("predict_var = %lld\n", (long long) NUM_THREADS * INCREMENT_CNT);
    printf("real_result = %lld\n", shared_var);
}