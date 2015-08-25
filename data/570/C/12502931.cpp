//Language: GNU C++11


#pragma comment(linker, "/STACK:256000000")
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <deque>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <vector>
#include <ctime>
#include <cstring>
#include <sstream>

//#include <unordered_map>

using namespace std;

//types
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<pii> vpii;

// for
#define FI(n) for(int i=0; i<n; i++)
#define FI1(n) for(int i=1; i<=n; i++)
#define FJ(n) for(int j=0; j<n; j++)
#define FJ1(n) for(int j=1; j<=n; j++)
#define FK(n) for(int k=0; k<n; k++)
#define FU(i, n) for (int i=0; i<n; i++)
#define F(i, s, e) for (int i=s; i<=e; i++)

//scanf types
#define SI(x) scanf("%d", &x)
#define SII(x, y) scanf("%d %d", &x, &y)
#define SIII(x, y, z) scanf("%d %d %d", &x, &y, &z)
#define SIIII(x, y, z, t) scanf("%d %d %d %d", &x, &y, &z, &t)
#define SD(x) scanf("%lf", &x)
#define SP(x) scanf("%d %d", &x.first, &x.second)
#define SS(x) scanf("%s", &x)
#define SA(x, n) FI(n) SI(x[i])
#define SAA(x, n, m) FI(n) FJ(m) SI(x[i][j])

#define Tests(t) int t; SI(t); for(int test=1; test<=t; test++)
#define WS(n) int n; while(SI(n) != EOF)

//scanf with def
#define DI(x) int x; SI(x)
#define DII(x, y) int x, y; SII(x, y);
#define DIII(x, y, z) int x, y, z; SIII(x, y, z);
#define DD(x) double x; SD(x)
#define DS(x) string s; cin>>s
#define DA(a, n) int n; SI(n); SA(a, n);
#define DA2(a, n) int n; SI(n); SAA(a, n, n)
#define DAA(a, n, m) int n, m; SII(n, m); SAA(a, n, m)

//input & files
#define FR(x) freopen(x, "rt", stdin)
#define FW(x) freopen(x, "wt", stdout)
#define FRW(x, y) FR(x); FW(y)
#define UNSYNC() ios::sync_with_stdio(false)

//output && db
#define DB(x) cout<<#x<<" = "<<(x)<<" ";
#define DBN(x) cout<<#x<<" = "<<(x)<<"\n";
#define DBA(x, n) {cout<<#x<<" = [ "; FI(n) cout<<x[i]<<((i+1==n)?" ]":", ");}
#define DS(x) {cout<<#x<<" = [ "; int i = 0, n = x.size(); for(auto x:c) { cout<<x[i]<<((i+1==n)?" ]":", "); i++;}}

#define PI(x) printf("%d", x)
#define PIS(x) printf("%d ", x)
#define PIN(x) printf("%d\n", x)
#define PA(x, n) FI(n) if (i+1==n) PIN(x) : PIS(x)
#define PS(x) for (auto it: x) cout<<it<<" "; 

#define D_EQ(l, r, p) (r-l <= p)
#define D_EQ6(l, r) D_EQ(l, r, 1e-6)
#define D_EQ9(l, r) D_EQ(l, r, 1e-9)

//consts 
const int INF = 100000000;
const int mod = 1000 * 1000 * 1000 + 7;
const double PI = 3.1415926535897932;

//pair
#define x first
#define y second

//functions
double sqr(double x) { return x*x; };
ll sqr(ll x) { return x*x; };
ll sqr(int x) { return x * 1LL * x; };

const int N = 360000;
const int BS = 600;

char p[N];
struct block{
	int l, r;
	char s[BS+1];
	int ans;

	block() {
		l = r = 0;
		ans = 0;
	}

	int update(int p, char c) {
		if (p < l || p > r) return ans;
		s[p - l] = c;
		ans = 0;
		for (int i = 1; i <= r - l; i++)
			if (s[i] == '.' && s[i - 1] == '.')
				ans++;
		return ans;
	}
};

block bs[BS];
int bl = 0;

int main() {

	DII(n, m);
	gets(p); gets(p);

	FI(n) {
		if (i % BS == 0) {
			bl++;
			bs[bl-1].l = bs[bl-1].r = i + 1;
		}
		else {
			bs[bl-1].r++;
		}
		bs[bl-1].s[bs[bl-1].r - bs[bl-1].l] = p[i];
	}

	FJ(bl)
		bs[j].update(bs[j].l, bs[j].s[0]);

	FI(m) {
		DI(ps); char c = getchar();
		while (c == ' ')
			c = getchar();
	
		int r = 0, last = 0;
		FJ(bl) {
			r += bs[j].update(ps, c);
			if (last == '.' && bs[j].s[0] == '.') r++;
			last = bs[j].s[bs[j].r - bs[j].l];
		}
		PIN(r);
	}
	return 0;
}