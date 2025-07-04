# Day1 학습 정리: C언어의 심장 - 메모리와 포인터

## 🎯 학습 목표

* C 코드의 실행 파일 변환 과정 이해.
* 프로그램의 메모리 구조(Code, Data, BSS, Heap, Stack) 파악 및 변수 배치 방식 설명 가능.
* 포인터를 '메모리 주소를 다루는 도구'로 정의하고, 포인터 변수와 그 변수가 가리키는 값을 명확히 구분하여 사용 가능.
* 동적 메모리 할당의 필요성 이해 및 `malloc`, `free`의 책임감 있는 사용.

---

## 1. 컴파일의 여정: 코드에서 실행 파일까지

자바의 `javac` 명령어 뒤에 숨겨져 있던 과정을 C에서는 4단계로 나눌 수 있음.

1.  **전처리 (Preprocessing):** 소스 코드(`.c`)에서 `#include`, `#define` 같은 지시문을 처리하여 확장된 소스 코드(`.i`) 생성.
2.  **컴파일 (Compilation):** 전처리된 코드(`.i`)를 어셈블리 코드(`.s`)로 변환. 이 단계에서 주로 문법 오류 검사.
3.  **어셈블 (Assembly):** 어셈블리 코드(`.s`)를 컴퓨터가 직접 읽을 수 있는 기계어(목적 코드, `.o`)로 변환.
4.  **링크 (Linking):** 생성된 목적 파일(`.o`)과 프로그램에 필요한 라이브러리(예: `printf` 함수가 담긴 C 표준 라이브러리)를 연결하여 최종 실행 파일 생성.

**[실습 확인]** `gcc -v -save-temps main.c -o main` 명령어를 통해 각 단계의 중간 산출물을 직접 확인하며, 소스 코드의 변환 과정 파악함.

---

## 2. 프로그램의 지도: 메모리 구조

프로그램 실행 시, 변수와 함수는 OS에 의해 약속된 메모리 구역에 배치됨.

| 영역                 | 설명                                   | 주요 내용                     |
| :------------------- | :------------------------------------- | :---------------------------- |
| **코드 (Code/Text)** | 실행할 기계어 코드. 읽기 전용.         | 함수 본체, `const` 상수       |
| **데이터 (Data)** | 초기값이 있는 전역/정적 변수.          | `int global_var = 10;`        |
| **BSS** | 초기값이 없는 전역/정적 변수.          | `int global_var;` (시작 시 0으로 초기화됨) |
| **힙 (Heap)** | 프로그래머가 동적으로 할당/해제하는 공간. | `malloc()`, `free()`          |
| **스택 (Stack)** | 함수 호출 시 지역변수, 매개변수 저장.  | 함수가 끝나면 사라짐.         |

**[실습 확인]** `memory_layout.c` 실습을 통해 각 영역에 선언된 변수들의 주소를 출력. 실제로 코드, 데이터, BSS 영역은 정적 주소 공간에, 힙과 스택은 동적 주소 공간에 위치하며, 스택은 높은 주소에서 낮은 주소로 자라나는 것을 확인함.

---

## 3. 포인터: 메모리를 직접 제어하는 열쇠

### 3.1. 포인터의 본질

포인터는 '어려운 문법'이 아니라, **"메모리의 주소 값을 저장하는 변수"** 임.

### 3.2. 포인터의 두 얼굴: `*`

C언어에서 `*` 기호는 사용 위치에 따라 의미가 완전히 다름.

* **선언 시:** "이 변수는 포인터 변수다" 라는 **타입 명시자**.
    ```c
    int *p; // p는 int가 아니라, int형 변수의 '주소'를 담는 변수임.
    ```
* **사용 시:** "이 포인터가 가리키는 주소로 찾아가서 실제 값을 가져와라" 라는 **역참조(Dereference) 연산자**.
    ```c
    *p = 10; // p에 저장된 주소로 찾아가서, 그 공간에 10을 대입함.
    ```

### 3.3. 동적 메모리 할당과 `malloc`

`malloc`은 프로그램 실행 중 **힙(Heap) 영역**에서 필요한 만큼 메모리를 빌려오는 함수임.

* `int *p = (int*)malloc(sizeof(int));`
    * `malloc(sizeof(int))`: 힙 영역에 `int` 크기(4바이트)의 공간을 할당하고, 그 시작 주소 반환.
    * `int *p`: `p`라는 포인터 변수 자체는 **스택 영역**에 생성됨.
    * `=`: `malloc`이 반환한 **힙 주소**를 스택에 있는 `p`에 **값으로 저장**함.

**[핵심 정리]**
| 표현식       | 읽는 법                 | 의미                                    | 저장된 위치 |
| :----------- | :---------------------- | :-------------------------------------- | :---------- |
| **`&p`** | "p의 주소"              | 포인터 변수 `p` 자체의 주소             | **스택** |
| **`p`** | "p"                     | `p`가 값으로 가지고 있는 주소           | **힙** |
| **`*p`** | "p가 가리키는 곳"       | `p`가 가리키는 곳에 저장된 실제 데이터  | **힙** |

> **중요:** `malloc`으로 빌린 메모리는 반드시 `free(p)`를 통해 직접 반납해야 함. 그렇지 않으면 **메모리 누수(Memory Leak)** 발생.

### 3.4. 함수와 포인터: Call by Value의 한계 극복

C언어는 항상 **값에 의한 호출(Call by Value)** 만 지원함. 함수에 변수를 넘기면 값이 '복사'되어 전달될 뿐, 원본 수정 불가.

`swap` 함수 실습을 통해, 함수 외부 변수를 수정하기 위해서는 해당 변수의 **주소(포인터)를 넘겨줘야 함**을 확인. 함수는 넘겨받은 주소를 통해 원본 변수의 위치를 찾아가 값을 직접 변경 가능. 이것이 C에서 **참조에 의한 호출(Call by Reference)을 흉내 내는** 방법임.

---

## 📝 주간 회고

1주차 학습을 통해, C언어는 단순히 코드를 작성하는 것을 넘어 컴퓨터의 근본적인 동작 방식과 메모리 구조 위에서 동작한다는 것을 체감함. 특히, 포인터는 메모리 주소를 직접 다루는 강력한 도구이며, 모든 메모리 접근의 기반이 됨을 이해. 자바와 같은 고수준 언어가 제공하는 추상화와 자동화(GC 등)가 얼마나 많은 것들을 숨기고 있었는지 깨닫는 계기가 됨.
