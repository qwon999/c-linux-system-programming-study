#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include <wait.h>

int main(){
    pid_t pid = fork();

    if(pid<0){
        perror("fork error");
        return 1;
    }else if(pid == 0){
        printf("child(PID : %d): ls -al 명령어로 변신\n",getpid());
        execlp("ls","ls","-al",NULL);
        perror("execlp error");
        return 1;
    }else{
        wait(NULL);
        printf("parent(PID:%d) : child(PID:%d)의 작업을 기다리고 종료\n",getpid(),pid);
    }
    return 0;
}