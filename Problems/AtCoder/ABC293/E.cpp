#include <cstdio>
#include <algorithm>

typedef long long LL;

LL a, X, p;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % p; if(!(y >>= 1)) return ret; x = x * x % p; } }

LL solve(LL x) {
	if(x == 0) return 0;
	if(x == 1) return a % p;
	LL v = solve(x >> 1);
	LL ret = (v + v * qpow(a, x >> 1) % p + (x & 1) * qpow(a, x)) % p;
	// printf("solve(%lld) = %lld\n", x, ret);
	return ret;
}

int main() {
	scanf("%lld%lld%lld", &a, &X, &p);
	printf("%lld\n", (solve(X - 1) + 1) % p);
	return 0;
}