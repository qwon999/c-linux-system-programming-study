#include <stdio.h>
#include <stdlib.h> // malloc, free를 위해 필요

int main(){
    int N;
    scanf("%d", &N);

    // VLA 대신 동적 할당을 사용
    int *arr = (int*)malloc(sizeof(int) * N);
    if (arr == NULL) return 1; // 메모리 할당 실패 시 종료

    // 포인터를 이용한 입력
    for(int i = 0 ; i < N ; i++){
        // arr[i] 대신 *(arr + i)를 사용.
        // &arr[i]와 (arr + i)는 같은 주소를 가리킴.
        scanf("%d", arr + i);
    }

    int min = 1000000;
    int max = -1000000;

    // 포인터 변수를 직접 사용하여 배열 순회
    int *p;
    for(p = arr; p < arr + N; p++){ // 포인터 p가 배열의 끝에 도달할 때까지
        if(*p < min) min = *p;   // p가 가리키는 실제 값(*p)을 비교
        if(*p > max) max = *p;
    }

    printf("%d %d", min, max);

    free(arr); // 동적 할당한 메모리는 해제.
    return 0;
}