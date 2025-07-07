#include <stdio.h>
#include <stdlib.h>

#define mod 1000003

int n,s,e,t,len;

void mul(int** ans, int** a, int** b){
    long long** temp = (long long**)malloc(sizeof(long long*) * len);
    for(int i = 0 ; i < len ; i++){
        temp[i] = (long long*)calloc(len, sizeof(long long));
    }
    for(int i = 0 ; i < len ; i++){
        for(int j = 0 ; j < len ; j++){
            for(int k = 0 ; k < len ; k++){
                temp[i][j] += (long long)a[i][k] * b[k][j];
                temp[i][j] %= mod;
            }
        }
    }
    for(int i = 0 ; i < len ; i++){
        for(int j = 0 ; j < len ; j++){
            ans[i][j] = (int)temp[i][j];
        }
    }
    for (int i = 0; i < len; i++) {
        free(temp[i]);
    }
    free(temp);
}

void power(int** ans, int** matrix, int t){
    while(t>0){
        if(t&1) {
            mul(ans, ans, matrix);
        }
        mul(matrix, matrix, matrix);
        t >>= 1;
    }
}

int main(){
    scanf("%d %d %d %d",&n,&s,&e,&t);

    len = 5 * n;

    int** matrix = (int**)malloc(sizeof(int*)*len);
    int** ans = (int**)malloc(sizeof(int*)*len);

    for(int i = 0 ; i < len ; i++) {
        matrix[i] = (int*)calloc(len,sizeof(int));
        ans[i] = (int*)calloc(len,sizeof(int));
        ans[i][i] = 1;
    }

    for(int i = 0 ; i < n ; i++){
        for(int j = 1 ; j < 5 ; j++){
            matrix[i*5+j][i*5+j-1] = 1;
        }
    }

    for(int i = 0 ; i < n ; i++){
        char temp[n];
        scanf("%s",temp);
        for(int j = 0 ; j < n ; j++){
            int w = temp[j] - '0';;
            if(w == 0) continue;
            matrix[i*5][j*5+w-1] = 1;
        }
    }

    power(ans, matrix, t);

    printf("%d\n",ans[(s-1)*5][(e-1)*5]);
    for(int i = 0 ; i < len ; i++){
        free(matrix[i]);
        free(ans[i]);
    }
    free(matrix);
    free(ans);

    return 0;
}