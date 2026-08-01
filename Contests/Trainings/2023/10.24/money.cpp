#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e6 + 5;
const LL MOD = 998244353;

LL qpow(LL x, LL y) { x %= MOD; LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

int vis[N];
LL presum[N], prepower[N];

int main() {
#ifndef DEBUG
	freopen("money.in", "r", stdin);
	freopen("money.out", "w", stdout);
#endif
	int A, B;
	LL p;
	scanf("%d%d%lld", &A, &B, &p);
	(p *= inv(1000000)) %= MOD;
	LL power = 1, sum = 0;
	for(int i = 1; A; i++) {
		A <<= 1;
		if(A >= B) {
			// printf("i = %d\n", i);
			(sum += power * p) %= MOD;
			(power *= (MOD + 1 - p) % MOD) %= MOD;
			A -= B;
		} else (power *= p) %= MOD;
		presum[i] = sum, prepower[i] = power;
		if(vis[A]) {
			// printf("cycle!\n");
			LL csum = (sum - presum[vis[A]] + MOD) % MOD;
			LL cpower = power * inv(prepower[vis[A]]) % MOD;
			sum = (presum[vis[A]] + csum * inv(1 - cpower + MOD)) % MOD;
			break;
		}
		vis[A] = i;
	}
	printf("%lld\n", sum);
	return 0;
}