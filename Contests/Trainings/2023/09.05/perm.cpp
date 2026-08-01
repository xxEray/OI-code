#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e7 + 5;

int n;
LL mod;

LL fac[N];

LL f[N];

int main() {
#ifndef DEBUG
	freopen("perm.in", "r", stdin);
	freopen("perm.out", "w", stdout);
#endif
	scanf("%d%lld", &n, &mod);
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	for(int i = 3; i <= n; i++) {
		(f[i] += f[i - 1]) %= mod;
		(f[i] += (i - 1) * f[i - 2]) %= mod;
		(f[i] += (LL)(i - 2) * (i - 1) / 2 % mod * fac[i - 2]) %= mod;
	}
	LL ans = 0;
	for(int i = 1; i <= n; i++) ans ^= f[i];
	printf("%lld\n", ans);
	return 0;
}
