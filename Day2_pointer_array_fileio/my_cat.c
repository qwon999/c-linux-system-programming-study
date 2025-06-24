#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
    // argc : 커맨드 라인 인자의 개수,
    // argv : 인자 문자열 배열의 포인터

    if(argc != 2){
        fprintf(stderr, "사용법: %s <파일이름>\n",argv[0]);
    }

    int fd = open(argv[1], O_RDONLY);
    if(fd == -1){
        perror("open");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while((bytes_read = read(fd,buffer,BUFFER_SIZE)) > 0){
        if(write(STDOUT_FILENO, buffer, bytes_read) != bytes_read){
            perror("write");
            close(fd);
            return 1;
        }
    }
    close(fd);
    return 0;


}