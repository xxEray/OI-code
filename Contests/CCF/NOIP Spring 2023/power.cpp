#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long double LD;
typedef long long LL;

LL n;
int K;

LL power(LL x, int y) {
	LL ret = 1;
	while(true) {
		if(y & 1) {
			if((LD)ret * x > n) return n + 1;
			ret *= x;
		}
		if(!(y >>= 1)) return ret;
		if((LD)x * x > n) x = n + 1;
		else x *= x;
	}
}
LL calc(int v) {
	LL st = std::max(1LL, (LL)roundl(powl(n, (LD)1 / v)));
	// printf("st = %lld\n", st);
	while(power(st, v) > n) st--;
	while(power(st + 1, v) <= n) st++;
	// printf("calc(%d) = %lld\n", v, st - 1);
	return st - 1;
}

LL f[100];

int main() {
// #ifndef DEBUG
	freopen("power.in", "r", stdin);
	freopen("power.out", "w", stdout);
// #endif
	scanf("%lld%d", &n, &K);
	K = std::min(K, 64);
	for(int i = 64; i >= 1; i--) {
		f[i] = calc(i);
		for(int j = i + i; j <= 64; j += i) f[i] -= f[j];
		// printf("f[%d] = %lld\n", i, f[i]);
	}
	LL ans = 0;
	for(int i = K; i <= 64; i++) ans += f[i];
	printf("%lld\n", ans + 1);
	return 0;
}