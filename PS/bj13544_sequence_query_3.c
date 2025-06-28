#include <stdio.h>
#include <stdlib.h>

// --- 빠른 입력을 위한 구현부 ---
#define BUF_SIZE (1 << 20) // 1MB 버퍼
char in_buf[BUF_SIZE];
char* in_ptr = in_buf + BUF_SIZE;

static inline char read_char() {
    if (in_ptr == in_buf + BUF_SIZE) {
        fread(in_buf, 1, BUF_SIZE, stdin);
        in_ptr = in_buf;
    }
    return *in_ptr++;
}

static inline int read_int() {
    int res = 0;
    char c = read_char();
    while (c <= ' ') {
        c = read_char();
    }
    do {
        res = res * 10 + (c - '0');
    } while ((c = read_char()) >= '0' && c <= '9');

    return res;
}

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

int counter(int node, int v){
    int l = 0,r = (st+node)->size;

    while(l<r){
        int m = (l+r) >> 1;
        if(*((st+node)->arr+m) <= v) l = m+1;
        else r = m;
    }
    return (st+node)->size-l;

}

int query(int node, int s, int e, int l, int r, int v){
    if(s>r || e<l) return 0;
    if(l<=s && e<=r) return counter(node, v);
    int m = (s+e) >> 1;
    return query(node<<1,s,m,l,r,v) + query((node<<1)+1,m+1,e,l,r,v);
}

int main(){
    int N,Q;
    N = read_int();
    int size = 2;
    while(size < N) size <<= 1;
    size <<= 1;

    st = (TreeNode*)malloc(sizeof(TreeNode)*size);
    arr = (int*)malloc(sizeof(int)*(N+1));

    for(int i = 1 ; i <= N ; i++) *(arr+i) = read_int();

    build(1,1,N);
    free(arr);

    Q = read_int();
    int ans=0;
    int i,j,k;
    while(Q--){
        i=read_int()^ans;
        j=read_int()^ans;
        k=read_int()^ans;
        ans = query(1,1,N,i,j,k);
        printf("%d\n",ans);
    }
    free(st);
    return 0;
}