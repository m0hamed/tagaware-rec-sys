//Language: GNU C++11


#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#define INF 0x3f3f3f3f3f3f3f3f
typedef long long ll;

using namespace std;
const ll maxn = 1e5+10;
const ll mod = 1e9+13;


struct edge{
    ll v,to,cost;
    edge(ll t,ll c):to(t),cost(c){};
    edge(ll v, ll t,ll c):v(v),to(t),cost(c){};
    bool operator < (const edge & a) const{
        return cost > a.cost;
    }
};

vector <edge> G_a[maxn];
vector <edge> G_b[maxn];
vector <edge> e;


void addedge(ll from, ll to, ll cost){
    G_a[from].push_back(edge(to, cost));
    G_b[to].push_back(edge(from, cost));
}
ll dis_a[maxn];
ll dis_b[maxn];
ll cnt_a[maxn];
ll cnt_b[maxn];
ll n;

void Dijkstra(ll s,ll cnt[], ll dis[],bool flag){
    for (ll i = 0 ; i <= n ; i ++){
        dis[i] = INF;cnt[i] = 0;
    }
    dis[s] = 0;cnt[s] = 1;
    priority_queue<edge> Q;
    Q.push(edge(s,dis[s]));
    while(!Q.empty()){
        edge tmp = Q.top();Q.pop();
        ll limt = flag?G_a[tmp.to].size():G_b[tmp.to].size();
        for(ll i = 0 ; i < limt; i ++){
            edge& next = flag ? G_a[tmp.to][i]:G_b[tmp.to][i];
            if(dis[next.to] == tmp.cost+next.cost)
                cnt[next.to] = (cnt[tmp.to]+cnt[next.to])%mod;
            if(dis[next.to] > tmp.cost + next.cost){
                cnt[next.to] = cnt[tmp.to];
                dis[next.to] = tmp.cost + next.cost;
                Q.push(edge(next.to,dis[next.to]));
            }
        }
    }
}

int main(){
    ll m,s,t;
    cin >>n>>m>>s>>t;
    ll from, to, cos;
    for (ll i = 0 ; i < m ; i ++){
        scanf("%I64d %I64d %I64d",&from,&to,&cos);
        addedge(from,to,cos);
        e.push_back(edge(from,to,cos));
    }
    Dijkstra(s,cnt_a,dis_a,true);
    Dijkstra(t,cnt_b,dis_b,false);
    for(ll i = 0 ; i < m ; i ++){

        if(dis_a[e[i].v]+e[i].cost+dis_b[e[i].to] == dis_a[t] && (cnt_a[e[i].v]*cnt_b[e[i].to])%mod == cnt_a[t])
            puts("YES");
        else{
            ll ect = dis_a[t]-dis_a[e[i].v]-dis_b[e[i].to]-1;
            if(ect < 1 || e[i].cost == 1)
                puts("NO");
            else printf ("CAN %I64d\n",e[i].cost-ect);
        }
    }
}
