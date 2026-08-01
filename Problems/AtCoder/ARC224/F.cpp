#include <bits/stdc++.h>
#include <cassert>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;
const LL inv2 = (MOD + 1) / 2;

int n, K;
LL a[N];

LL fac[N], invfac[N];
LL qpow(LL x, LL y) {
	LL ret = 1;
	for(; y; (x *= x) %= MOD, y >>= 1) if(y & 1) (ret *= x) %= MOD;
	return ret;
}
LL C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_fac(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = qpow(fac[mx], MOD - 2);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

bool contain(LL x, LL y) { return (x & y) == x; }

int main() {
	get_fac(2e5);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		LL best = 0;
		for(int i = n - K + 1; i <= n; i++) best |= a[i];
		auto calc = [](int ind, int rest) -> LL {
			// printf("calc %d %d\n", ind, rest);
			LL ret = 0;
			for(int i = 0; i <= rest; i++) (ret += C(ind, i)) %= MOD;
			return ret;
		};
		LL ans = 0, U = 0;
		for(int i = 1; i <= n; i++) U |= a[i];
		// used -- OR Operation
		auto dfs = [=, &ans](auto &&self, int i, int rest, LL fixed, LL ret) -> void {
			if(rest < 0) return;
			if((best & ~fixed) == 0) {
				(ans += ret) %= MOD;
				return;
			}
			if(i == 0) return;
			// assert(ret == calc(i, rest));
			LL nret = (ret + C(i - 1, rest)) * inv2 % MOD;
			// AND
			if(contain(best & ~fixed, a[i]))
				self(self, i - 1, rest, (fixed | (~best & ~a[i])) & U, nret);
			// OR
			if(contain(~best & ~fixed, ~a[i]))
				self(self, i - 1, rest - 1, (fixed | (best & a[i])) & U, (nret - C(i - 1, rest) + MOD) % MOD);
		};
		dfs(dfs, n, K, 0LL, calc(n, K));
		printf("%lld\n", ans);
	}
	return 0;
}