#include <stdio.h>


int str_len(const char* s){
    int len = 0;
    while(*s != '\0'){
        s++;
        len++;

    }
    return len;
}

void my_str_copy(char *dest, const char *src){
  while(*src != '\0'){
      *dest++ = *src++;
  }
}


int main(){
    char str1[50] = "adsj21lkA90a";
    char str2[50];
    printf("%s의 길이 : %d\n",str1,str_len(str1));

    my_str_copy(str2,str1);

    printf("복사된 문자열: %s\n", str2);
    return 0;
}