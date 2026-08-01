#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long long LL;

const int N = 50 + 5;

LL a[N][2];
int n;

LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }
LL lcm(LL a, LL b) { return (long long)a * b / gcd(a, b); }

LL calc(LL x) {
	int g1 = 0, g2 = 0;
	for(int i = 1; i <= n; i++) {
		if(a[i][0] % x == 0) g1 = gcd(g1, a[i][0]), g2 = gcd(g2, a[i][1]);
		else g1 = gcd(g1, a[i][1]), g2 = gcd(g2, a[i][0]);
	}
	return lcm(g1, g2);
}

int main() {
	scanf("%d", &n);
	LL lcmall = 1;
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &a[i][0], &a[i][1]), lcmall = lcm(lcmall, lcm(a[i][0], a[i][1]));
	LL sqlcmall = sqrt(lcmall) + 1;
	LL ans = 1;
	for(int j = 2; j <= sqlcmall; j++) {
		if(lcmall % j) continue;
		ans = std::max(ans, calc(j));
		ans = std::max(ans, calc(lcmall / j));
	}
	printf("%lld\n", ans);
	return 0;
}