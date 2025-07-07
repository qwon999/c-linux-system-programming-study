#include <stdio.h>
#include <stdlib.h>

int main() {
    int size = 10;

    // 1. 메모리를 할당하고 123이라는 값으로 채웁니다.
    int *arr1 = (int*)malloc(sizeof(int) * size);
    if (arr1 == NULL) return 1;

    printf("arr1의 주소: %p\n", arr1);
    printf("arr1에 123을 채웁니다.\n");
    for (int i = 0; i < size; i++) {
        arr1[i] = 123;
    }

    // 2. 메모리를 해제합니다. (데이터는 그대로 남아있을 수 있음)
    free(arr1);
    printf("arr1 메모리를 해제했습니다.\n\n");

    // 3. 같은 크기로 다시 할당받습니다.
    int *arr2 = (int*)malloc(sizeof(int) * size);
    if (arr2 == NULL) return 1;

    printf("arr2의 주소: %p\n", arr2);
    printf("arr2의 초기 내용을 확인합니다:\n");

    // 4. 내용을 확인하면?
    for (int i = 0; i < size; i++) {
        printf("%d ", arr2[i]); // 이전 데이터인 123이 그대로 출력될 확률이 높음
    }
    printf("\n");

    free(arr2);

    return 0;
}