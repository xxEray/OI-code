#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;
const int MOD = 998244353;

int n, K;
LL a[N];

LL f[N];

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

inline LL calc(int i, int j) { return i - j + 1 >= j && j >= 0 ? C(i - j + 1, j) : 0LL; }

int main() {
	scanf("%d%d%*d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	get_factorial(n);
	for(int i = 1; i <= n; i++) f[i] = (f[i - 1] + calc(n - 4 * i + 1, K - 2 * i + 1)) % MOD;
	LL ans = 0;
	for(int i = 1; i <= n; i++) {
		int l = std::min(i - 1, n - i);
		(ans += calc(n - 1 - 2 * l - (~l & 1), K - 1 - (l - (l & 1))) * a[i]) %= MOD;
		// printf("%d: l = %d, calc(%d, %d)\n", i, l, n - 1 - 2 * l - (~l & 1), K - 1 - (l - (l & 1)));
	}
	// printf("ans = %lld\n", ans);
	for(int i = 2; i <= n - 1; i++) (ans += (LL)f[std::min((i - 1) / 2, (n - i) / 2)] * a[i]) %= MOD;
	printf("%lld\n", ans);
	return 0;
} /*
7 4 2
1 2 3 4 5 6 7
*/