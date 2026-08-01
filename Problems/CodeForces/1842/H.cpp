#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e3 + 5;
const LL MOD = 1e9 + 7;

int n;
LL m, V;
LL a[N];

LL f[N][N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

int main() {
	scanf("%d%lld%lld", &n, &m, &V);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	f[0][0] = 1;
	LL invn = qpow(n, MOD - 2);
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= std::min(i, (int)m); j++) {
			(f[i][j] += f[i - 1][j] * a[i] % MOD) %= MOD;
			(f[i][j] += f[i - 1][j] * j % MOD * V % MOD) %= MOD;
			if(j) (f[i][j] += f[i - 1][j - 1] * (m - (j - 1)) % MOD * i % MOD * invn % MOD * V % MOD) %= MOD;
		}
	LL ans = 0;
	for(int i = 0; i <= std::min(n, (int)m); i++) (ans += f[n][i]) %= MOD;
	printf("%lld\n", ans);
	return 0;
}