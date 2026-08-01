#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1000 + 5;
const int S = (1 << 10) + 1;
const int MOD = 998244353;

char str[N];
int a[N];
int n;

LL f[N][S], g[N][S], sum[N][15];

int setsize(int s) {
	int cnt = 0;
	for(int i = 0; i < 10; i++) cnt += (s >> i) & 1;
	return cnt;
}

LL qpow(LL a, LL b) {
	LL ret = 1;
	for(; b; b >>= 1) {
		if(b & 1) (ret *= a) %= MOD;
		(a *= a) %= MOD;
	}
	return ret;
}
LL inv(LL x) { return qpow(x, MOD - 2); }

int main() {
	scanf("%d%s", &n, str + 1);
	for(int i = 1; i <= n; i++) a[i] = str[i] - 'A';
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < 10; j++)
			sum[i][j] = sum[i - 1][j] + (a[i] == j);
	int U = (1 << 10) - 1;
	f[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int s = 0; s <= U; s++) {
			// g[i][s ^ (1 << a[i])] = g[i - 1][s ^ (1 << a[i])];
			// int j = i - 2;
			// g[i][s ^ (1 << a[i])] = 0;
			for(int j = 0; j <= i - 2; j++) {
				// if(j == i - 2) if(g[i][s ^ (1 << a[i])] != g[i - 1][s ^ (1 << a[i])]) printf("%d %d %lld %lld\n", i, s ^ (1 << a[i]), g[i][s ^ (1 << a[i])], g[i - 1][s ^ (1 << a[i])]);
				if(a[j + 1] == a[i])
					(g[i][s ^ (1 << a[i])] += inv(qpow(2, sum[j][a[j + 1]] + 2)) * f[j][s ^ (1 << a[i])] % MOD) %= MOD;
			}
			if(s & (1 << a[i])) {
				(f[i][s] = qpow(2, sum[i][a[i]]) * g[i][s ^ (1 << a[i])]) %= MOD;
				(f[i][s] += f[i - 1][s ^ (1 << a[i])]) %= MOD;
			}
			(f[i][s] += f[i - 1][s]) %= MOD;
		}
	}
	LL ans = 0;
	for(int s = 1; s <= U; s++) (ans += f[n][s]) %= MOD;
	printf("%lld\n", ans);
	return 0;
} /*
3
AAA
*/