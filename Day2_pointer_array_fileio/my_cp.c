#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
    int src_fd, dest_fd;
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];

    // 1. 인자 개수 확인
    // 인자가 3개가 아니면 사용법 출력하고 종료
    if(argc != 3){
        fprintf(stderr, "사용법: %s <원본파일> <대상파일>\n",argv[0]);
        exit(1);
    }

    // 2. 원본파일 열기(읽기 전용)
    src_fd = open(argv[1], O_RDONLY);
    if(src_fd == -1){
        perror("오류(원본파일 열기");
        exit(1);
    }

    // 3. 대상파일 열기(쓰기 전용, 생성, 내용 초기화)
    // O_CREAT: 파일 없으면 새로 생성
    // O_TRUNC: 파일 이미 존재하면 내용 초기화
    // 0644: 생성될 파일의 권한 설정(소유자: 읽기/쓰기, 그룹/기타: 읽기 전용)
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(dest_fd==-1){
        perror("오류(대상파일 열기)");
        close(src_fd);
        exit(1);
    }

    while((bytes_read = read(src_fd, buffer,BUFFER_SIZE)) > 0){
        if(write(dest_fd, buffer, bytes_read) != bytes_read){
            perror("오류(대상파일 쓰기");
            close(src_fd);
            close(dest_fd);
            exit(1);
        }
    }

    if(bytes_read == -1){
        perror("오류(원본파일 읽기)");
        close(src_fd);
        close(dest_fd);
        exit(1);
    }

    close(src_fd);
    close(dest_fd);

    printf("파일 복사 완료\n");

    return 0;

}