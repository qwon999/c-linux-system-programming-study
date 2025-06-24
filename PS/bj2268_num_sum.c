#include <stdio.h>
#include <stdlib.h>


long long* st1 ;
const int len = 2097152;

void update(int node, int s, int e, int idx, int val){
    if(s==e){
        *(st1+node) = val;
        return;
    }
    int m = (s+e) >> 1;
    if(idx <= m) update(node<<1,s,m,idx,val);
    else update ((node<<1)+1,m+1,e,idx,val);
    *(st1+node) = *(st1+(node<<1)) + *(st1+(node<<1)+1);
}

long long query(int node, int s, int e, int l, int r){
    if(s>r || e<l) return 0;
    if(l<=s && e<=r) return *(st1+node);

    int m = (s+e) >> 1;

    long long left = query(node<<1,s,m,l,r);
    long long right = query((node<<1)+1,m+1,e,l,r);

    return left + right;
}


int main(){
    int N,M;
    scanf("%d%d",&N,&M);

    st1 = (long long*)malloc(sizeof(long long)*len);

    int t,a,b;


    while(M-->0){
        scanf("%d%d%d",&t,&a,&b);
        if(t==1){
            update(1,1,N,a,b);
        }else{
            long long ans = 0;
            if(a < b) ans = query(1,1,N,a,b);
            else ans = query(1,1,N,b,a);

            printf("%lld\n",ans);
        }
    }

    free(st1);

    return 0;


}