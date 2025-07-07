# C언어 및 리눅스 시스템 프로그래밍 학습 레포지토리

C언어 및 리눅스 시스템 프로그래밍 학습과 관련 코드, 프로젝트 기록을 위한 레포지토리.
모든 코드는 Docker 컨테이너 안의 격리된 리눅스(Ubuntu) 환경에서 컴파일 및 실행됨.

## 🚀 개발 환경 설정

프로젝트 코드 빌드 및 실행을 위해 아래 도구가 필요하며, 다음 순서에 따라 환경을 설정함.

### 필수 요구사항

* [Docker Desktop](https://www.docker.com/products/docker-desktop/)
* [CLion](https://www.jetbrains.com/clion/) (또는 원격 개발을 지원하는 다른 에디터)

### 설정 과정

1.  **Git Repository 복제 (Clone)**

    ```bash
    git clone [https://github.com/YourUsername/c-linux-system-programming-study.git](https://github.com/YourUsername/c-linux-system-programming-study.git)
    cd c-linux-system-programming-study
    ```

    *(참고: `YourUsername`은 실제 본인 GitHub 아이디로 변경)*

2.  **개발 환경 Docker 이미지 빌드**

    이 프로젝트는 `Dockerfile`을 사용하여 개발에 필요한 모든 도구(`gcc`, `g++`, `cmake`, `gdb` 등)가 설치된 커스텀 Docker 이미지를 생성함.
    프로젝트 최상위 폴더에서 아래 명령어를 실행하여 이미지 빌드.

    ```bash
    docker build -t my-dev-env .
    ```

    * `my-dev-env` 이름의 로컬 이미지 생성됨.

3.  **CLion 설정**

    1.  CLion 실행 후, 복제한 프로젝트 폴더(`c-linux-system-programming-study`) 열기.
    2.  `Settings/Preferences` > `Build, Execution, Deployment` > `Toolchains`로 이동.
    3.  `+` 버튼을 눌러 `Docker` Toolchain 추가.
    4.  `Image:` 필드에서 빌드한 `my-dev-env` 선택.
    5.  CLion이 이미지 안에서 컴파일러/디버거를 자동으로 찾을 때까지 대기. 모든 항목이 녹색 체크 표시로 바뀌면 `Apply` -> `OK` 클릭.
    6.  `Settings/Preferences` > `Build, Execution, Deployment` > `CMake`로 이동하여, 기본 프로필의 `Toolchain`을 생성한 `Docker` Toolchain으로 설정.

4.  **프로젝트 로드 및 실행**

    * 설정 완료 후, CLion이 자동으로 `CMakeLists.txt` 파일을 읽어 프로젝트를 로드함.
    * 우측 상단 실행 구성(Configuration) 확인 후, 초록색 실행(`▶︎`) 버튼을 눌러 코드 빌드 및 실행.

## 📖 학습 내용 및 바로가기

* **[Day1: C언어의 심장 - 메모리와 포인터](./Day1_pointer_memory/README.md)**
    * 주요 개념: 컴파일 과정, 메모리 구조, 포인터, 동적 할당
    * 구현 코드: `memory_layout.c`, `swap_test.c`

* **[Day2: 포인터와 배열, 파일 시스템의 문](./Day2_pointer_array_fileio/README.md)**
    * 주요 개념: 포인터와 배열의 관계, 파일 디스크립터, 시스템 콜(open, read, write, close)
    * 구현 코드: `my_string_test.c`, `my_cat.c`, `my_cp.c`
  
* **[Day3: 프로세스의 탄생과 죽음](./Day3_process_management/README.md)**
    * 주요 개념: 프로세스의 생명주기(fork, exec, wait)
    * 구현 코드: `fork_test.c`, `exec_text.c`, `wait_test.c`,`mini_shell.c`

* **[Day4: 스레드와 경쟁 조건](./Day4_thread_race_condition/README.md)**
    * 주요 개념: 스레드의 생명주기, 스레드의 경쟁조건
    * 구현 코드: `pthread.c`, `race_condition_test.c`

* *(학습 진행에 따라 계속 추가 예정)*

---
이 문서는 노력과 지식의 역사를 담는 소중한 기록임.
