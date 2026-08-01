#include <bits/stdc++.h>

typedef long long LL;

LL qpow(LL x, LL y, LL m) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % m; if(!(y >>= 1)) return ret; x = x * x % m; } }
LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }

LL getphi(LL x) {
	LL y = x;
	for(int i = 2; (LL)i * i <= x; i++) if(x % i == 0) {
		y = y / i * (i - 1);
		while(x % i == 0) x /= i;
	}
	if(x > 1) y = y / x * (x - 1);
	return y;
}

void exgcd(LL a, LL b, LL &x, LL &y) {
	if(b == 0) { x = 1, y = 0; return; }
	LL x_, y_;
	exgcd(b, a % b, x_, y_);
	x = y_, y = x_ - a / b * y_;
}

LL solve(LL a, LL d, LL c, LL m) {
	// printf("solve(%lld, %lld, %lld, %lld)\n", (long long)a, (long long)d, (long long)c, (long long)m);
	if(a % m == 0) return m - c;
	LL phi = getphi(m);
	LL r = solve(a, phi, -d + c, gcd(phi, m));
	LL k, t, v = qpow(a, phi + r, m) - r + d - c;
	// assert(v % gcd(phi, m) == 0);
	LL g = gcd(phi, m);
	exgcd(phi / g, m / g, k, t);
	k *= v / g, t *= v / g;
	if(k < 1) k += (1 - k + m / g - 1) / (m / g) * (m / g);
	else if(k > m / g) k -= (k - 1) / (m / g) * (m / g);
	while(k * phi + r - d <= 0) k += m / g;
	return k * phi + r - d;
}

int main() {
#ifndef DEBUG
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		long long a, m;
		scanf("%lld%lld", &a, &m);
		printf("%lld\n", solve(a, 0, 0, m));
	}
	return 0;
}