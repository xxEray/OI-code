#include <bits/stdc++.h>

typedef long long LL;

int n;
LL p[15], r[15];

void exgcd(LL a, LL b, LL &x, LL &y) {
	if(b == 0) { x = 1, y = 0; return; }
	exgcd(b, a % b, x, y);
	std::tie(x, y) = std::make_pair(y, x - a / b * y);
}
LL inv(LL x, LL mod) {
	x %= mod;
	LL u, v;
	exgcd(x, mod, u, v);
	u = (u % mod + mod) % mod;
	return u;
}

LL mul(LL x, LL y, LL mod) {
	LL z = x * y - (LL)((long double)x * y / mod + 0.5) * mod;
	return z < 0 ? z + mod : z;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &p[i], &r[i]);
	LL prodall = 1;
	for(int i = 1; i <= n; i++) prodall *= p[i];
	LL ans = 0;
	for(int i = 1; i <= n; i++) {
		LL prod = 1;
		for(int j = 1; j <= n; j++) if(j != i) prod *= p[j];
		prod *= inv(prod, p[i]);
		// printf("i = %d, prod = %lld\n", i, prod);
		(ans += mul(prod, r[i], prodall)) %= prodall;
	}
	printf("%lld\n", ans % prodall);
	return 0;
}