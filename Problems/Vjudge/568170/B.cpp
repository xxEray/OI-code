#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1000 + 5;
const LL MOD = 1e9 + 7;

int n;

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

int main() {
	// freopen("h.in", "r", stdin);
	// freopen("h.out", "w", stdout);
	while(scanf("%d", &n) == 1) {
		LL ans = 1;
		for(int i = 1; i <= n; i++) {
			LL x;
			scanf("%lld", &x);
			(ans *= phi(x)) %= MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}