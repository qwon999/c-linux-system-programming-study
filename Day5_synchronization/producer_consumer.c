#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define BUFFER_SIZE 5       // 공유 버퍼의 크기
#define NUM_PRODUCERS 2     // 생산자 스레드의 수
#define NUM_CONSUMERS 2     // 소비자 스레드의 수
#define ITEMS_TO_PRODUCE 10 // 각 생산자가 만들 아이템의 수

// --- 공유 자원 ---
int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;
int out = 0;

pthread_mutex_t mutex;
pthread_cond_t cond_not_full;
pthread_cond_t cond_not_empty;
// --- ---

void* producer(void *arg) {
    int thread_id = *(int*)arg; // 전달받은 주소의 '값'을 복사해옴
    free(arg); // 값을 복사했으므로, 원본 메모리는 바로 해제해도 안전함

    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) {
            printf("Producer #%d: Buffer is FULL. Waiting...\n", thread_id);
            pthread_cond_wait(&cond_not_full, &mutex);
        }

        int item = (thread_id * 100) + i; // 스레드별로 아이템 번호 구분
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("Producer #%d: Produced item %d. (Buffer: %d/%d)\n", thread_id, item, count, BUFFER_SIZE);

        pthread_cond_signal(&cond_not_empty);
        pthread_mutex_unlock(&mutex);

        usleep((rand() % 100) * 1000); // 0~99ms 사이의 랜덤한 시간 동안 대기
    }
    return NULL;
}

void* consumer(void *arg) {
    int thread_id = *(int*)arg;
    free(arg);

    // 각 소비자가 소비해야 할 아이템 개수 계산
    int items_to_consume = (NUM_PRODUCERS * ITEMS_TO_PRODUCE) / NUM_CONSUMERS;

    for (int i = 0; i < items_to_consume; i++) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {
            printf("Consumer #%d: Buffer is EMPTY. Waiting...\n", thread_id);
            pthread_cond_wait(&cond_not_empty, &mutex);
        }

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf("Consumer #%d: Consumed item %d. (Buffer: %d/%d)\n", thread_id, item, count, BUFFER_SIZE);

        pthread_cond_signal(&cond_not_full);
        pthread_mutex_unlock(&mutex);

        usleep((rand() % 150) * 1000); // 0~149ms 사이의 랜덤한 시간 동안 대기
    }
    return NULL;
}

int main() {
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];

    srand(time(NULL)); // 랜덤 시드 초기화

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_not_full, NULL);
    pthread_cond_init(&cond_not_empty, NULL);

    // 생산자 스레드 생성
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        int *thread_id = malloc(sizeof(int));
        *thread_id = i + 1;
        pthread_create(&producer_threads[i], NULL, producer, thread_id);
    }

    // 소비자 스레드 생성
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        int *thread_id = malloc(sizeof(int));
        *thread_id = i + 1;
        pthread_create(&consumer_threads[i], NULL, consumer, thread_id);
    }

    // 모든 스레드가 끝날 때까지 대기
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producer_threads[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_not_full);
    pthread_cond_destroy(&cond_not_empty);

    printf("\nAll tasks completed!\n");

    return 0;
}
