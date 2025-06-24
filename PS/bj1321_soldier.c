#include <stdio.h>
#include <stdlib.h>


int* arr;
int* st;

void build(int node, int s, int e){
    if(s==e) {
        *(st+node) = *(arr+s);
        return;
    }
    int m = (s+e)>>1;

    build(node<<1,s,m);
    build((node<<1)+1,m+1,e);

    *(st+node) = *(st+(node<<1)) + *(st+(node<<1) + 1);
}

void update(int node, int s, int e, int idx, int val){
    *(st+node) += val;
    if(s==e) return;

    int m = (s+e) >> 1;
    if(idx <= m) update(node<<1,s,m,idx,val);
    else update((node<<1)+1,m+1,e,idx,val);
}

int query(int node, int s, int e, int val){
    if(s==e) return s;

    int m = (s+e) >> 1;

    if(*(st+(node<<1)) < val) return query((node<<1)+1, m+1, e, val-*(st+(node<<1)));
    else return query(node<<1,s,m,val);
}

int main(){
    int N, M;
    scanf("%d",&N);

    arr = (int*)malloc(sizeof(int)*(N+1));
    st = (int*)malloc(sizeof(int)*1048576);

    for(int i = 1 ; i <= N ; i++) scanf("%d",(arr+i));

    build(1,1,N);

    int t,i,a;
    int ans;

    scanf("%d",&M);

    while(M-->0){
        scanf("%d",&t);
        if(t==1){
            scanf("%d%d",&i,&a);
            update(1,1,N,i,a);
        }else{
            scanf("%d",&i);
            ans = query(1,1,N,i);
            printf("%d\n",ans);
        }
    }

}