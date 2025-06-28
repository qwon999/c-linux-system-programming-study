#include<stdio.h>
#include<unistd.h> // fork(), getpid(), getppid()
#include<sys/types.h> //pid_t

int main(){
    pid_t pid;
    int data = 10;

    printf("===Before fork====\n");
    printf("Parent PID: %d\n", getpid());

    pid = fork(); // 이 순간, 프로세스 두개로 나뉨

    if(pid<0){ // fork 실패 시
        perror("fork");
        return 1;
    }else if(pid == 0){
        printf("\n===Child Process====\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
//        data++;
        printf("Child Data: %d\n", data);
    }else {
        printf("\n===Parent Process====\n");
        sleep(1); // 부모를 1초간 잠재운다! // 병렬성을 테스트하기위한 라인.
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
        data++;
        printf("Parent Data: %d\n", data);
    }

    printf("\n===After fork====\n");
    printf("End PID: %d\n", getpid());
    return 0;
}