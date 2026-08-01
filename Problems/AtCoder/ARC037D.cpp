#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 1e9 + 7;

int n;

LL f[N], g[N], h[N];

int main() {
	scanf("%d", &n);
	f[0] = 1, g[0] = 2, h[0] = 1;
	for(int i = 1; i <= n; i++) {
		f[i] = (3 * f[i - 1] % MOD + g[i - 1] * g[i - 1] % MOD * g[i - 1] % MOD) % MOD;
		g[i] = (g[i - 1] * g[i - 1] % MOD + (2 * g[i - 1] % MOD * h[i - 1] % MOD + MOD - h[i - 1] * h[i - 1] % MOD) % MOD * g[i - 1] % MOD) % MOD;
		h[i] = (g[i - 1] * g[i - 1] % MOD + (2 * g[i - 1] % MOD * h[i - 1] % MOD + MOD - h[i - 1] * h[i - 1] % MOD) % MOD * h[i - 1] % MOD) % MOD;
	}
	printf("%lld\n", f[n]);
	return 0;
}