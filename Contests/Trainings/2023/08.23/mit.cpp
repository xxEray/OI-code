#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;

int n;
LL mod;

LL inv[N], f[N], g[N] = {1, 1, 2, 3, 4, 6, 9};

int main() {
// #ifndef DEBUG
	freopen("mit.in", "r", stdin);
	freopen("mit.out", "w", stdout);
// #endif
	scanf("%d%lld", &n, &mod);
	for(int i = 7; i <= n; i++) g[i] = g[i - 3] * 3 % mod;
	printf("%lld\n", g[n]);
	inv[1] = 1;
	for(int i = 2; i <= n; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	LL sum = 0, val = 0;
	f[0] = 1, sum += f[0], val += sum;
	for(int i = 1; i <= n; i++) f[i] = inv[i] * val % mod, (sum += f[i]) %= mod, (val += sum) %= mod;
	printf("%lld\n", f[n]);
	return 0;
}