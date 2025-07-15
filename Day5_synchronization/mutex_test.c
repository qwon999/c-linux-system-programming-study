#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 10
#define INCREMENT_CNT 1000000

long long shared_var = 0;
pthread_mutex_t mutex;

void* function(void* arg){
    for(int i = 0 ; i < INCREMENT_CNT ; i++){
        pthread_mutex_lock(&mutex);
        shared_var++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(){
    pthread_t thread_id[NUM_THREADS];
    if(pthread_mutex_init(&mutex, NULL)!=0){
        perror("mutex init error");
        return 1;
    }

    for(int i=0; i<NUM_THREADS; i++){
        if(pthread_create(&thread_id[i], NULL, function, NULL)!=0){
            perror("pthread_create error");
        }
    }
    for(int i=0; i<NUM_THREADS; i++){
        pthread_join(thread_id[i], NULL);
    }
    printf("predict_var = %lld\n", NUM_THREADS * INCREMENT_CNT);
    printf("real_result = %lld\n", shared_var);
    return 0;
}