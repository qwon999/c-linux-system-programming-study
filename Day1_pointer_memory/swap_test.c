#include <stdio.h>

// main의 a와 b에 접근할 수 없으므로, a와 b의 '주소'를 받아온다.
void swap(int *pa, int *pb) {
    printf("  swap 함수 안: 교환 전 *pa=%d, *pb=%d\n", *pa, *pb);
    int temp = *pa; // pa가 가리키는 주소의 값(a의 값)을 temp에 저장
    *pa = *pb;      // pb가 가리키는 주소의 값(b의 값)을 pa가 가리키는 주소에 저장
    *pb = temp;     // temp의 값을 pb가 가리키는 주소에 저장
    printf("  swap 함수 안: 교환 후 *pa=%d, *pb=%d\n", *pa, *pb);
}

int main() {
    int a = 10;
    int b = 20;

    printf("main 함수 안: 교환 전 a=%d, b=%d\n", a, b);

    // a와 b의 값을 바꾸기 위해, a와 b의 '메모리 주소'를 넘겨준다.
    swap(&a, &b);

    printf("main 함수 안: 교환 후 a=%d, b=%d\n", a, b);

    return 0;
}
