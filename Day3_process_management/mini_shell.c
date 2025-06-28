#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
#include <string.h>

#define BUF_SIZE 256

int main(){
    char cmd_buf[BUF_SIZE];

    while(1){
        printf("shell> ");
        fgets(cmd_buf, BUF_SIZE, stdin);
        cmd_buf[strcspn(cmd_buf, "\n")] = '\0';

        if(strcmp(cmd_buf, "exit") == 0) break;

        pid_t pid = fork();

        if(pid<0){
            perror("fork error");
            return 1;
        }else if(pid == 0){
            char* args[(BUF_SIZE>>1) + 1]; // 최악의 경우 a b c d ~
            char* ptr = strtok(cmd_buf, " ");
            int i = 0;
            while(ptr != NULL){
                args[i++] = ptr;
                ptr = strtok(NULL, " ");
            }
            args[i] = NULL; // execvp에게 배열의 끝을 NULL로 알려줘야함.
            execvp(args[0], args);

            perror("execvp error");
            return 1;
        }else{
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}