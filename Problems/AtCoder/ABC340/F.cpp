#include <bits/stdc++.h>

typedef long long LL;

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }

void exgcd(LL a, LL b, LL &x, LL &y) {
	if(b == 0) { x = 1, y = 0; return; }
	exgcd(b, a % b, x, y);
	std::tie(x, y) = std::make_pair(y, x - a / b * y);
}

int main() {
	LL a, b;
	scanf("%lld%lld", &a, &b);
	LL extra = 2;
	if((~a & 1) && (~b & 1)) a >>= 1, b >>= 1, extra = 1;
	if(gcd(std::abs(a), std::abs(b)) > 1) { puts("-1"); return 0; }
	LL x, y;
	exgcd(std::abs(a), std::abs(b), x, y);
	if(a < 0) x = -x;
	if(b < 0) y = -y;
	printf("%lld %lld\n", -y * extra, x * extra);
	return 0;
}