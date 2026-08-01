#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n;
LL p[N], r[N];

void exgcd(LL a, LL b, LL &x, LL &y) {
	if(b == 0) { x = 1, y = 0; return; }
	exgcd(b, a % b, x, y);
	std::tie(x, y) = std::make_pair(y, x - a / b * y);
}

LL mul(LL x, LL y, LL mod) {
	LL z = x * y - (LL)((long double)x * y / mod + 0.5) * mod;
	return z < 0 ? z + mod : z;
}

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }
void merge(LL p1, LL r1, LL p2, LL r2, LL &pa, LL &ra) {
	pa = p1 / gcd(p1, p2) * p2;
	LL p1_copy = p1;
	LL k1, k2, rr = r2 - r1;
	p2 = -p2;
	if(rr < 0) p1 = -p1, p2 = -p2, rr = -rr;
	LL g = gcd(std::abs(p1), std::abs(p2));
	assert(rr % g == 0);
	p1 /= g, p2 /= g, rr /= g;
	exgcd(std::abs(p1), std::abs(p2), k1, k2);
	if(p1 < 0) k1 = -k1;
	k1 = (k1 % pa + pa) % pa;
	k1 = mul(k1, rr, pa);
	// assert(k1 * p1 + k2 * p2 == rr);
	ra = (mul(k1, p1_copy, pa) + r1) % pa;
	assert(ra % p1_copy == r1);
	// assert(ra % p2_copy == r2);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &p[i], &r[i]);
	LL p0 = 1, r0 = 0;
	for(int i = 1; i <= n; i++) {
		LL pt, rt;
		merge(p0, r0, p[i], r[i], pt, rt);
		p0 = pt, r0 = rt;
	}
	printf("%lld\n", r0);
	return 0;
}