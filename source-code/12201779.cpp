//Language: GNU C++


#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <cstring>
#include <cstdio>

using namespace std;



#define rep(i,k,n)                             for(__typeof(n) i=(k);i<(n);++i)
#define rep2(i,n)                              rep(i,0,n)
#define rrep(i,k,n)                            for(__typeof(n) i=(k)-1;i>=(n);--i)
#define rrep2(i,n)                             rrep(i,n,0)

#define readInt(n)							   scanf("%d", &n);
#define readStr(s)							   scanf("%s", s);


#define ll										long long
#define ull										unsigned long long
#define tkey									ll

#define MOD					(tkey)(1e9+7)
#define HASH_WEIGHT			4
#define PT_NUM				(tkey)(2e3+7)
#define MAX_NUM				(tkey)(2e5+7)



struct S_POINT
{
	int x;
	int y;
};
S_POINT pt[PT_NUM];

tkey fact[MAX_NUM], inv[MAX_NUM];
tkey dp[MAX_NUM];

int h, w, n;


tkey qpow(tkey base, tkey n)
{
	tkey ans = 1;
	while (n)
	{
		if (n & 1) ans = (ans * base) % MOD;
		base = base * base % MOD;
		n >>= 1;
	}
	return ans;
}


void calcInv(int m)
{
	int i;
	inv[0] = 1;
	fact[0] = 1;
	inv[1] = 1;
	for (i = 1; i < m; i++)
	{
		fact[i] = (fact[i - 1] * i) % MOD;
	}
	for (i = 2; i < m; i++)
	{
		inv[i] = qpow(fact[i], MOD - 2);
	}
}


// tkey C(tkey n, tkey m)
// {
// 	tkey i;
// 	//addLog("Need C(" << n << "," << m << ")");
// 	if (n < m) return 0;
// 	//cala the min
// 	if (m > n - m) m = n - m;
// 	//n %= MOD;
// 	tkey ans = inv[m];
// 	for (i = 1; i <= m; i++)
// 	{
// 		ans = (ans * (n - i + 1)) % MOD;
// 		////addLog("ans=" << ans);
// 	}
// 	//addLog("C(" << n << "," << m << ")=" << ans);
// 	return ans;
// }

// //lucas定理：C(n,m)%p = C(n/p,m/p) * C(n%p,m%p)
// //C(n,m)模p等于p进制数上各位的C(ni,mi)模p的乘积
// tkey C(tkey n, tkey m)
// {
// 	//C(n,0) = 1
// 	if (0 == m) return 1;
// 	return (getC(n % MOD, m % MOD) *  C(n / MOD, m / MOD)) % MOD;
// }

tkey C(tkey n, tkey m)
{
	return fact[n] * inv[m] % MOD * inv[n - m] % MOD;
}

bool cmp(S_POINT &a, S_POINT &b)
{
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

// 解法很简单，从点 x[j],y[j] 走到 x[i],y[i] 的步数为
// ComboNumber(x[i] - x[j] + y[i] - y[j], x[i] - x[j])
// 从平面图上可以看出，因为兵只能向下走一格或者向右走一格，所以x方向上只能走 x[i] - x[j] 格， y方向上之只能走 y[i] - y[j] 格
// 所以总的步数就是排列数  C (x+y, x)
// 从左上角走到右下角，如果没有任何限制条件，就是上述公式
// 如果某些格子不能走，那么可以从总步数里面减去坏格子的走法


void cf559C()
{
	readInt(h);
	readInt(w);
	readInt(n);
	rep(i, 1, n + 1)
	{
		readInt(pt[i].x);
		readInt(pt[i].y);
	}
	n++;
	pt[n].x = h;
	pt[n].y = w;
	calcInv(MAX_NUM);

	sort(pt + 1, pt + n + 1, cmp);

	// calc all the black cell steps
	rep(i, 1, n + 1)
	{
		dp[i] = C(pt[i].x + pt[i].y - 2, pt[i].x - 1);
		rep(j, 1, i)
		{
			dp[i] = (dp[i] + MOD - dp[j] * C(pt[i].x - pt[j].x + pt[i].y - pt[j].y, pt[i].x - pt[j].x) % MOD) % MOD;
		}
	}
	cout << dp[n] << endl;
}

int main(int argc, char * argv[])
{
	cf559C();


	return 0;
}

