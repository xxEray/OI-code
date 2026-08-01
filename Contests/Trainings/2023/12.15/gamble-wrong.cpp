#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 1e9 + 7;
const LL inv2 = (MOD + 1) / 2;

int n;

LL fac[2 * N], invfac[2 * N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
// LL inv(LL x) { return qpow(x, MOD - 2); }
// LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
// void get_factorial(int mx) {
// 	fac[0] = 1;
// 	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
// 	invfac[mx] = inv(fac[mx]);
// 	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
// }

LL calc(int x) { return (2 - qpow(inv2, x + 2) + MOD) % MOD; }

int main() {
#ifndef DEBUG
	freopen("gamble.in", "r", stdin);
	freopen("gamble.out", "w", stdout);
#endif
	scanf("%d", &n);
	// get_factorial(2 * n);
	LL power = qpow(2, 2 * n - 1);
	LL last = 0;
	int x = 0, y = 0;
	while(x < n && y < n) {
		int winner;
		scanf("%d", &winner);
		LL now = 0;
		(now += power * calc(n - x) % MOD * calc(n - y - 1) % MOD) %= MOD;
		(now += MOD - power * calc(n - x - 1) % MOD * calc(n - y) % MOD) %= MOD;
		printf("%lld\n", (winner == 0 ? (now - last + MOD) % MOD : (last - now + MOD) % MOD));
		last = now;
		if(winner == 0) x++;
		else y++;
	}
	return 0;
}