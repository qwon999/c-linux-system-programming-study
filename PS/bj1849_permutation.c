#include <stdio.h>
#include <stdlib.h>

int* st;
int* ans;

void init(int node, int s, int e){
    if(s==e){
        *(st + node) = 1;
        return;
    }
    int m = (s+e)/2;
    init(2*node,s,m);
    init(2*node+1,m+1,e);
    *(st+node) = *(st+2*node)+*(st+2*node+1);
}

int query(int node, int s, int e, int v){
    if(s==e) return s;
    int m = (s+e)/2;

    if(*(st+2*node)>v) return query(2*node, s, m, v);
    else return query(2*node+1, m+1, e, v-*(st+2*node));
}

void update(int node, int s, int e, int idx){
    *(st+node)-=1;
    if(s==e) return;
    int m = (s+e)/2;
    if(idx <= m) update(2*node, s, m, idx);
    else update(2*node+1, m+1, e, idx);
}


int main(){
    int n;
    scanf("%d",&n);

    st = (int*)malloc(sizeof(int)*262144);
    ans = (int*)malloc(sizeof(int)*(n+1));

    init(1,1,n);

    for(int i = 1 ; i <= n ; i++){
        int v;
        scanf("%d",&v);

        int pos = query(1,1,n,v);
        *(ans+pos) = i;
        update(1,1,n,pos);
    }

    for(int i = 1 ; i <= n ; i++){
        printf("%d\n",*(ans+i));
    }

    free(st);
    free(ans);

}