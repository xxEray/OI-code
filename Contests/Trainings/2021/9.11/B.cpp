#include <cstdio>

typedef long long LL;

const int N = 3000 + 5;

LL n, m, K, mod;
LL fac[N], invfac[N];
LL C[N][N];

LL qpow(LL a, LL b) { LL ret = 1; for(; b; b >>= 1) { if(b & 1) ret = ret * a % mod; a = a * a % mod; } return ret; }
void preprocess() {
	for(int i = 0; i <= 3000; i++) C[i][0] = 1;
	for(int i = 1; i <= 3000; i++)
		for(int j = 1; j <= 3000; j++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
}

int main() {
#ifndef DEBUG
	freopen("stamps.in", "r", stdin);
	freopen("stamps.out", "w", stdout);
#endif
	scanf("%lld%lld%lld%lld", &n, &m, &K, &mod);
	preprocess();
	LL ans = 0;
	for(int i = 0; i <= K / 2; i++) {
		int j = K - i * 2;
		if((!m && i) || (!n && j)) continue;
		(ans += (i ? C[i + m - 1][m - 1] : 1) * (j ? C[j + n - 1][n - 1] : 1) % mod) %= mod;
	}
	printf("%lld\n", ans);
	return 0;
} /*
2 2 4 47 
*/
