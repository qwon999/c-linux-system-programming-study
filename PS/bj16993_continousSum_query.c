#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int l;
    int r;
    int c;
    int a;
}Node;


Node* st;
int* arr;

void build(int node, int s, int e){
    if(s==e){
        (st+node)->l = (st+node)->r = (st+node)->c = (st+node)->a = *(arr+s);
        return;
    }
    int m = (s+e)>>1;
    build(node<<1,s,m);
    build((node<<1)+1,m+1,e);
    Node* lp = (st+(node<<1));
    Node* rp = (st+(node<<1)+1);
    (st+node)->l = (lp)->l > (lp)->a + (rp)->l ? (lp)->l : (lp)->a + (rp)->l;
    (st+node)->r = (rp)->r > (lp)->r + (rp)->a ? (rp)->r : (lp)->r + (rp)->a;
    int temp_c = (lp)->c > (rp)->c ? (lp)->c : (rp)->c;
    (st+node)->c = temp_c > (lp)->r + (rp)->l ? temp_c : (lp)->r + (rp)->l;
    (st+node)->a = (lp)->a + (rp)->a;
}

Node query(int node, int s, int e, int i, int j){
    if(s>j || e<i) {
        Node temp;
        temp.l = temp.r = temp.c = -1000000001;
        temp.a = 0;
        return temp;
    }
    if(i<=s && e<=j) return *(st+node);
    int m = (s+e) >> 1;
    Node left = query(node<<1,s,m,i,j);
    Node right = query((node<<1)+1,m+1,e,i,j);
    Node temp;
    temp.l = left.l > left.a + right.l ? left.l : left.a + right.l;
    temp.r = right.r > left.r + right.a ? right.r : left.r + right.a;
    int tc = left.c > right.c ? left.c : right.c;
    temp.c = tc > left.r + right.l ? tc : left.r + right.l;
    temp.a = left.a + right.a;
    return temp;
}

int main(){
    int N,M;
    scanf("%d",&N);
    int len = 2;
    while(len < N) len <<= 1;
    len <<= 1;
    st = (Node*)malloc(sizeof(Node)*len);
    for(int i = 1 ; i < len ; i++) (st+i)->l = (st+i)->r = (st+i)->c = (st+i)->a = -1000000001;

    arr = (int*)malloc(sizeof(int)*(N+1));


    for(int i = 1 ; i <= N ; i++) scanf("%d",arr+i);

    build(1,1,N);

    free(arr);


//    printf("메모리 할당 완료. PID를 확인하고 Enter를 누르세요...\n");
//    getchar(); // 사용자가 Enter를 누를 때까지 대기

    scanf("%d",&M);

    int i,j;

    while(M--){
        scanf("%d%d",&i,&j);
        Node ans = query(1,1,N,i,j);
        printf("%d\n",ans.c);
    }

    return 0;
}