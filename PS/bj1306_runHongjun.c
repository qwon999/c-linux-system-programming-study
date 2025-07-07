#include <stdio.h>
#include <stdlib.h>


int* st;
int* arr;

void build(int node, int s, int e){
    if(s==e) {
        *(st+node) = *(arr+s);
        return;
    }
    int m = (s+e)/2;
    build(node*2,s,m);
    build(node*2+1,m+1,e);
    *(st+node) = *(st+(node*2)) > *(st+(node*2)+1) ? *(st+(node*2)) : *(st+(node*2)+1);
}

int query(int node, int s, int e, int l, int r){
    if(s>r || e<l) return 0;
    if(l<=s && e<=r) return *(st+node);
    int m = (s+e)/2;
    int left = query(node*2,s,m,l,r);
    int right = query(node*2+1,m+1,e,l,r);
    return left > right ? left : right;
}

int main(){
    int N,M;
    scanf("%d %d",&N,&M);

    int len = 1;
    while(len < N) len <<= 1;
    len <<= 1;
    st = (int*)malloc(sizeof(int)*len);
    arr = (int*)malloc(sizeof(int)*(N+1));

    for(int i = 1 ; i <= N ; i++) scanf("%d",arr+i);


    build(1,1,N);

    free(arr);


    for (int mid = M; mid <= N - M + 1; mid++) {
        int start = mid - (M - 1);
        int end = mid + (M - 1);

        int ans = query(1, 1, N, start, end);
        printf("%d\n", ans);
    }
    free(st);
    return 0;

}