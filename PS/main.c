#include <stdio.h>
#include <stdlib.h>


int** arr;
int* nums;

int checker(int n, int depth) {
    printf("%d\n", depth);
    if (depth == 81) {
        for(int i=0;i<9;i++) {
            for(int j=0;j<9;j++) {
                printf("%d ", arr[i][j]);
            }
            printf("\n");
        }
        return 1;
    }
    int i = n / 9;
    int j = n % 9;
    printf("%d ", i*10+j);
    while (1) {
        printf("%d ", arr[i][j]);
        if (arr[i][j] == 0) break;
        printf("! " );
        n++;
        i = n / 9;
        j = n % 9;
    }
    printf("%d %d \n", i,j);

    int temp[10];
    for(int i=1;i<=9;i++) {
        temp[i] = 0;
    }
    for (int r = 0 ; r < 9 ; r++) {
        temp[arr[i][r]] ++;
        temp[arr[r][j]] ++;
    }

    int ii = i / 3;
    int jj = j / 3;
    for (int r = ii*3 ; r<ii*3+3 ;r++) {
        for (int c = jj*3 ; c<jj*3+3 ;c++) {
            printf("%d %d \n",r,c);
            temp[arr[r][c]] ++;
        }
    }
    for (int k = 1 ; k <= 9 ; k++) {

        if (temp[k]>0) {
            printf("%d ", temp[k]);
            printf("%d\n", k);
            continue;
        }

        printf("!\n ");
        arr[i][j] = k;
        checker(n+1, depth+1);
        arr[i][j] = 0;
    }
    free(temp);
}

int main() {
    arr = (int**)malloc(sizeof(int*)*9);
    nums = (int*)malloc(sizeof(int)*10);
    int depth = 0;
    for(int i=1; i<=9; i++) nums[i] = 9;
    for(int i=0;i<9;i++) {
        arr[i] = (int*)malloc(sizeof(int)*9);
        for(int j=0;j<9;j++) {
            int temp;
            scanf("%d",&temp-1);
            arr[i][j] = temp;
            if (temp>0) {
                depth++;
                nums[depth]++;
            }
        }
    }
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }


    checker(0,depth);



}