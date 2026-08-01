#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;
const LL MOD = 998244353;

int n;
char s[N];
LL pa, pb, qa, qb;
int ca, cb;

LL f[N][N], g[N][N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

int main() {
#ifndef DEBUG
	freopen("vanish.in", "r", stdin);
	freopen("vanish.out", "w", stdout);
#endif
	scanf("%d%s%lld%lld%d%d", &n, s + 1, &qa, &qb, &ca, &cb);
	pa = qb * inv(qa + qb) % MOD, pb = qa * inv(qa + qb) % MOD;
	f[0][cb] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(s[i] == 'B') f[i][j] = f[i - 1][j + 1];
			else f[i][j] = (f[i][j - 1] * pa + f[i - 1][j] * pb) % MOD;
	g[n + 1][ca] = 1;
	for(int i = n; i >= 1; i--)
		for(int j = 1; j <= n; j++)
			if(s[i] == 'A') g[i][j] = g[i + 1][j + 1];
			else g[i][j] = (g[i][j - 1] * pb + g[i + 1][j] * pa) % MOD;
	if(ca == 0) { printf("%lld\n", f[n - 1][1]); return 0; }
	else if(cb == 0) { printf("%lld\n", g[2][1]); return 0; }
	LL ans = 0;
	for(int i = 1; i < n; i++) if(s[i] == 'B' &&  s[i + 1] == 'A') (ans += f[i - 1][1] * g[i + 2][1]) %= MOD;
	printf("%lld\n", ans);
	return 0;
}