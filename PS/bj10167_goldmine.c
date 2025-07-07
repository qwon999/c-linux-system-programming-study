#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long left;
    long long right;
    long long max;
    long long sum;
} node;

typedef struct {
    int x;
    int y;
    int w;
} point;

typedef struct {
    int s;
    int i;
} temp;

typedef struct {
    int x;
    int w;
} xw;

node* st;
point* arr;
temp* tx;
temp* ty;
temp* ts;


void merge(temp* t, int s, int m, int e){
    for(int i = s ; i <= e ; i++) {
        *(ts+i) = *(t+i);
    }
    int i = s, j = m+1, k = s;
    while(i<=m && j<=e){
        if((ts+i)->s <= (ts+j)->s){
            *(t+k++) = *(ts+i++);
        }
        else{
            *(t+k++) = *(ts+j++);
        }
    }
    while(i<=m){
        *(t+k++) = *(ts+i++);
    }
}

void mergeSort(temp* t, int s, int e){
    if(s<e){
        int m = (s+e)>>1;
        mergeSort(t,s,m);
        mergeSort(t,m+1,e);
        merge(t,s,m,e);
    }
}

node res(node* l, node* r){
    node ret;
    ret.left = l->left > l->sum + r->left ? l->left : l->sum + r->left;
    ret.right = r->right > l->right + r->sum ? r->right : l->right + r->sum;
    long long t_max = l->max > r->max ? l->max : r->max;
    ret.max = t_max > l->right + r->left ? t_max : l->right + r->left;
    ret.sum = l->sum + r->sum;
    return ret;
}

void update(int node, int s, int e, int x, int w){
    if(s==e){
        (st+node)->sum += w;
        (st+node)->left = (st+node)->right = (st+node)->max = (st+node)->sum;

        return;
    }
    int m = (s+e)>>1;
    if(x <= m) update(node<<1,s,m,x,w);
    else update((node<<1)+1,m+1,e,x,w);
    *(st+node) = res(st+(node<<1),st+(node<<1)+1);
}

int N;

int main(){
    scanf("%d",&N);
    arr = (point*)malloc(sizeof(point)*(N+1));
    tx = (temp*)malloc(sizeof(temp)*(N+1));
    ty = (temp*)malloc(sizeof(temp)*(N+1));

    for(int i = 1 ; i <= N ; i++){
        scanf("%d %d %d",&arr[i].x,&arr[i].y,&arr[i].w);
        tx[i].s = arr[i].x;
        ty[i].s = arr[i].y;
        tx[i].i = i;
        ty[i].i = i;
    }

    ts = (temp*)malloc(sizeof(temp)*(N+1));

    mergeSort(tx,1,N);
    mergeSort(ty,1,N);


    free(ts);

    int rank = 1;
    (arr+(tx+1)->i)->x = rank;
    for(int i = 2 ; i <= N ; i++){
        if((tx+i)->s > (tx+i-1)->s) rank++;
        (arr+(tx+i)->i)->x = rank;
    }

    int Nx = rank;

    rank = 1;
    (arr+(ty+1)->i)->y = rank;
    for(int i = 2 ; i <= N ; i++){
        if((ty+i)->s > (ty+i-1)->s) rank++;
        (arr+(ty+i)->i)->y = rank;
    }

    free(tx);
    free(ty);

    int* y_counts = (int*)malloc(sizeof(int)*(rank + 1));

    for(int i = 0; i <= rank; i++) {
        y_counts[i] = 0;
    }

    for (int i = 1; i <= N; i++) {
        *(y_counts+(arr+i)->y)+=1;
    }

    xw** yArr = (xw**)malloc(sizeof(xw*)*(rank + 1));
    for(int i = 1 ; i <= rank ; i++) {
        *(yArr+i) = (xw*)malloc(sizeof(xw)*(y_counts[i]));
    }

    int* y_cidx = (int*)malloc(sizeof(int)*(rank + 1));
    for(int i = 0 ; i <= rank ; i++) {
        y_cidx[i] = 0;
    }
    for(int i = 1 ; i <= N ; i++) {
        int y = (arr+i)->y;
        int x = (arr+i)->x;
        int w = (arr+i)->w;
        int idx = y_cidx[y]++;
        yArr[y][idx].x = x;
        yArr[y][idx].w = w;
    }

    int len = 1;
    while(len < Nx) len <<= 1;
    len <<= 1;

    long long ans = 0;
    st = (node*)malloc(sizeof(node)*len);
    for(int i = 1; i <= rank ; i++) {
        for(int j = 1 ; j < len ; j++) {
            st[j].left = st[j].right = st[j].max = st[j].sum = 0;
        }
        for(int j = i ; j <= rank ; j++) {
            int cnt = y_counts[j];
            for(int k = 0 ; k < cnt ; k++){
                update(1,1,Nx,yArr[j][k].x,yArr[j][k].w);
            }
            ans = ans > st[1].max ? ans : st[1].max;
        }

    }
    printf("%lld\n",ans);
    free(yArr);
    free(y_counts);
    free(y_cidx);
    free(arr);
    free(st);

}