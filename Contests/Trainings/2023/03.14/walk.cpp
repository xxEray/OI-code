#include <cstdio>
#include <algorithm>

typedef long long LL;
const LL MOD = 998244353;

const int N = 1.2e5 + 5; 

LL D, n, m, K, A, B, C;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL Cxy(LL x, LL y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

namespace Solve_50 {
	const int N = 50 + 5;
	LL a[N][N][N], b[N][N][N];
	void main() {
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) for(int k = 1; k <= K; k++) a[i][j][k] = 1;
		for(int d = 1; d <= D; d++) {
			for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) for(int k = 1; k <= K; k++) b[i][j][k] = a[i][j][k], a[i][j][k] = 0;
			for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) for(int k = 1; k <= K; k++) {
				(a[i][j][k] += b[i + 1][j][k]) %= MOD;
				(a[i][j][k] += b[i - 1][j][k]) %= MOD;
				(a[i][j][k] += b[i][j + 1][k]) %= MOD;
				(a[i][j][k] += b[i][j - 1][k]) %= MOD;
				(a[i][j][k] += b[i][j][k + 1]) %= MOD;
				(a[i][j][k] += b[i][j][k - 1]) %= MOD;
			}
		}
		printf("%lld\n", a[A][B][C]);
	}
}

namespace Solve_mK1 {
	void main() {
		LL ans = 0;
		for(LL i = 1; i <= n; i++) {
			LL ii = std::abs(i - A);
			if((D & 1) != (ii & 1)) continue;
			if(D < ii) continue;
			(ans += Cxy(D, (D + ii) / 2)) %= MOD;
		}
		printf("%lld\n", ans);
	}
}

int main() {
#ifndef DEBUG
	freopen("walk.in", "r", stdin);
	freopen("walk.out", "w", stdout);
#endif
	scanf("%lld%lld%lld%lld%lld%lld%lld", &D, &n, &m, &K, &A, &B, &C);
	get_factorial(1.2e5);
	if(n <= 50 && m <= 50 && K <= 50 && D <= 50) Solve_50::main();
	else if(m == 1 && K == 1) Solve_mK1::main();
	return 0;
}
