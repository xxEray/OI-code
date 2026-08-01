#include <bits/stdc++.h>

typedef long long LL;

const LL MOD = 998244353;

LL n, K;

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }

LL bitprod(LL x) {
	LL prod = 1;
	while(x) prod *= x % 10, x /= 10;
	return prod;
}

int main() {
	scanf("%lld%lld", &n, &K);
	LL ans = 0;
	for(LL i = 1; i <= n; i++) for(LL j = 1; j <= n; j++) if(bitprod(i) && bitprod(j) && gcd(bitprod(i), bitprod(j)) <= K) ans++;
	printf("%lld\n", ans % MOD);
	return 0;
}