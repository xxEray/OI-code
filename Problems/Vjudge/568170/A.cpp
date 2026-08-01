#include <bits/stdc++.h>

typedef long long LL;

LL n;
int m;

LL phi(LL x) {
	LL v = x, copy = x;
	for(int i = 2; (LL)i * i <= x; i++) if(x % i == 0) {
		v = v / i * (i - 1);
		while(x % i == 0) x /= i;
	}
	if(x > 1) v = v / x * (x - 1);
	// printf("phi(%lld) = %lld\n", copy, v);
	return v;
}

LL qpow(LL x, LL y, LL mod) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL calc(int mod) { LL p = phi(mod); return mod == 1 ? 0 : qpow(n, calc(p) + p, mod); }

int main() {
	scanf("%lld%d", &n, &m);
	LL fac = 1;
	for(int i = 1; i <= m; i++) fac *= i;
	printf("%lld\n", calc(fac));
	return 0;
}