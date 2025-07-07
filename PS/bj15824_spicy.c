#include<stdio.h>
#include<stdlib.h>
#define mod 1000000007

int* temp;

void merge(int* arr, int s, int m, int e){
    for(int i = s ; i <= e ; i++) temp[i]=arr[i];
    int i = s, j = m+1, k = s;
    while(i<=m && j<=e){
        if(temp[i]<=temp[j]){
            arr[k++] = temp[i++];
        }else{
            arr[k++] = temp[j++];
        }
    }
    while(i<=m){
        arr[k++] = temp[i++];
    }

}

void mergeSort(int* arr, int s, int e){
    if(s<e){
        int m = (s+e)>>1;
        mergeSort(arr,s,m);
        mergeSort(arr,m+1,e);
        merge(arr,s,m,e);
    }
}





int main(){
    int N;
    scanf("%d",&N);
    int* arr = (int*)malloc(sizeof(int)*N);
    int* two = (int*)malloc(sizeof(int)*N);
    *two = 1;
    for(int i = 1 ; i < N ; i++){
        long long t = (long long)*(two+i-1)<<1;
        *(two+i) = (int)(t%mod);
    }
    for(int i = 0 ; i < N ; i++) scanf("%d",arr+i);

    temp = (int*)malloc(sizeof(int)*N);
    mergeSort(arr,0,N-1);
    free(temp);


    long long ans = 0;
    long long pos = 0;
    long long neg = 0;
    for(int i = 0 ; i < N ; i++){
        pos += ((long long)(*(two+i)-1))**(arr+i);
        neg += ((long long)(*(two+N-i-1)-1))**(arr+i);
        pos %= mod;
        neg %= mod;
    }
    ans = (pos%mod + mod - neg%mod)%mod;

    printf("%lld\n",ans);
    free(two);
    free(arr);
    return 0;
}