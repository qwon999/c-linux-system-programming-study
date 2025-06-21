#include <stdio.h>
#include <stdlib.h>

int main() {
    // 1. 힙에 int 크기(4바이트)의 공간을 할당하고, 그 주소를 dynamic_var에 저장
    int *dynamic_var = (int*)malloc(sizeof(int));

    // 만약 할당에 실패했으면 프로그램 종료
    if (dynamic_var == NULL) {
        printf("메모리 할당 실패!\n");
        return 1;
    }

    // 2. 할당받은 힙 공간에 값 100을 저장
    *dynamic_var = 100;

    printf("--- 포인터 완전 정복 ---\n");

    // 포인터 변수 '자체'의 주소 (스택 주소)
    printf("1. &dynamic_var (포인터 변수의 주소)   : %p\n", &dynamic_var);

    // 포인터 변수가 '값'으로 가지고 있는 주소 (힙 주소)
    printf("2.  dynamic_var (가리키고 있는 힙 주소) : %p\n", dynamic_var);

    // 포인터가 가리키는 힙 주소로 찾아가서 읽은 '실제 데이터'
    printf("3. *dynamic_var (힙 주소에 저장된 값)   : %d\n", *dynamic_var);

    // 4. 할당받은 힙 메모리 반납
    free(dynamic_var);

    return 0;
}