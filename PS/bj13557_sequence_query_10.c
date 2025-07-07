#include <stdio.h>
#include <stdlib.h>
#define MAX 10000000000

typedef struct {
    long long left;
    long long right;
    long long max;
    long long sum;
}Node;

Node* st;
int* arr;


Node merge(Node left, Node right){
    Node temp;
    temp.left = left.left > right.left + left.sum? left.left : right.left + left.sum;
    temp.right = right.right > left.right + right.sum ? right.right : left.right + right.sum;
    long long t_max = left.max > right.max ? left.max : right.max;
    temp.max = t_max > left.right + right.left ? t_max : left.right + right.left;
    temp.sum = left.sum + right.sum;
    return temp;
}

void build(int node, int s, int e){
    if(s==e){
        (st+node)->left = (st+node)->right = (st+node)->max = (st+node)->sum = *(arr+s);
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
int main(){
    int N,M;
    scanf("%d", &N);
    int len = 2;
    while(len < N) len <<= 1;
    len <<= 1;
    arr = (int*)malloc(sizeof(int)*(N+1));
    st = (Node*)malloc(sizeof(Node)*len);
    for(int i = 1 ; i <= N ; i++) scanf("%d",arr+i);

    // build를 하는데 굳이 필요할까?
//    for(int i = 1; i < len ; i++) (st+i)->left = (st+i)->right = (st+i)->max = (st+i)->sum = -1000000001;

    build(1,1,N);
    free(arr);

    scanf("%d", &M);
    int a,b,c,d;
    while(M--){
        scanf("%d%d%d%d",&a,&b,&c,&d);
        long long ans = 0;
        if(b<c){
            // [b,c]구간
            Node center = query(1,1,N,b,c);
            // [a,b)
            Node left = query(1,1,N,a,b-1);
            Node right = query(1,1,N,c+1,d);
            if(left.right > 0) ans += left.right;
            if(right.left > 0) ans += right.left;
            ans += center.sum;
            printf("%lld\n",ans);
        }else{
            Node center = query(1,1,N,c,b);
            // [a,c)
            Node left = query(1,1,N,a,c-1);
            Node right = query(1,1,N,b+1,d);

            long long s1 = left.right +center.left;
            long long s2 = right.left + center.right;
            long long s3 = left.right+center.sum+right.left;
            long long s4 = center.max;

//            printf("%d %d %d %d\n",s1,s2,s3,s4);

            long long m1 = s1 > s2 ? s1 : s2;
            long long m2 = s3 > s4 ? s3 : s4;
            ans += m1 > m2 ? m1 : m2;
            printf("%lld\n",ans);
        }
    }

    free(st);
    return 0;
}