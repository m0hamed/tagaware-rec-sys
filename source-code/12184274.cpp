//Language: GNU C++11


#include "assert.h"
#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;

#if LOCAL
	#define DO_NOT_SEND
#endif

typedef long long LL;

int IntMaxVal = (int) 1e20;
int IntMinVal = (int) -1e20;
LL LongMaxVal = (LL) 1e20;
LL LongMinVal = (LL) -1e20;

#define FOR(i, a, b) for(int i = a; i < b ; ++i)
#define FORD(i, a, b) for(int i = a; i >= b; --i)

template<typename T> inline void minimize(T &a, T b) { a = std::min(a, b); }
template<typename T> inline void maximize(T &a, T b) { a = std::max(a, b); }

template<typename T> inline void swap(pair<T, T> &p) { swap(p.first , p.second ); }

#define all(v) v.begin(),v.end()

#define endl '\n'
template<typename T> struct argument_type;
template<typename T, typename U> struct argument_type<T(U)> { typedef U type; };
#define next(t, i) argument_type<void(t)>::type i; cin >> i;

template <typename T1, typename T2> istream& operator >>(istream& is, pair<T1, T2>& s) { is >> s.first >> s.second; return is; }
template <typename T> ostream& operator << (ostream& os, const vector<T> &v) { for (int i = 0 ; i < v.size() ; i++) { if (i) os << ' '; os << v[i]; } os << endl; return os; }
template <typename T1, typename T2> ostream& operator << (ostream& os, const vector<pair<T1, T2>> &v) { for (int i = 0 ; i < v.size() ; i++) { os << v[i] << endl; } return os; }
template <typename T1, typename T2> ostream& operator <<(ostream& s, const pair<T1, T2>& t) { s << t.first << ' ' << t.second; return s; }
template <typename T> vector<T> readVector(int n) { vector<T> res(n); for (int i = 0 ; i < n ; i++) cin >> res[i]; return res; }

const int MOD = 1000 * 1000 * 1000 + 7;

struct mod_num {
	int x;
	
	mod_num() : x(0) { }
	mod_num(int x) : x(x >= MOD ? x % MOD : x) { }
	
	mod_num operator + (const mod_num &b) const { int res = x + b.x; if (res >= MOD) res -= MOD; return res; }
	mod_num operator +=(const mod_num &b) { x += b.x; if (x >= MOD) x -= MOD; return *this; }
	
	mod_num operator - (const mod_num &b) const { int res = x - b.x; if (res < 0) res += MOD; return res; }
	mod_num operator -=(const mod_num &b) { if (b.x > 0) *this += MOD - b.x; return *this; }
	
	mod_num operator * (const mod_num &b) const { return (int) (x * (LL) b.x % MOD); }
	mod_num operator *=(const mod_num &b) { x = x * (LL) b.x % MOD; return *this; }
		
	mod_num pow(int n) const {
		if (n == 0) return 1;
		auto res = pow(n / 2);
		res *= res;
		if (n & 1) res *= *this;
		return res;
	}
	
	mod_num rev() const {
		return pow(MOD - 2);
	}
};

mod_num operator +(int a, const mod_num &b) { return mod_num(a) + b; }
mod_num operator *(int a, const mod_num &b) { return mod_num(a) * b; }
istream& operator >> (istream& is, mod_num &x) { return is >> x.x; }
ostream& operator << (ostream& os, const mod_num &x) { return os << x.x; }

struct datum {

};

vector<mod_num> fact(200 * 1000 + 10, 1);
vector<mod_num> fact_rev(fact.size(), 1);

mod_num c(int n, int k) {
	return fact[n] * fact_rev[k] * fact_rev[n - k];
}

mod_num c(vector<pair<int, int>> &ps, int cur, int prev) {
	int dx = ps[cur].second - ps[prev].second;
	int dy = ps[cur].first - ps[prev].first;
	if (dx < 0 || dy < 0) return 0;
	return c(dx + dy, dx);
}

int main() {
	srand (time(NULL));
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	FOR (i, 2, fact.size()) fact[i] = fact[i - 1] * i;
	FOR (i, 2, fact.size()) fact_rev[i] = fact_rev[i - 1] * (mod_num(i).rev());
	
	next(int, h);
	next(int, w);
	next(int, n);

	auto ps = readVector<pair<int, int>>(n);
	ps.push_back( make_pair(1, 1 ) );
	ps.push_back( make_pair(h, w ) );
	sort(all(ps));
	n += 2;

	vector<mod_num> good_ways(n);
	good_ways[0] = 1;
	FOR (i, 1, n) {
		good_ways[i] = c(ps, i, 0);
		FOR (first_fail, 1, i) good_ways[i] -= good_ways[first_fail] * c(ps, i, first_fail);
	}

	cout << good_ways.back();
}