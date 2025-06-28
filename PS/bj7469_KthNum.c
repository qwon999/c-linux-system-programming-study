#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int* arr;
    int size;
}TreeNode;

TreeNode* st;
int* arr;

void build(int node, int s, int e){
    if(s==e){
        (st+node)->arr = (int*)malloc(sizeof(int));
        (st+node)->size = 1;
        *((st+node)->arr) = *(arr+s);
        return;
    }
    int m = (s+e) >> 1;
    build(node<<1,s,m);
    build((node<<1)+1,m+1,e);

    TreeNode* lp = (st+(node<<1));
    TreeNode* rp = (st+(node<<1)+1);

    (st+node)->size = (lp)->size + (rp)->size;
    (st+node)->arr = (int*)malloc(sizeof(int)*(st+node)->size);

    int i = 0, j = 0, k = 0;
    while(i < lp->size && j < rp->size){
        if(*(lp->arr+i) < *(rp->arr+j)){
            *((st+node)->arr+k++) = *(lp->arr+i++);
        }else{
            *((st+node)->arr+k++) = *(rp->arr+j++);
        }
    }
    while(i < lp->size){
        *((st+node)->arr+k++) = *(lp->arr+i++);
    }
    while(j < rp->size){
        *((st+node)->arr+k++) = *(rp->arr+j++);
    }
}

int upper_bound(int node, int v){
    int l = 0,r = (st+node)->size;
    while(l<r){
        int m = (l+r) >> 1;
        if(*((st+node)->arr+m) <= v) l = m+1;
        else r = m;
    }
    return l;

}

int query(int node, int s, int e, int l, int r, int v){
    if(s>r || e<l) return 0;
    if(l<=s && e<=r) return upper_bound(node, v);
    int m = (s+e) >> 1;
    return query(node<<1,s,m,l,r,v) + query((node<<1)+1,m+1,e,l,r,v);
}

int main(){
    int N,Q;
    scanf("%d%d",&N,&Q);
    int size = 2;
    while(size < N) size <<= 1;
    size <<= 1;

    st = (TreeNode*)malloc(sizeof(TreeNode)*size);
    arr = (int*)malloc(sizeof(int)*(N+1));

    for(int i = 1 ; i <= N ; i++) scanf("%d",arr+i);

    build(1,1,N);
    free(arr);

    int i,j,k;
    int l,r;
    while(Q--){
        scanf("%d%d%d",&i,&j,&k);

        l = -1000000001;
        r = 1000000001;
        int ans = r;

        while(l<=r){
            int m = (l+r) >> 1;
            int temp =query(1,1,N,i,j,m);
            if(temp < k) {
                l = m + 1;
            }
            else {
                ans = m;
                r = m - 1;
            }
        }

        printf("%d\n",ans);
    }
    free(st);
    return 0;
}