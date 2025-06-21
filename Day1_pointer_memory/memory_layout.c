//코드(Code/Text) 영역: 실행할 기계어 코드. 읽기 전용.
//데이터(Data) 영역: 초기화된 전역/정적 변수.
//BSS 영역: 초기화되지 않은 전역/정적 변수. (프로그램 시작 시 0으로 초기화됨)
//힙(Heap) 영역: 프로그래머가 동적으로 할당하는 메모리 공간 (malloc). 낮은 주소에서 높은 주소로 자라남.
//스택(Stack) 영역: 함수 호출 시 사용되는 지역 변수, 매개변수, 리턴 주소. 높은 주소에서 낮은 주소로 자라남.

//Output
//1. 코드 영역 (함수 주소): 		0x100fc7d00
//2. 데이터 영역 (초기화된 전역변수): 	0x100fcc000
//3. 데이터 영역 (초기화된 정적변수): 	0x100fcc004
//4. BSS 영역 (초기화X 전역변수): 	0x100fcc00c
//5. BSS 영역 (초기화X 정적변수): 	0x100fcc008
//6. 힙 영역 (동적 할당): 		0x6000036c8030
//7. 스택 영역 (main의 지역변수): 	0x16ee3b018
//- 함수 내부 지역 변수 (스택): 	0x16ee3afdc

#include <stdio.h>
#include <stdlib.h>

int global_init_var = 10; // Data영역
int global_uninit_var; // BSS영역
const int const_global_var = 10; // Cods or ROData영역

void function() {
    int local_var = 20;        // 스택(Stack) 영역
    printf("  - 함수 내부 지역 변수 (스택): \t%p\n", &local_var);
}

int main(){
    static int static_init_var = 5; // Data영역
    static int static_uninit_var;   // BSS 영역
    int local_main_var = 30;          // 스택(Stack) 영역
    int *dynamic_var = (int*)malloc(sizeof(int)); // 힙(Heap) 영역

    printf("1. 코드 영역 (함수 주소): \t\t%p\n", &main);
    printf("2. 데이터 영역 (초기화된 전역변수): \t%p\n", &global_init_var);
    printf("3. 데이터 영역 (초기화된 정적변수): \t%p\n", &static_init_var);
    printf("4. BSS 영역 (초기화X 전역변수): \t%p\n", &global_uninit_var);
    printf("5. BSS 영역 (초기화X 정적변수): \t%p\n", &static_uninit_var);
    printf("6. 힙 영역 (동적 할당): \t\t%p\n", dynamic_var);
    printf("7. 스택 영역 (main의 지역변수): \t%p\n", &local_main_var);

    // static_uninit_var 초기화 실행 후 확인 ->  위치 바뀌지 않음
    static_uninit_var = 3;
    printf("8. BSS 영역 (초기화X 정적변수): \t%p\n", &static_uninit_var);

    function();

    free(dynamic_var); // 동적 할당 메모리 해제
    return 0;
}