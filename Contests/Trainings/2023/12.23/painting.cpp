#include <bits/stdc++.h>

typedef long long LL;

const int D = 2000;
const int N = D + 5;
const LL MOD = 1e9 + 7;

int K;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

struct Poly {
	LL a[N];
	void trim() { for(int i = 0; i <= D; i++) a[i] = (a[i] % MOD + MOD) % MOD; }
	void clear() { memset(a, 0, sizeof(a)); }
	Poly() { memset(a, 0, sizeof(a)); }
	LL at(LL x) const {
		LL ret = 0;
		for(int i = D; i >= 0; i--) ret = (ret * x + a[i]) % MOD;
		return ret;
	}
};
Poly operator+(const Poly &x, const Poly &y) {
	Poly z;
	for(int i = 0; i <= D; i++) z.a[i] = (x.a[i] + y.a[i]) % MOD;
	return z;
}
Poly operator-(const Poly &x, const Poly &y) {
	Poly z;
	for(int i = 0; i <= D; i++) z.a[i] = (x.a[i] - y.a[i] + MOD) % MOD;
	return z;
}
Poly operator*(const Poly &x, const Poly &y) {
	Poly z;
	for(int i = 0; i <= D; i++) for(int j = 0; j <= D - i; j++) (z.a[i + j] += x.a[i] * y.a[j]) %= MOD;
	return z;
}
Poly operator/(const Poly &x, const Poly &y) {
	Poly z;
	for(int i = 0; i <= D; i++) {
		z.a[i] = x.a[i];
		for(int j = 0; j < i; j++) (z.a[i] += MOD - z.a[j] * y.a[i - j] % MOD) %= MOD;
		(z.a[i] *= inv(y.a[0])) %= MOD;
	}
	return z;
}

Poly f, g, h, p, q, s, t;

LL tmp[N], invv[2 * N];
void lagrange() {
	for(int i = -D; i <= D; i++) invv[i + D] = inv(i);
	f.clear();
	tmp[0] = 1;
	for(int i = 1; i <= D; i++)
		for(int j = D - 1; j >= 0; j--)
			tmp[j] = ((j ? tmp[j - 1] : 0) + (MOD - i) * tmp[j]) % MOD;
	for(int i = 1; i <= D; i++) {
		LL val = t.a[i];
		for(int j = 1; j <= D; j++) if(j != i) (val *= invv[i - j + D]) %= MOD;
		for(int j = 0; j <= D - 1; j++) tmp[j] = ((j ? tmp[j - 1] : 0) + MOD - tmp[j]) * invv[i + D] % MOD;
		for(int j = 0; j <= D - 1; j++) (f.a[j] += tmp[j] * val) %= MOD;
		for(int j = D - 1; j >= 0; j--) tmp[j] = ((j ? tmp[j - 1] : 0) + (MOD - i) * tmp[j]) % MOD;
	}
}

int main() {
#ifndef DEBUG
	freopen("painting.in", "r", stdin);
	freopen("painting.out", "w", stdout);
#endif
	int T; scanf("%d%d", &T, &K);
	p.clear(), p.a[0] += 1, p.a[1] += -1, p.trim();
	q.clear(), q.a[0] += 1, q.a[1] += -2, q.a[K + 1] += 1, q.trim();
	f = p / q;
	p.clear(), p.a[0] += 1, p.a[1] += -1, p.trim();
	q.clear(), q.a[0] += 1, q.a[1] += -2, q.a[K] += 1, q.trim();
	f = f - p / q;
	// printf("f: "); for(int i : {10, 20, 30}) printf("%lld ", f.a[i]); puts("");
	p.clear(), p.a[K + 1] += 1, p.trim();
	q.clear(), q.a[0] += 1, q.a[1] += -1, q.trim();
	g = p / q;
	// printf("g: "); for(int i : {10, 20, 30}) printf("%lld ", g.a[i]); puts("");
	p.clear(), p.a[0] += 1, p.trim();
	q.clear(), q.a[0] += 2, q.trim();
	h = p - f * g;
	s = f + g + q;
	t = s / h - g;
	lagrange();
	while(T--) {
		LL n;
		scanf("%lld", &n);
		printf("%lld ", f.at(n % MOD));
	}
	puts("");
	return 0;
} /*
3 2
2 3 4
*/