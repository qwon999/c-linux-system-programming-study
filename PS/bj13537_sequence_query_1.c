#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int* arr;
    int size;
}TreeNode;

int* init_arr;
TreeNode* st;
int len = 262144;

int upper_bound(int* arr, int n, int tgt){
    int l = 0, r = n;
    while(l<r){
        int m = (l+r) >> 1;
        if(arr[m]>tgt) r = m;
        else l = m+1;
    }
    return l;
}

void build(int node, int s, int e){
    if(s==e){
        (st+node)->arr = (int*)malloc(sizeof(int));
        (st+node)->size = 1;
        *((st+node)->arr) = *(init_arr+s);
        return;
    }
    int m = (s+e) >> 1;


    build(node<<1,s,m);
    build((node<<1)+1,m+1,e);

    TreeNode* lp = (st+(node<<1));
    TreeNode* rp = (st+(node<<1)+1);

    (st+node)->size = (lp)->size + (rp)->size;
    (st+node)->arr = (int*)malloc(sizeof(int)*(st+node)->size);

    // 포인터 병합 알고리즘
    int i = 0, j = 0, k = 0;
    while(i<lp->size && j<rp->size){
        if(*(lp->arr+i) < *(rp->arr+j)){
            *((st+node)->arr+k) = *(lp->arr+i);
            i++;
        }else{
            *((st+node)->arr+k) = *(rp->arr+j);
            j++;
        }
        k++;
    }
    while(i<lp->size){
        *((st+node)->arr+k) = *(lp->arr+i);
        i++;
        k++;
    }
    while(j<rp->size){
        *((st+node)->arr+k) = *(rp->arr+j);
        j++;
        k++;
    }
}

int query(int node, int s, int e, int l, int r, int v){
    if(r<s || l>e) return 0;
    if(l<=s && e<=r){
        return (st+node)->size-upper_bound((st+node)->arr, (st+node)->size, v);
    }
    int m = (s+e) >> 1;
    int left = query(node<<1,s,m,l,r,v);
    int right = query((node<<1)+1,m+1,e,l,r,v);
    return left + right;
}


int main(){
    int N, M;
    scanf("%d",&N);
    init_arr = (int*)malloc(sizeof(int)*(N+1));
    for(int i = 1 ; i <= N ; i++){
        scanf("%d",init_arr+i);
    }

    st = (TreeNode*)malloc(sizeof(TreeNode)*len);
    build(1,1,N);

    printf("메모리 할당 완료. PID를 확인하고 Enter를 누르세요...\n");
    getchar(); // 사용자가 Enter를 누를 때까지 대기

    scanf("%d",&M);
    while(M--){
        int l,r,v;
        scanf("%d%d%d",&l,&r,&v);
        printf("%d\n",query(1,1,N,l,r,v));
    }
    return 0;
}