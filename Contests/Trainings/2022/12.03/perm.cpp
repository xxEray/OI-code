#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e7 + 5;

LL mod;

LL f[N], fac[N];

LL calc(int n) {
	LL ans = 0;
	for(int i = 1; i <= n; i++) f[i] = 0;
	f[0] = 1;
	for(int i = 0; i <= n - 2; i++) {
		(f[i + 1] += f[i]) %= mod;
		(f[i + 2] += f[i] * (n - i - 1) % mod) %= mod;
		(ans += f[i] * ((LL)(n - i - 1) * (n - i - 2) / 2 % mod) % mod * fac[n - i - 2]) %= mod;
	}
//	for(int i = 0; i <= n; i++) printf("[%d] %lld\n", i, f[i]);
	return ans;
}

int main() {
#ifndef DEBUG
	freopen("perm.in", "r", stdin);
	freopen("perm.out", "w", stdout);
#endif
	int n;
	scanf("%d%lld", &n, &mod);
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = i * fac[i - 1] % mod;
	LL ans = 0;
	for(int i = 1; i <= n; i++) ans ^= calc(i);
	printf("%lld\n", ans);
	return 0;
}
