#include <stdio.h>
#include <unistd.h> // 리눅스 시스템 콜을 위한 헤더

int main() {
    // 이 코드는 macOS가 아닌, Docker 안의 리눅스에서 실행됩니다!
    printf("Hello from Linux Container!\n");
    printf("My Process ID is: %d\n", getpid());
    return 0;
}

