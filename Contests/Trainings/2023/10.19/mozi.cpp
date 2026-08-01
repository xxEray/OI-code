#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e7;
const LL MOD = 1e9 + 7;
const LL inv2 = (MOD + 1) / 2;

int n;

LL inv[N];

int main() {
#ifndef DEBUG
	freopen("mozi.in", "r", stdin);
	freopen("mozi.out", "w", stdout);
#endif
	scanf("%d", &n);
	LL facn = 1;
	for(int i = 1; i <= n; i++) (facn *= i) %= MOD;
	inv[1] = 1;
	for(int i = 2; i <= n; i++) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
	LL ans = 0;
	for(int i = 1; i <= n - 1; i++) (ans += inv2 * (n + i + 1) % MOD * (n - i) % MOD * facn % MOD * inv[i + 1] % MOD) %= MOD;
	printf("%lld\n", ans);
	return 0;
}
