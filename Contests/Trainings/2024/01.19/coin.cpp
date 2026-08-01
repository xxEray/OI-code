#include <bits/stdc++.h>

#ifndef DEBUG
	#undef assert
	#define assert(...) ((void)0)
#endif

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 998244353;

#define SZ(x) ((int)(x).size())

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
	Polynomial inv() const {
		polynomial_assert(a[0]);
		Polynomial ret({inv_v(a[0])});
		int l = SZ(a);
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
	Polynomial ln() const {
		polynomial_assert(a[0] == 1);
		Polynomial tmp = derivative() * inv();
		tmp.a.resize(SZ(a) - 1);
		return tmp.integral();
	}
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
	Polynomial pow(int y) const {
		Polynomial tmp = ln();
		for(int i = 0; i < SZ(tmp.a); i++) tmp.a[i] = (LL)tmp.a[i] * y % MOD;
		return tmp.exp();
	}
	inline Polynomial subpoly(int start) const { return Polynomial(std::vector<int>(a.begin() + start, a.end())); }
	inline Polynomial subpoly(int start, int end) const {
		Polynomial ret{std::vector<int>(end - start)};
		memcpy(ret.a.data(), a.data() + start, (std::min(SZ(a), end) - start) * sizeof(int));
		return ret;
	}
	inline int size() const { return SZ(a); }
	inline void resize(int len) { a.resize(len); }
	inline int &operator[](const int &x) { return a[x]; }
	inline const int &operator[](const int &x) const { return a[x]; }
	friend inline Polynomial operator*(const Polynomial &x, const Polynomial &y) { return Polynomial(x) *= y; }
};

typedef Polynomial<MOD, 3> Poly;

int n, K;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL catalan(int x) { return C(2 * x, x) * inv(x + 1) % MOD; }

int main() {
#ifndef DEBUG
	freopen("coin.in", "r", stdin);
	freopen("coin.out", "w", stdout);
#endif
	get_factorial(1e6);
	int type;
	scanf("%d", &type);
	if(type == 1) {
		scanf("%d%d", &n, &K);
		Poly F;
		F.resize(2 * K + 1);
		for(int i = 0; i <= K; i++) F[2 * i] = catalan(i);
		// printf("F: "); for(int i = 0; i <= n; i++) printf("%d ", F[i]); puts("");
		F = F.pow(n - 2 * K + 1);
		// printf("F: "); for(int i = 0; i <= n; i++) printf("%d ", F[i]); puts("");
		printf("%lld\n", (LL)F[2 * K] * (n - 2 * K + 1) % MOD);
	} else {
		scanf("%d", &n);
		Poly F;
		F.resize(n + 1);
		for(int i = 1; 2 * i <= n; i++) F[2 * i] = (MOD - catalan(i - 1)) * qpow(233, i) % MOD;
		F[0] = 1, F[1] = MOD - 1;
		F = F.inv();
		// printf("F: "); for(int i = 0; i <= n; i++) printf("%d ", F[i]); puts("");
		LL ans = F[n];
		for(int i = 0; i < n; i++) (ans += (LL)F[i] * F[n - i - 1]) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
} /*
2
1000000
*/