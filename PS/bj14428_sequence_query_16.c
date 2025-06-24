#include <stdio.h>
#include <stdlib.h>


int* st1 ;
const int len = 262144;

void build(int node, int s, int e, int* arr) {
    if (s == e) {
        *(st1 + node) = *(arr + s);
        *(st1 + node + len) = s;
        return;
    }

    int m = (s + e) >> 1;
    build(node << 1, s, m, arr);
    build((node << 1) + 1, m + 1, e, arr);

    if (*(st1 + (node << 1)) <= *(st1 + ((node << 1) + 1))) {
        *(st1 + node) = *(st1 + (node << 1));
        *(st1 + node + len) = *(st1 + (node << 1) + len);
    } else {
        *(st1 + node) = *(st1 + ((node << 1) + 1));
        *(st1 + node + len) = *(st1 + ((node << 1) + 1) + len);
    }
}

void update(int node, int s, int e, int idx, int val){
    if(s==e){
        *(st1+node) = val;
        *(st1+node+len) = idx;
        return;
    }
    int m = (s+e) >> 1;
    if(idx <= m) update(node<<1,s,m,idx,val);
    else update ((node<<1)+1,m+1,e,idx,val);

    if(*(st1+(node<<1)) <= *(st1+(node<<1)+1)){
        *(st1+node) = *(st1+(node<<1));
        *(st1+node+len) = *(st1+(node<<1)+len);
    }else{
        *(st1+node) = *(st1+(node<<1)+1);
        *(st1+node+len) = *(st1+(node<<1)+1+len);
    }
}

int query(int node, int s, int e, int l, int r){
    if(s>r || e<l) return 0;
    if(l<=s && e<=r) return node;

    int m = (s+e) >> 1;

    int left = query(node<<1,s,m,l,r);
    int right = query((node<<1)+1,m+1,e,l,r);

    return *(st1+(left)) <= *(st1+(right)) ? left : right;
}


int main(){
    int N;
    scanf("%d",&N);

    st1 = (int*)malloc(sizeof(int)*len*2+1);

    for (int i = 0; i <= len; i++) {
        *(st1 + i) = 1000000001;
    }

    int* arr = (int*)malloc(sizeof(int) * (N + 1));
    for (int i = 1; i <= N; i++) {
        scanf("%d", arr + i);
    }

    build(1, 1, N, arr);

    free(arr);

    int t,a,b;


    int M;
    scanf("%d",&M);


    while(M-->0){
        scanf("%d%d%d",&t,&a,&b);
        if(t==1){
            update(1,1,N,a,b);
        }else{
            int ans = query(1,1,N,a,b);
            printf("%d\n",*(st1+ans+len));
        }
    }

    free(st1);

    return 0;


}