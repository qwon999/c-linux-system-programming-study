#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void* thread_func(void* arg){
    int thread_num = *(int*)arg;
    printf("thread %d start...\n", thread_num);
    sleep(2);
    printf("thread %d end...\n", thread_num);
    return NULL;
}

int main(){
    pthread_t thread_id;
    int arg = 1;

    printf("main thread : create new thread.\n");
    if(pthread_create(&thread_id, NULL, thread_func, &arg)!=0) {
        perror("pthread_create error");
        return 1;
    }
    printf("main thread : wait for thread end.\n");
    pthread_join(thread_id, NULL); // wait과 유사
    printf("main thread : thread end.\n");
    return 0;


}