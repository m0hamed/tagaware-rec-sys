//Language: GNU C++


#include<bits/stdc++.h>
using namespace std;
set<int> s;
int n,m,k,len,sum;

void init(){
    scanf("%d%d%d%d",&n,&k,&len,&m);
}

inline int f(int x){ return (x+1)/(len+1); }
void solve(){
    int sum=f(n); s.clear();
    s.insert(0),s.insert(n+1);
    int lie=-1;
    for(int i=1,x;i<=m;++i){
        scanf("%d",&x);
        int l=*(--s.lower_bound(x)),r=*s.lower_bound(x);
        if(r==x) continue; ++l,--r;
        sum-=f(r-l+1),sum+=f(x-l)+f(r-x),s.insert(x);
        if(sum<k){ lie=i; break; }
    }
    printf("%d\n",lie);
}

int main(){
    init();
    solve();
    return 0;
}