#include <bits/stdc++.h>

typedef long long LL;

const int N = 500 + 5;
const LL MOD = 998244353;

int type, n, K;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

LL f[N][N][N];

int main() {
	scanf("%d", &type);
	if(type == 1) scanf("%d%d", &n, &K);
	else scanf("%d", &n);
	f[0][0][0] = 1;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++)
			for(int k = 0; k <= n; k++) {
				(f[i + 1][j + 1][k] += f[i][j][k]) %= MOD;
				if(j) (f[i + 1][j - 1][k + 1] += f[i][j][k]) %= MOD;
				else (f[i + 1][j][k] += f[i][j][k]) %= MOD;
			}
	if(type == 1) {
		LL ans = 0;
		for(int j = 0; j <= n; j++) (ans += f[n][j][K]) %= MOD;
		printf("%lld\n", ans);
	} else {
		LL ans = 0;
		for(int i = 0; i <= n; i++) {
			LL sum = 0;
			for(int j = 0; j <= n; j++) (sum += f[n][j][i]) %= MOD;
			(ans += sum * qpow(233, i)) %= MOD;
			// printf("K = %d: ans = %lld\n", i, sum);
		}
		printf("%lld\n", ans);
	}
	return 0;
}