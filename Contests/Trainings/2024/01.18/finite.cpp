#include <bits/stdc++.h>

typedef long long LL;

const LL MOD = 998244353;

LL n, a, b, c, d;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

using VI = std::vector<int>;
using VPI = std::vector<std::pair<int, int>>;

std::vector<int> G{1};
void get_G(int len) {
	if(len & (len - 1)) len = (31 ^ __builtin_clz(len)) + 1;
	else len = 31 ^ __builtin_clz(len);
	G.resize(1 << len);
	G[1 << (len - 1)] = qpow(3, (MOD - 1) >> (len + 1));
	for(int i = len - 1; i > 0; i--) G[1 << (i - 1)] = (LL)G[1 << i] * G[1 << i] % MOD;
	for(int lim = 1; lim < (1 << len); lim <<= 1)
		for(int i = lim + 1; i < (lim << 1); i++)
			G[i] = (LL)G[i - lim] * G[lim] % MOD;
}

void DIF(std::vector<int> &vct) {
	int lim = vct.size();
	for(int i = (lim >> 1); i >= 1; i >>= 1)
		for(int j = 0, t = 0; j < lim; j += (i << 1), t++)
			for(int k = 0; k < i; k++) {
				LL x = vct[j + k], y = (LL)vct[j + i + k] * G[t] % MOD;
				vct[j + k] = (x + y >= MOD ? x + y - MOD : x + y);
				vct[j + i + k] = (x - y < 0 ? x - y + MOD : x - y);
			}
}
void DIT(std::vector<int> &vct) {
	int lim = vct.size();
	for(int i = 1; i < lim; i <<= 1)
		for(int j = 0, t = 0; j < lim; j += (i << 1), t++)
			for(int k = 0; k < i; k++) {
				LL x = vct[j + k], y = vct[j + i + k];
				vct[j + k] = (x + y >= MOD ? x + y - MOD : x + y);
				vct[j + i + k] = (x - y + MOD) * G[t] % MOD;
			}
	LL invlim = inv(lim);
	for(int i = 0; i < lim; i++) vct[i] = vct[i] * invlim % MOD;
	std::reverse(vct.begin() + 1, vct.end());
}

int sz;
struct Poly {
	std::vector<int> a;
	Poly() : a({0}) {}
	Poly(const std::vector<int> &a_) : a(a_) {}
	Poly(std::vector<int> &&a_) : a(a_) {}
	Poly(const std::vector<std::pair<int, int>> &);
	int size() const { return a.size(); }
	void resize(int n_) { a.resize(n_); }
	int &operator[](int x) { return a[x]; }
	const int &operator[](int x) const { return a[x]; }
	Poly &operator*=(Poly y);
	Poly &operator%=(Poly y);
};
Poly::Poly(const std::vector<std::pair<int, int>> &vct) {
	int mx = 0;
	for(auto p : vct) mx = std::max(mx, p.first);
	a.resize(mx + 1);
	for(auto [x, y] : vct) (a[x] += y + MOD) %= MOD;
}
Poly operator*(const Poly &p, const Poly &q) {
	Poly ret;
	ret.resize(p.size() + q.size());
	for(int i = 0; i < p.size(); i++) for(int j = 0; j < q.size(); j++) (ret[i + j] += (LL)p[i] * q[j] % MOD) %= MOD;
	return ret;
}
Poly operator+(const Poly &p, const Poly &q) {
	Poly ret = p;
	ret.resize(std::max(p.size(), q.size()));
	for(int i = 0; i < q.size(); i++) (ret[i] += q[i]) %= MOD;
	return ret;
}
Poly operator-(const Poly &p, const Poly &q) {
	Poly ret = p;
	ret.resize(std::max(p.size(), q.size()));
	for(int i = 0; i < q.size(); i++) (ret[i] += MOD - q[i]) %= MOD;
	return ret;
}
Poly inv(Poly x) {
	assert(x[0]);
	Poly ret((VI){(int)inv(x[0])});
	int len = x.size();
	if(len & (len - 1)) len = 1 << ((31 ^ __builtin_clz(len)) + 1);
	for(int i = 2; i <= len; i <<= 1) {
		Poly tmp;
		tmp.resize(i);
		memcpy(tmp.a.data(), x.a.data(), std::min(i, (int)x.a.size()) * sizeof(int));
		tmp.resize(i << 1), ret.resize(i << 1);
		DIF(tmp.a), DIF(ret.a);
		for(int j = 0; j < (i << 1); j++) ret.a[j] = (LL)ret.a[j] * (2 - (LL)tmp.a[j] * ret.a[j] % MOD + MOD) % MOD;
		DIT(ret.a), ret.a.resize(i);
	}
	ret.resize(x.size());
	return ret;
}
Poly &Poly::operator*=(Poly y) {
	// int l_ = a.size() + y.size() - 1;
	// std::vector<int> ret(l_);
	// for(int i = 0; i < (int)a.size(); i++)
	// 	for(int j = 0; j < (int)y.a.size(); j++) {
	// 		ret[i + j] += (LL)a[i] * y.a[j] % MOD;
	// 		if(ret[i + j] >= MOD) ret[i + j] -= MOD;
	// 	}
	// a.swap(ret), a.resize(l_);
	// return *this;
	int len = size() + y.size();
	int len_ = len;
	if(len & (len - 1)) len = 1 << ((31 ^ __builtin_clz(len)) + 1);
	resize(len), y.resize(len);
	DIF(a), DIF(y.a);
	for(int i = 0; i < len; i++) a[i] = (LL)a[i] * y.a[i] % MOD;
	DIT(a);
	a.resize(len_);
	return *this;
}
Poly &Poly::operator%=(Poly y) {
	// LL invv = (MOD - inv(y[y.size() - 1])) % MOD;
	// for(int i = size() - 1; i >= sz; i--) {
	// 	LL tmp = a[i] * invv % MOD;
	// 	for(int j = 0; j < y.size(); j++) {
	// 		a[j + (i - y.size()) + 1] += tmp * y[j] % MOD;
	// 		if(a[j + (i - y.size()) + 1] >= MOD) a[j + (i - y.size()) + 1] -= MOD;
	// 	}
	// }
	// if(size() > sz) resize(sz);
	// return *this;
	if(size() < y.size()) return *this;
	int len_ = y.size() - 1;
	Poly xr = *this, yr = y;
	std::reverse(yr.a.begin(), yr.a.end());
	yr = inv(yr);
	std::reverse(xr.a.begin(), xr.a.end());
	int len = xr.size() + yr.size();
	if(len & (len - 1)) len = 1 << ((31 ^ __builtin_clz(len)) + 1);
	xr.resize(len), yr.resize(len);
	DIF(xr.a), DIF(yr.a);
	for(int i = 0; i < len; i++) xr.a[i] = (LL)xr.a[i] * yr.a[i] % MOD;
	DIT(xr.a);
	xr.resize(size() - y.size() + 1);
	std::reverse(xr.a.begin(), xr.a.end());
	len = size();
	if(len & (len - 1)) len = 1 << ((31 ^ __builtin_clz(len)) + 1);
	a.resize(len), xr.resize(len), y.resize(len);
	DIF(a), DIF(xr.a), DIF(y.a);
	for(int i = 0; i < len; i++) a[i] = (a[i] - (LL)xr[i] * y[i] % MOD + MOD) % MOD;
	DIT(a);
	a.resize(len_);
	return *this;
}

struct Fraction {
	Poly p, q;
	Fraction() : p(), q((VI){1}) {}
	Fraction(const Poly &t) : p(t), q((VI){1}) {}
	Fraction(const Poly &p_, const Poly &q_) : p(p_), q(q_) {}
};
Fraction operator/(const Poly &p, const Poly &q) { return Fraction(p, q); }
Fraction operator+(const Fraction &x, const Fraction &y) { return Fraction(x.p * y.q + y.p * x.q, x.q * y.q); }
Fraction operator-(const Fraction &x, const Fraction &y) { return Fraction(x.p * y.q - y.p * x.q, x.q * y.q); }
Fraction operator*(const Fraction &x, const Fraction &y) { return Fraction(x.p * y.p, x.q * y.q); }
Fraction operator/(const Fraction &x, const Fraction &y) { return Fraction(x.p * y.q, x.q * y.p); }

int main() {
#ifndef DEBUG
	freopen("finite.in", "r", stdin);
	freopen("finite.out", "w", stdout);
#endif
	get_G(10000);
	int T; scanf("%d", &T);
	while(T--) {
		int U, V;
		scanf("%lld%lld%lld%lld%lld%d%d", &n, &a, &b, &c, &d, &U, &V);
		if(U == 0 || V == 0) {
			if(U == 0 && V == 0) puts("1");
			else if(U == 0) printf("%lld\n", (n / c + n / d + 1) % MOD);
			else printf("%lld\n", (n / a + n / b + 1) % MOD);
			continue;
		}
		Fraction A(Poly((VPI){{a, 1}, {b, 1}, {a + b, -2}}), Poly((VPI){{0, 1}, {a, -1}}) * Poly({{0, 1}, {b, -1}}));
		Fraction B(Poly((VPI){{c, 1}, {d, 1}, {c + d, -2}}), Poly((VPI){{0, 1}, {c, -1}}) * Poly({{0, 1}, {d, -1}}));
		Fraction H = (Poly((VI){2}) + A + B) / (Poly((VI){1}) - A * B) - Poly((VI){1});
		Fraction S = H / Poly((VI){1, MOD - 1});
		while(S.p.a.size() >= 2 && S.p.a.back() == 0) S.p.a.pop_back();
		sz = S.p.size();
		Poly qq;
		qq.resize(S.q.size());
		qq[S.q.size() - 1] = 1;
		for(int i = 1; i < S.q.size(); i++) qq[S.q.size() - 1 - i] = (LL)S.q[i] * inv(S.q[0]) % MOD;
		while(qq.size() > 1 && qq.a.back() == 0) qq.a.pop_back();
		sz = std::max(sz, qq.size());
		fprintf(stderr, "sz = %d\n", sz);
		fprintf(stderr, "clock = %.3f\n", (double)clock() / CLOCKS_PER_SEC);
		Poly base((VI){1}), now((VI){0, 1});
		while(true) {
			if(n & 1) (base *= now) %= qq;
			if(!(n >>= 1)) break;
			(now *= now) %= qq;
		}
		fprintf(stderr, "clock = %.3f\n", (double)clock() / CLOCKS_PER_SEC);
		Poly ret;
		ret.resize(std::max(S.p.size(), S.q.size()));
		for(int i = 0; i < ret.size(); i++) {
			ret[i] = (i < S.p.size() ? S.p[i] : 0);
			for(int j = 0; j < i; j++) (ret[i] += MOD - (LL)ret[j] * S.q[i - j] % MOD) %= MOD;
			ret[i] = (LL)ret[i] * S.q[0] % MOD;
		}
		LL ans = 0;
		for(int i = 0; i < base.size(); i++) (ans += (LL)base[i] * ret[i] % MOD) %= MOD;
		printf("%lld\n", ans);
	}
	fprintf(stderr, "clock = %.3f\n", (double)clock() / CLOCKS_PER_SEC);
	return 0;
} /*
1
538333181918 3 3 3 1 652172950 279475170

1000000000000 660 686 695 675 560033600 642134094
*/