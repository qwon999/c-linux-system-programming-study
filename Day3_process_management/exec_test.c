#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    pid_t pid = fork();

    if(pid < 0){
        perror("fork error");
        return 1;
    }else if(pid == 0){
        printf("child (PID : %d) : ls -al 명령어로 변신\n",getpid());


        // lp : l 은 인자를 리스트로 받겠다. p 는 PATH 환경변수에서 명령어를 찾는다.
        // 첫번째 ls : 실행할 파일 이름
        // 두번째 ls : argv[0]에 해당
        // -al : argv[1]에 해당
        // NULL : 인자리스트의 끝을 의미
        execlp("ls","ls","-al",NULL);

        // 만약 exec가 성공하면 아래 코드는 실행되지 않음
        // 왜? 프로세스의 메모리 공간이 ls프로그램으로 덮어씌워졌기 때문.
        // 만약 실패 시 perror 실행
        perror("exec error");
        return 1;
    } else{
        printf("parent (PID : %d) : child(PID : %d)를 만들고 바로 종료\n",getpid(),pid);
        // wait()을 호출하지 않았으므로, 자식이 끝나기 전에 부모가 먼저 종료될 수 있음
        // 해당 경우 자식은 고아가 되어 PID 1의 자식으로 입양됨
    }
    return 0;
}