#include <bits/stdc++.h>

#define SZ(x) ((int)(x).size())

typedef long long LL;

#ifdef DEBUG
	#define polynomial_assert(...) assert(__VA_ARGS__)
#else
	#define polynomial_assert(...) ((void)0)
#endif
template<int MOD, int G>
class Polynomial {
	static_assert(MOD & 1);
	std::vector<int> a;
	static inline int lg2(int x) { return 31 ^ __builtin_clz(x); }
	static inline int modadd(const int &x) { return x + ((x >> 31) & MOD); }
	static inline int modsub(const int &x) { return x >= MOD ? x - MOD : x; }
	static inline int qpow(int x, int y) { int ret = 1; while(true) { if(y & 1) ret = (LL)ret * x % MOD; if(!(y >>= 1)) return ret; x = (LL)x * x % MOD; } }
	static inline int inv_v(int x) { return qpow(x, MOD - 2); }
	static const std::vector<int> &get_power_G(int len) {
		static std::vector<int> vct{1};
		static int last = 0;
		if(SZ(vct) < len) {
			len = lg2(len);
			int k = last;
			vct.resize(1 << len);
			vct[1 << (len - 1)] = qpow(G, (MOD - 1) >> (len + 1));
			for(int i = len - 1; i > k; i--) vct[1 << (i - 1)] = (LL)vct[1 << i] * vct[1 << i] % MOD;
			for(int lim = (1 << k); k < len; k++, lim <<= 1)
				for(int i = lim + 1; i < (lim << 1); i++)
					vct[i] = (LL)vct[i - lim] * vct[lim] % MOD;
			last = len;
		}
		return vct;
	}
	static void DIF(std::vector<int> &arr) {
		const auto &power = get_power_G(arr.size() >> 1);
		int lim = SZ(arr);
		for(int i = (lim >> 1); i >= 1; i >>= 1) {
			for(int k = 0; k < i; k++) {
				LL x = arr[k], y = arr[i + k];
				arr[k] = modsub(x + y);
				arr[i + k] = modadd(x - y);
			}
			for(int j = (i << 1), t = 1; j < lim; j += (i << 1), t++)
				for(int k = 0; k < i; k++) {
					LL x = arr[j + k], y = (LL)arr[j + i + k] * power[t] % MOD;
					arr[j + k] = modsub(x + y);
					arr[j + i + k] = modadd(x - y);
				}
		}
	}
	static void DIT(std::vector<int> &arr) {
		auto &power = get_power_G(arr.size() >> 1);
		int lim = SZ(arr);
		for(int i = 1; i < lim; i <<= 1) {
			for(int k = 0; k < i; k++) {
				LL x = arr[k], y = arr[i + k];
				arr[k] = modsub(x + y);
				arr[i + k] = modadd(x - y);
			}
			for(int j = (i << 1), t = 1; j < lim; j += (i << 1), t++)
				for(int k = 0; k < i; k++) {
					LL x = arr[j + k], y = arr[j + i + k];
					arr[j + k] = modsub(x + y);
					arr[j + i + k] = (LL)(x - y + MOD) * power[t] % MOD;
				}
		}
		LL invlim = qpow(lim, MOD - 2);
		for(int i = 0; i < lim; i++) arr[i] = (LL)arr[i] * invlim % MOD;
		std::reverse(arr.begin() + 1, arr.end());
	}
	static const std::vector<int> &get_invs(int l) {
		static std::vector<int> vct{0, 1};
		if(l >= (int)vct.size()) {
			for(int i = (int)vct.size(); i <= l; i++) vct.emplace_back((LL)(MOD - MOD / i) * vct[MOD % i] % MOD);
		}
		return vct;
	}
public:
	Polynomial() : a({0}) {}
	explicit Polynomial(const int &x) : a({x}) {}
	explicit Polynomial(const std::vector<int> &rhs) : a(rhs) { polynomial_assert(!a.empty()); }
	explicit Polynomial(std::vector<int> &&rhs) : a(rhs) { polynomial_assert(!a.empty()); }
	inline constexpr int getMOD() const { return MOD; }
	inline constexpr int getG() const { return G; }
	inline std::vector<int> &data() { return a; }
	inline const std::vector<int> &data() const { return a; }
	inline void negative() { for(int i = 0; i < SZ(a); i++) a[i] = MOD - a[i]; }
	inline Polynomial operator+() const { return *this; }
	inline Polynomial operator-() const { auto tmp = *this; tmp.negative(); return tmp; }
	inline Polynomial &operator+=(const Polynomial &rhs) {
		a.resize(std::max(SZ(a), SZ(rhs.a)));
		for(int i = 0; i < SZ(rhs.a); i++) a[i] = modsub(a[i] + rhs.a[i]);
		return *this;
	}
	inline Polynomial &operator-=(const Polynomial &rhs) {
		a.resize(std::max(SZ(a), SZ(rhs.a)));
		for(int i = 0; i < SZ(rhs.a); i++) a[i] = modadd(a[i] - rhs.a[i]);
		return *this;
	}
	Polynomial &operator*=(const Polynomial &rhs) {
		if(std::min(SZ(a), SZ(rhs.a)) <= 8) {
			int l_ = SZ(a) + SZ(rhs.a) - 1;
			std::vector<int> ret(SZ(a) + SZ(rhs.a) - 1);
			for(int i = 0; i < SZ(a); i++)
				for(int j = 0; j < SZ(rhs.a); j++) {
					ret[i + j] += (LL)a[i] * rhs.a[j] % MOD;
					if(ret[i + j] >= MOD) ret[i + j] -= MOD;
				}
			*this = Polynomial(std::move(ret));
			a.resize(l_);
			return *this;
		}
		int l = SZ(a) + SZ(rhs.a) - 1;
		int l_ = l;
		if(l & (l - 1)) l = 1 << (lg2(l) + 1);
		a.resize(l), DIF(a);
		if(&rhs != this) {
			Polynomial rhs_ = rhs;
			rhs_.a.resize(l), DIF(rhs_.a);
			for(int i = 0; i < l; i++) a[i] = (LL)a[i] * rhs_.a[i] % MOD;
		} else for(int i = 0; i < l; i++) a[i] = (LL)a[i] * a[i] % MOD;
		DIT(a);
		a.resize(l_);
		return *this;
	}
	inline Polynomial &operator*=(const int &v) {
		for(int i = 0; i < SZ(a); i++) a[i] = (LL)a[i] * v % MOD;
		return *this;
	}
	inline Polynomial inv() const { return inv(SZ(a)); }
	Polynomial inv(int len) const {
		polynomial_assert(a[0]);
		Polynomial ret({inv_v(a[0])});
		int l = len;
		if(l & (l - 1)) l = 1 << (lg2(l) + 1);
		for(int i = 2; i <= l; i <<= 1) {
			Polynomial tmp = subpoly(0, i);
			tmp.a.resize(i << 1), ret.a.resize(i << 1);
			DIF(tmp.a), DIF(ret.a);
			for(int j = 0; j < (i << 1); j++) ret.a[j] = (LL)ret.a[j] * (2 - (LL)tmp.a[j] * ret.a[j] % MOD + MOD) % MOD;
			DIT(ret.a), ret.a.resize(i);
		}
		ret.a.resize(SZ(a));
		return ret;
	}
	inline Polynomial derivative() const {
		int l = SZ(a);
		if(l == 1) return Polynomial({0});
		Polynomial ret{std::vector<int>(l - 1)};
		for(int i = 0; i < l - 1; i++) ret.a[i] = (LL)a[i + 1] * (i + 1) % MOD;
		return ret;
	}
	inline Polynomial integral() const {
		int l = SZ(a);
		Polynomial ret{std::vector<int>(l + 1)};
		const auto &invs = get_invs(l);
		for(int i = 1; i <= l; i++) ret.a[i] = (LL)a[i - 1] * invs[i] % MOD;
		return ret;
	}
	inline Polynomial sqrt() const { return sqrt(SZ(a)); }
	inline Polynomial sqrt(int len) const { polynomial_assert(a[0] == 1); return sqrt_qr(len, 1); }
	inline Polynomial sqrt_qr(const std::function<int(int)> &qr_func) const { return sqrt_qr(SZ(a), qr_func(a[0])); }
	inline Polynomial sqrt_qr(int len, const std::function<int(int)> &qr_func) const { return sqrt_qr(len, qr_func(a[0])); }
	inline Polynomial sqrt_qr(int qr) const { return sqrt_qr(SZ(a), qr); }
	Polynomial sqrt_qr(int len, int qr) const {
		polynomial_assert(a[0]);
		Polynomial ret({qr});
		int l = len;
		if(l & (l - 1)) l = 1 << (lg2(l) + 1);
		for(int i = 2; i <= l; i <<= 1) {
			static constexpr LL inv2 = (MOD + 1) >> 1;
			Polynomial tmp = subpoly(0, i);
			ret.a.resize(i);
			tmp *= ret.inv();
			for(int j = 0; j < i; j++) ret.a[j] = (ret.a[j] + tmp.a[j]) * inv2 % MOD;
		}
		ret.a.resize(SZ(a));
		return ret;
	}
	Polynomial inline ln() const {
		polynomial_assert(a[0] == 1);
		Polynomial tmp = derivative() * inv();
		tmp.a.resize(SZ(a) - 1);
		return tmp.integral();
	}
	// O(n log^2 n) 实现，实测比 O(n log n)（就是下面那个）慢
	// Polynomial exp() const {
	// 	polynomial_assert(a[0] == 0);
	// 	int ll = SZ(a);
	// 	const auto &invs = get_invs(ll - 1);
	// 	Polynomial ret;
	// 	ret.a.resize(ll);
	// 	ret.a[0] = 1;
	// 	auto exp_cdq = [&](auto &&self, int l, int r) {
	// 		if(l == r) {
	// 			if(l) ret.a[l] = (LL)ret.a[l] * invs[l] % MOD;
	// 			return;
	// 		}
	// 		int mid = (l + r) >> 1;
	// 		self(self, l, mid);
	// 		Polynomial x(std::vector<int>(ret.a.begin() + l, ret.a.begin() + mid + 1));
	// 		Polynomial y(std::vector<int>(a.begin(), a.begin() + r - l + 1));
	// 		for(int i = 0; i <= r - l; i++) y[i] = (LL)y[i] * i % MOD;
	// 		x *= y;
	// 		for(int i = mid + 1; i <= r; i++) ret.a[i] = modsub(ret.a[i] + x[i - l]);
	// 		self(self, mid + 1, r);
	// 	};
	// 	exp_cdq(exp_cdq, 0, ll - 1);
	// 	return ret;
	// }
	// O(n log n) 实现，实测比 O(n log^2 n)（就是上面那个）快
	Polynomial exp() const {
		polynomial_assert(a[0] == 0);
		Polynomial ret({1});
		int l = SZ(a);
		if(l & (l - 1)) l = 1 << (lg2(l) + 1);
		for(int i = 2; i <= l; i <<= 1) {
			ret.a.resize(i);
			Polynomial tmp = ret.ln();
			Polynomial tmp2 = subpoly(0, i);
			tmp2.a[0] = 1;
			tmp.a.resize(i << 1);
			tmp2.a.resize(i << 1);
			ret.a.resize(i << 1);
			DIF(tmp.a), DIF(tmp2.a), DIF(ret.a);
			for(int j = 0; j < (i << 1); j++) ret.a[j] = (LL)ret.a[j] * (tmp2.a[j] - tmp.a[j] + MOD) % MOD;
			DIT(ret.a);
			ret.a.resize(i);
		}
		ret.a.resize(SZ(a));
		return ret;
	}
	// y 应该是取模之前的数，如果需要对 y 取模请调用双参数版本
	Polynomial pow(int y) const {
		if(y == 0) {
			Polynomial ret{std::vector<int>(SZ(a))};
			ret.a[0] = 1;
			return ret;
		}
		int id = -1, len = SZ(a);
		for(int i = 0; i < len; i++) if(a[i]) { id = i; break; }
		if(id == -1 || id >= (len + y - 1) / y) return Polynomial(std::vector<int>(len));
		Polynomial x = subpoly(id, id + len - id * y);
		const LL power = qpow(a[id], y);
		if(SZ(x.a) == 1) x.a[0] = power;
		else {
			const LL invv = inv_v(a[id]);
			for(int i = 0; i < SZ(x.a); i++) x.a[i] = x.a[i] * invv % MOD;
			x = x.ln();
			for(int i = 0; i < SZ(x.a); i++) x.a[i] = (LL)x.a[i] * y % MOD;
			x = x.exp();
			for(int i = 0; i < SZ(x.a); i++) x.a[i] = x.a[i] * power % MOD;
		}
		Polynomial ret{std::vector<int>(len)};
		for(int i = 0; i < len - id * y; i++) ret.a[i + id * y] = x.a[i];
		return ret;
	}
	// 当调用这个函数的时候请务必保证 y >= mod
	// y_mod：指数对 mod 取模的后值
	// y_phi：指数对 phi(mod) = mod - 1 取模后的值
	Polynomial pow(int y_mod, int y_phi) const {
		int len = SZ(a);
		if(!a[0]) return Polynomial(std::vector<int>(len));
		Polynomial x = *this;
		const LL power = qpow(a[0], y_phi);
		if(SZ(x.a) == 1) x.a[0] = power;
		else {
			const LL invv = inv_v(a[0]);
			for(int i = 0; i < SZ(x.a); i++) x.a[i] = x.a[i] * invv % MOD;
			x = x.ln();
			for(int i = 0; i < SZ(x.a); i++) x.a[i] = (LL)x.a[i] * y_mod % MOD;
			x = x.exp();
			for(int i = 0; i < SZ(x.a); i++) x.a[i] = x.a[i] * power % MOD;
		}
		return x;
	}
	inline Polynomial &operator/=(const int &v) {
		const LL invv = inv_v(v);
		for(int i = 0; i < SZ(a); i++) a[i] = a[i] * invv % MOD;
		return *this;
	}
	inline Polynomial subpoly(int start) const { return Polynomial(std::vector<int>(a.begin() + start, a.end())); }
	inline Polynomial subpoly(int start, int end) const {
		Polynomial ret{std::vector<int>(end - start)};
		memcpy(ret.a.data(), a.data() + start, (std::min(SZ(a), end) - start) * sizeof(int));
		return ret;
	}
	friend inline Polynomial mulT(Polynomial x, Polynomial y) {
		std::reverse(y.a.begin(), y.a.end());
		int n = SZ(x.a), m = SZ(y.a);
		x *= y;
		return x.subpoly(m - 1, m + n - 1);
	}
	std::vector<int> multipoint(std::vector<int> vct) const {
		int sz_vct = SZ(vct);
		int n = std::max(SZ(a), SZ(vct));
		vct.resize(n);
		std::vector<int> ret(n);
		std::vector<Polynomial> Q(4 * n + 1);
		auto dfs_Q = [&](auto &&self, int x, int l, int r) {
			if(l == r) { Q[x] = Polynomial(std::vector<int>({1, vct[l] ? MOD - vct[l] : 0})); return; }
			int mid = (l + r) >> 1;
			self(self, x << 1, l, mid), self(self, x << 1 | 1, mid + 1, r);
			Q[x] = Q[x << 1] * Q[x << 1 | 1];
		};
		dfs_Q(dfs_Q, 1, 0, n - 1);
		auto dfs = [&](auto &&self, int x, int l, int r, Polynomial &&F) {
			F.a.resize(r - l + 1);
			if(l == r) { ret[l] = F[0]; return; }
			int mid = (l + r) >> 1;
			self(self, x << 1, l, mid, mulT(F, Q[x << 1 | 1]));
			self(self, x << 1 | 1, mid + 1, r, mulT(F, Q[x << 1]));
		};
		dfs(dfs, 1, 0, n - 1, mulT(subpoly(0, n), Q[1].inv()));
		ret.resize(sz_vct);
		return ret;
	}
	friend inline std::vector<int> multipoint(const Polynomial &f, const std::vector<int> &vct) { return f.multipoint(vct); }
	static Polynomial interpolate(const std::vector<int> &X, const std::vector<int> &Y) {
		polynomial_assert(X.size() == Y.size());
		int n = SZ(X);
		std::vector<Polynomial> Q(4 * n + 1);
		auto dfs_Q = [&](auto &&self, int x, int l, int r) {
			if(l == r) { Q[x] = Polynomial(std::vector<int>({X[l] ? MOD - X[l] : 0, 1})); return; }
			int mid = (l + r) >> 1;
			self(self, x << 1, l, mid), self(self, x << 1 | 1, mid + 1, r);
			Q[x] = Q[x << 1] * Q[x << 1 | 1];
		};
		dfs_Q(dfs_Q, 1, 0, n - 1);
		auto &&q = multi_point(Q[1].derivative(), X);
		auto dfs = [&](auto &&self, int x, int l, int r) {
			if(l == r) return Polynomial(std::vector<int>({(int)((LL)Y[l] * inv_v(q[l]) % MOD)}));
			int mid = (l + r) >> 1;
			return self(self, x << 1, l, mid) * Q[x << 1 | 1] + self(self, x << 1 | 1, mid + 1, r) * Q[x << 1];
		};
		return dfs(dfs, 1, 0, n - 1);
	}
	inline int evaluate(int x) const {
		int ret = 0;
		for(int i = SZ(a) - 1; i >= 0; i--) ret = ((LL)ret * x + a[i]) % MOD;
		return ret;
	}
	inline Polynomial &operator/=(const Polynomial &rhs) { return *this *= rhs.inv(std::max(SZ(a), SZ(rhs.a))); }
	inline int size() const { return SZ(a); }
	inline int length() const { return SZ(a); }
	inline void resize(int len) { a.resize(len); }
	inline int &operator[](const int &x) { return a[x]; }
	inline const int &operator[](const int &x) const { return a[x]; }
	friend inline Polynomial inv(const Polynomial &x) { return x.inv(); }
	friend inline Polynomial inv(const Polynomial &x, int len) { return x.inv(len); }
	friend inline Polynomial sqrt(const Polynomial &x) { return x.sqrt(); }
	friend inline Polynomial sqrt(const Polynomial &x, int len) { return x.sqrt(len); }
	friend inline Polynomial sqrt_qr(const Polynomial &x, int qr) { return x.sqrt_qr(qr); }
	friend inline Polynomial sqrt_qr(const Polynomial &x, int len, int qr) { return x.sqrt_qr(len, qr); }
	friend inline Polynomial sqrt_qr(const Polynomial &x, const std::function<int(int)> &func_qr) { return x.sqrt_qr(func_qr(x[0])); }
	friend inline Polynomial sqrt_qr(const Polynomial &x, int len, const std::function<int(int)> &func_qr) { return x.sqrt_qr(len, func_qr(x[0])); }
	friend inline Polynomial derivative(const Polynomial &x) { return x.derivative(); }
	friend inline Polynomial integral(const Polynomial &x) { return x.integral(); }
	friend inline Polynomial ln(const Polynomial &x) { return x.ln(); }
	friend inline Polynomial exp(const Polynomial &x) { return x.exp(); }
	// y 应该是取模之前的数，如果需要对 y 取模请调用三参数版本
	friend inline Polynomial pow(const Polynomial &x, int y) { return x.pow(y); }
	// 当调用这个函数的时候请务必保证 y >= mod
	// y_mod：指数对 MOD 取模的后值
	// y_phi：指数对 phi(MOD) = MOD - 1 取模后的值
	friend inline Polynomial pow(const Polynomial &x, int y_mod, int y_phi) { return x.pow(y_mod, y_phi); }
	friend inline Polynomial mul(const Polynomial &x, const Polynomial &y, int len) { Polynomial z = x * y; z.resize(len); return z; }
	friend inline Polynomial operator*(const Polynomial &x, const int &y) { return Polynomial(x) *= y; }
	friend inline Polynomial operator*(const int &x, const Polynomial &y) { return Polynomial(y) *= x; }
	friend inline Polynomial operator/(const Polynomial &x, const int &y) { return Polynomial(x) /= y; }
	friend inline Polynomial operator+(const Polynomial &x, const Polynomial &y) { return Polynomial(x) += y; }
	friend inline Polynomial operator-(const Polynomial &x, const Polynomial &y) { return Polynomial(x) -= y; }
	friend inline Polynomial operator*(const Polynomial &x, const Polynomial &y) { return Polynomial(x) *= y; }
	friend inline Polynomial operator/(const Polynomial &x, const Polynomial &y) { return Polynomial(x) /= y; }
};

const int N = 1e5 + 5;
const int D = 1e5;
const int MOD = 998244353;

typedef Polynomial<MOD, 3> Poly;

int n, m;
int cnt[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = (LL)ret * x % MOD; if(!(y >>= 1)) return ret; x = (LL)x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

Poly f;

int main() {
	scanf("%d%d", &n, &m);
	f.resize(m + 1);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); cnt[x]++; }
	for(int i = 1; i <= m; i++)
		for(int j = i; j <= m; j += i)
			(f[j] += cnt[i] * inv(j / i) % MOD) %= MOD;
	f = f.exp();
	for(int i = 1; i <= m; i++) printf("%d\n", f[i]);
	return 0;
}