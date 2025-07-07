#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(){
    int N,M;
    scanf("%d %d",&N,&M);
    int *arr = (int*)malloc(sizeof(int)*N);
    for(int i = 0 ; i < N ; i++) scanf("%d",arr+i);

    long long l = 1;
    long long r = 1000000000;
    r*=M;

    while(l<=r){
        bool flag = true;
        long long mid = (l+r) >> 1;
        int cnt = 0;
        for(int i = 0 ; i < N ; i++){
            cnt += mid/(*(arr+i));
            if(cnt < 0||cnt>=M) {
                r = mid-1;
                flag = false;
                break;
            }
        }
        if(flag) l = mid+1;
    }


    printf("%lld\n",r+1);
    free(arr);
    return 0;
}