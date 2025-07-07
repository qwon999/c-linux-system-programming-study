#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000000

typedef struct {
    int left;
    int right;
    int max;
    int sum;
}Node;

Node* st;
int* arr;
int U,V;



Node merge(Node left, Node right){
    Node temp;
    temp.left = left.left > right.left + left.sum? left.left : right.left + left.sum;
    temp.right = right.right > left.right + right.sum ? right.right : left.right + right.sum;
    int tm = left.max > right.max ? left.max : right.max;
    temp.max = tm > left.right + right.left ? tm : left.right + right.left;
    temp.sum = left.sum + right.sum;
    return temp;
}

void build(int node, int s, int e){
    if(s==e){
        (st+node)->left = (st+node)->right = (st+node)->max = (st+node)->sum = *(arr+s)*U+V;
        return;
    }
    int m = (s+e)>>1;
    build(node<<1,s,m);
    build((node<<1)+1,m+1,e);
    *(st+node) = merge(*(st+(node<<1)), *(st+(node<<1)+1));
}

Node query(int node, int s, int e, int l, int r){
    if(s>r || e<l) return (Node){-MAX,-MAX,-MAX,0};
    if(l<=s && e<=r) return *(st+node);
    int m = (s+e)>>1;
    Node left = query(node<<1,s,m,l,r);
    Node right = query((node<<1)+1,m+1,e,l,r);
    return merge(left,right);
}

void update(int node, int s, int e, int idx, int val){
    if(s==e){
        (st+node)->left = (st+node)->right = (st+node)->max = (st+node)->sum = val;
        return;
    }
    int m = (s+e)>>1;
    if(idx <= m) update(node<<1,s,m,idx,val);
    else update((node<<1)+1,m+1,e,idx,val);
    *(st+node) = merge(*(st+(node<<1)), *(st+(node<<1)+1));
}

// 값에 U를 곱하고 V더하면 됨 -> 쿼리 때 무조건 V만 빼주면 됨.
int main(){
    int N,Q;
    scanf("%d %d %d %d",&N,&Q,&U,&V);
    // 트리 사이즈
    int len = 2;
    while(len < N) len <<= 1;
    len <<= 1;
    // 트리 메모리 할당
    st = (Node*)malloc(sizeof(Node)*len);
    // 초기 배열 메모리 할당 및 초기화
    arr = (int*)malloc(sizeof(int)*(N+1));
    for(int i = 1 ; i <= N ; i++) scanf("%d",arr+i);
    // 트리 생성
    build(1,1,N);

    while(Q--){
        int c,a,b;
        scanf("%d %d %d",&c,&a,&b);
        if(c==0){
            Node ans = query(1,1,N,a,b);
            printf("%d\n",ans.max-V);
        }else{
            update(1,1,N,a,b*U+V);
        }
    }

    return 0;
}