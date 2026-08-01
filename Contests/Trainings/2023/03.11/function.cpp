#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 300 + 5;
const int S = (1 << 17) + 5;
const LL MOD = 998244353;

int n, m;

LL f[N][N];

LL Cmi[N], C[N][N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

void preprocess(int mx) {
	Cmi[0] = 1;
	for(int i = 1; i <= n; i++) Cmi[i] = Cmi[i - 1] * (m - i + 1) % MOD * inv(i) % MOD;
	for(int i = 0; i <= n; i++) C[i][0] = 1;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
}

int main() {
#ifndef DEBUG
	freopen("function.in", "r", stdin);
	freopen("function.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	preprocess(300);
	LL ans1 = 0, ans2 = 0;
	int U = (1 << (n - 1)) - 1;
	for(int s = 0; s < U; s++) {
		int sz = 0;
		for(int i = 1; i <= n; i++) sz += (s >> i & 1);
		LL ret = 1;
		for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) f[i][j] = 0;
		int i = 0;
		while(true) {
			int j = i;
			i++; while((s >> (i - 1) & 1)) i++;
			for(int k = 0; k <= j; k++)
			if(i == n) break;
		}
		printf("s=%d, ret = %lld\n", s, ret);
		(ans1 += Cmi[n - sz] * ret % MOD) %= MOD;
	}
	printf("%lld %lld\n", ans1, ans2);
	return 0;
}
