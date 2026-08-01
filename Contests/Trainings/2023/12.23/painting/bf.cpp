#include <bits/stdc++.h>

typedef long long LL;

const int N = 2000 + 5;
const LL MOD = 1e9 + 7;

int K;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

struct Poly {
	LL a[N];
	void trim() { for(int i = 0; i <= 2000; i++) a[i] = (a[i] % MOD + MOD) % MOD; }
	void clear() { memset(a, 0, sizeof(a)); }
	Poly() { memset(a, 0, sizeof(a)); }
};
Poly operator+(const Poly &x, const Poly &y) {
	Poly z;
	for(int i = 0; i <= 2000; i++) z.a[i] = (x.a[i] + y.a[i]) % MOD;
	return z;
}
Poly operator-(const Poly &x, const Poly &y) {
	Poly z;
	for(int i = 0; i <= 2000; i++) z.a[i] = (x.a[i] - y.a[i] + MOD) % MOD;
	return z;
}
Poly operator*(const Poly &x, const Poly &y) {
	Poly z;
	for(int i = 0; i <= 2000; i++) for(int j = 0; j <= 2000 - i; j++) (z.a[i + j] += x.a[i] * y.a[j]) %= MOD;
	return z;
}
Poly operator/(const Poly &x, const Poly &y) {
	Poly z;
	for(int i = 0; i <= 2000; i++) {
		z.a[i] = x.a[i];
		for(int j = 0; j < i; j++) (z.a[i] += MOD - z.a[j] * y.a[i - j] % MOD) %= MOD;
		(z.a[i] *= inv(y.a[0])) %= MOD;
	}
	return z;
}

Poly f, g, h, p, q, s, t;

int main() {
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
	while(T--) {
		int n;
		scanf("%d", &n);
		printf("%lld ", t.a[n]);
	}
	puts("");
	return 0;
} /*
3 2
2 3 4
*/