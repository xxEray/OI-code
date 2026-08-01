#include <cstdio>
#include <algorithm>
#include <cassert>

typedef long long LL;

const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }
LL lcm(LL x, LL y) { return x / gcd(x, y) * y; }

void exgcd(LL a, LL b, LL &x, LL &y) {
    if(b == 0) { x = 1, y = 0; return; }
    exgcd(b, a % b, x, y);
    LL tmp = x;
    x = y;
    y = tmp - a / b * y;
}


LL calc(LL a, LL b, LL n, LL m) {
	LL tmax = lcm(n, m);
	if(a == b) return a;
	if((b - a) % gcd(n, m)) return LLINF;
	// printf("calc (%lld,%lld) in (%lld,%lld) | %lldx+%lld=%lldy+%lld | ", a, b, n, m, n, a, m, b);
	LL x, y, g = gcd(n, m);
	exgcd(n / g, m / g, x, y);
	// printf("%lldx+%lldy=1 => x=%lld,y=%lld | ", n / g, m / g, x, y);
	if(b - a < 0) x = -x, y = -y;
	y = -y;
	x *= std::abs(b - a) / g, y *= std::abs(b - a) / g;
	// printf("x=%lld,y=%lld | ", x, y);
	assert(n * x + a == m * y + b);
	LL gn = n / g, gm = m / g, i = -LLINF;
	if(x < 0) i = std::max(i, (-x + gm - 1) / gm);
	else i = std::max(i, -(x / gm));
	if(y < 0) i = std::max(i, (-y + gn - 1) / gn);
	else i = std::max(i, -(y / gn));
	x += i * gm, y += i * gn;
	// printf("x=%lld,=%lld\n", x, y);
	assert(n * x + a == m * y + b);
	return n * x + a < tmax ? n * x + a : LLINF;
}

int main() {
	LL n, m;
	int K;
	scanf("%lld%lld%d", &n, &m, &K);
	while(K--) {
		LL a, b;
		scanf("%lld%lld", &a, &b);
		LL ans = std::min({calc(a, b, 2 * n, 2 * m), calc(2 * n - a, b, 2 * n, 2 * m), calc(a, 2 * m - b, 2 * n, 2 * m), calc(2 * n - a, 2 * m - b, 2 * n, 2 * m)});
		if(ans == LLINF) puts("-1");
		else printf("%lld\n", ans);
	}
	return 0;
}