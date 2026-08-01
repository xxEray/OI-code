/* 陽炎は黄泉に待たむと。*/

#include <bits/stdc++.h>
using namespace std;

#define inl inline
typedef long long ll;
typedef unsigned long long ull;
// typedef __int128 lll;
// typedef long double llf;
typedef pair <int, int> pint;
#define fst first
#define scd second
#define all(p) begin (p), end (p)
#define empb emplace_back

#ifdef SHIKEN
#define msg(args...) fprintf (stderr, args)
#else
#define msg(...) void ()
#endif

struct bint : private vector <unsigned int> {
	using uint = uint32_t;
	using ull = uint64_t;
	using ulll = __uint128_t;
	using fmtflags = _Ios_Fmtflags;
	static constexpr int BUF_SIZE = 1<<18;
	static ull h[];

	uint* &g = _M_impl._M_start;
	inline static void fix (ull a[], int n) {
		for (int i = 0; i + 1 < n; ++i)
			a[i + 1] += a[i] >> 32,
			a[i] &= UINT_MAX;
		a[n - 1] &= UINT_MAX;
	}
	inline static void store (ull a[], uint b[], int n) {
		for (int i = 0; i + 1 < n; ++i)
			a[i + 1] += a[i] >> 32,
			b[i] = a[i];
		b[n - 1] = a[n - 1];
	}
	inline bool sgn () const { return back ()>>31; }
	inline int lg () const {
		int k = size () - 1;
		while (~k && !g[k]) --k;
		return k == -1 ? -1 : k * 32 + __lg (g[k]);
	}
	inline bint abs () const {
		return sgn () ? -*this : *this;
	}
	template <class T>
	inline static constexpr bool sgn (const T &x) requires (is_integral_v <T>) {
		return is_signed_v <T> && (x >> CHAR_BIT * sizeof (T) - 1);
	}
	inline static int bit_pad (int k) { return k / 32 + 1; }
	template <class T>
	constexpr static size_t tp_width = max ((size_t) 1, sizeof (T)>>2);

	bint (const bint &b) : vector <uint> (b) {}
	bint () : vector <uint> (1) {};
	template <class T>
	bint (T x) requires (is_integral_v <T>)
		: vector <uint> (tp_width <T> + 1) {
		const int n = size ();
		for (int i = 0; i < n; ++i)
			g[i] = x, x >>= 31 % (sizeof (T) * CHAR_BIT), x >>= 1;
		shrink ();
	}
	bint (const char* s, const fmtflags &flg = (fmtflags) 0) : bint (string (s)) {}
	bint (const string &s, const fmtflags &flg = (fmtflags) 0) : vector <uint> (1) {
		if (!s.length ()) return;
		const char d[] = "0123456789abcdef";
		int b = 10, i = 0; ull t = 1, a = 0;
		bool neg = 0;
		if (s[0] == '-') ++i, neg = 1;
		if (flg & fmtflags::_S_hex) b = 16;
		if (flg & fmtflags::_S_oct) b = 8;
		const ull lmt = ULLONG_MAX / b;
		const int m = s.length ();
		for (; i < m; ++i) {
			t *= b;
			(a *= b) += find (d, d + sizeof d, (char) tolower (s[i])) - d;
			if (t >= lmt || i + 1 == m) {
				(*this *= t) += a;
				a = 0, t = 1;
			}
		}
		if (neg) negate ();
		shrink ();
	}
	bint& operator = (const bint &b) {
		assign (b.begin (), b.end ());
		return *this;
	}

	inline void guarantee (size_t n) {
		if (n > size ())
			resize (n, (uint) -sgn ());
	}
	inline void shrink () {
		int k = size () - 1;
		const uint x = -sgn ();
		if (g[k] == x)
			while (k > 0 && g[k - 1] == x) --k;
		resize (k + 1);
	}

	inline string hex () const {
		string s = ""; char buf[12];
		int k = size () - 1;
		while (~k && !g[k]) --k;
		if (k == -1) return "0";
		sprintf (buf, "%x", g[k]); s += buf;
		while (~--k) sprintf (buf, "%08x", g[k]), s += buf;
		return s;
	}
	inline string dec () const {
		bint a (sgn () ? -*this : *this);
		string s = ""; char buf[12];
		while (a) {
			const auto [q, r] = div <int> (a, 1e9);
			reverse (buf, buf + sprintf (buf, q ? "%09d" : "%d", r));
			a = q; s += buf;
		}
		if (s.empty ()) s = "0";
		if (sgn ()) s += "-";
		reverse (s.begin (), s.end ());
		return s;
	}
	inline string oct () const {
		string s = ""; int k = lg ();
		if (k == -1) return "0";
		int r = k % 3;
		while (~k) {
			int c = r, x = 0;
			while (~c && ~k)
				(x <<= 1) |= __get_bit (k--), --c;
			s += '0' + x; r = 2;
		}
		return s;
	}

	friend ostream& operator << (ostream &out, const bint &a) {
		string s;
		const auto flg = out.flags ();
		if (flg & out.hex) {
			s = (flg & out.showbase ? "0x" : "") + a.hex ();
			if (flg & out.uppercase)
				for (char &c : s) c = toupper (c);
		}
		else if (flg & out.oct)
			s = (flg & out.showbase ? "0" : "") + a.oct ();
		else s = a.dec ();
		return out << s;
	}
	friend istream& operator >> (istream &in, bint &a) {
		string s; in >> s;
		a = bint (s, in.flags ());
		return in;
	}

	inline bint& operator |= (const bint &b) {
		guarantee (b.size ());
		const uint high = -b.sgn ();
		const int m = b.size ();
		for (int i = m - 1; ~i; --i)
			g[i] |= b.g[i];
		for (int i = size () - 1; i >= m; --i)
			g[i] |= high;
		return *this;
	}
	inline bint& operator &= (const bint &b) {
		guarantee (b.size ());
		const uint high = -b.sgn ();
		const int m = b.size ();
		for (int i = m - 1; ~i; --i)
			g[i] &= b.g[i];
		for (int i = size () - 1; i >= m; --i)
			g[i] &= high;
		return *this;
	}
	inline bint& operator ^= (const bint &b) {
		guarantee (b.size ());
		const uint high = -b.sgn ();
		const int m = b.size ();
		for (int i = m - 1; ~i; --i)
			g[i] ^= b.g[i];
		for (int i = size () - 1; i >= m; --i)
			g[i] ^= high;
		return *this;
	}
	inline friend bint operator | (bint a, const bint &b) {
		return a |= b;
	}
	inline friend bint operator & (bint a, const bint &b) {
		return a &= b;
	}
	inline friend bint operator ^ (bint a, const bint &b) {
		return a ^= b;
	}
	inline bint operator ~ () const {
		bint c;
		for (int i = size () - 1; ~i; --i)
			c.g[i] = ~g[i];
		return c;
	}
	inline void __set_bit (size_t k, bool x) {
		g[k / 32] &= UINT_MAX ^ (1u<<k % 32);
		g[k / 32] |= (uint) x<<k % 32;
	}
	inline void set_bit (size_t k, bool x) {
		guarantee (bit_pad (k));
		__set_bit (k, x);
	}
	inline bool __get_bit (size_t k) const {
		return (g[k / 32] >> k % 32) & 1;
	}
	inline bool get_bit (size_t k) const {
		return k >= size () * 32 ? sgn () : __get_bit (k);
	}

	inline bint& operator <<= (size_t k) {
		guarantee (bit_pad (k) + size ());
		const int r = k % 32, p = k / 32;
		if (r == 0) {
			for (int i = size () - 1, j = i - p; i >= p; --i, --j)
				g[i] = g[j];
		} else {
			for (int i = size () - 1, j = i - p; i > p; --i, --j)
				g[i] = g[j] << r | g[j - 1] >> 32 - r;
			g[p] = g[0] << r;
		}
		for (int i = 0; i < p; ++i) g[i] = 0;
		return shrink (), *this;
	}
	inline friend bint operator << (bint a, size_t k) {
		return a <<= k;
	}
	inline bint& operator >>= (size_t k) {
		if (k >= size () * 32)
			return g[0] = -sgn (), resize (1), *this;
		const int r = k % 32, p = k / 32, n = size ();
		const uint sup = -sgn ();
		int i = 0, j = p;
		if (r == 0) {
			for (; j < n; ++i, ++j)
				g[i] = g[j];
			--i;
		} else {
			for (; j + 1 < n; ++j, ++i)
				g[i] = g[j] >> r | g[j + 1] << 32 - r;
			g[i] = g[j] >> r | sup << 32 - r;
		}
		return resize (i + 1), shrink (), *this;
	}
	inline friend bint operator >> (bint a, size_t k) {
		return a >>= k;
	}

	inline friend auto operator <=> (const bint &a, const bint &b) {
		if (auto sgncmp = b.sgn () <=> a.sgn (); sgncmp != 0)
			return sgncmp;
		if ((a.size () <=> b.size ()) != 0)
			return a.sgn () ? b.size () <=> a.size () : a.size () <=> b.size ();
		for (int i = a.size () - 1; ~i; --i)
			if (auto cmp = a.g[i] <=> b.g[i]; cmp != 0)
				return cmp;
		return strong_ordering::equal;
	}
	inline friend bool operator == (const bint &a, const bint &b) {
		if (a.size () != b.size ()) return 0;
		for (int i = a.size () - 1; ~i; --i)
			if (a.g[i] != b.g[i]) return 0;
		return 1;
	}

	explicit inline operator bool () const {
		for (int i = size () - 1; ~i; --i)
			if (g[i]) return 1;
		return 0;
	}
	template <class T>
	explicit inline operator T () const requires (is_integral_v <T> && !is_same_v <bool, T>) {
		T x = 0;
		const uint u = -sgn ();
		for (int i = size (); i < tp_width <T>; ++i)
			x |= (T) u<<32 * i;
		for (int i = min (tp_width <T>, size ()) - 1; ~i; --i)
			x |= (T) g[i]<<32 * i;
		return x;
	}
	inline bool operator ! () const { return !bool (*this); }

	template <class T>
	inline bint& operator += (T b) requires (is_integral_v <T>) {
		ull c = 0;
		guarantee (max (size (), tp_width <T>) + 1);
		const int n = size ();
		for (int i = 0; i < n; ++i) {
			c += (ull) g[i] + (uint) b,
			g[i] = c, c >>= 32;
			b >>= 31 % (sizeof (T) * CHAR_BIT), b >>= 1;
		}
		return shrink (), *this;
	}
	inline bint& operator += (const bint &b) {
		guarantee (max (b.size (), size ()) + 1);
		ull c = 0;
		const int n = size (), m = b.size ();
		const uint x = -b.sgn ();
		for (int i = 0; i < m; ++i)
			c += (ull) g[i] + b.g[i],
			g[i] = c, c >>= 32;
		for (int i = m; i < n; ++i)
			c += (ull) g[i] + x,
			g[i] = c, c >>= 32;
		return shrink (), *this;
	}
	template <class T>
	inline friend bint operator + (bint a, const T &b) {
		return a += b;
	}
	inline bint& operator ++ () { return *this += 1; }
	inline bint operator ++ (int) {
		bint a (*this);
		return *this += 1, a;
	}
	template <class T>
	inline bint& operator -= (T b) requires (is_integral_v <T>) {
		ull c = 1; b = ~b;
		guarantee (max (size (), tp_width <T> + 1) + 1);
		const int n = size ();
		for (int i = 0; i < n; ++i) {
			c += (ull) g[i] + (uint) b,
			g[i] = c, c >>= 32;
			b >>= 31 % (sizeof (T) * CHAR_BIT), b >>= 1;
		}
		return shrink (), *this;
	}
	inline bint& operator -= (const bint &b) {
		guarantee (max (b.size () + 1, size ()) + 1);
		ull c = 1;
		const int n = size (), m = b.size ();
		const uint x = ~-b.sgn ();
		for (int i = 0; i < m; ++i)
			c += (ull) g[i] + ~b.g[i],
			g[i] = c, c >>= 32;
		for (int i = m; i < n; ++i)
			c += (ull) g[i] + x,
			g[i] = c, c >>= 32;
		return shrink (), *this;
	}
	template <class T>
	inline friend bint operator - (bint a, const T &b) {
		return a -= b;
	}
	inline bint& operator -- () { return *this -= 1; }
	inline bint operator -- (int) {
		bint a (*this);
		return *this -= 1, a;
	}
	inline bint& negate () {
		guarantee (size () + 1);
		const int n = size ();
		ull c = 1;
		for (int i = 0; i < n; ++i)
			g[i] = c += ~g[i], c >>= 32;
		return shrink (), *this;
	}
	inline bint operator - () const {
		bint b (*this);
		return b.negate ();
	}

	inline void raw_convo (const bint &b, const int n, const int m) {
		memset (h, 0, n + m<<3);
		for (int i = 0; i < n; ++i) {
			ull c = 0, d;
			for (int j = 0; j < m; ++j)
				d = (ull) g[i] * b.g[j],
				h[i + j] += c + (uint) d, c = d >> 32;
			h[m + i] += c;
		}
		guarantee (n + m);
		store (h, g, n + m);
	}

	template <class T>
	inline bint& operator *= (T x) requires (is_integral_v <T>) {
		make_unsigned_t <T> _x = x;
		const bool rev = sgn () ^ sgn (x),
			sgna = sgn (), sgnb = sgn (x);
		if (sgna) negate ();
		if (sgnb) _x = -_x;
		const int n = size (), m = tp_width <T>;
		memset (h, 0, n + m<<3);
		for (int i = 0; i < m; ++i) {
			ull c = 0;
			for (int j = 0; j < n; ++j)
				c += (ull) g[j] * (uint) _x,
				h[i + j] += (uint) c, c >>= 32;
			h[n + i] += c;
			_x >>= 31 % (sizeof (T) * CHAR_BIT), _x >>= 1;
		}
		guarantee (n + m);
		store (h, g, n + m);
		if (rev) negate ();
		return shrink (), *this;
	}
	inline bint& operator *= (bint b) {
		const bool rev = sgn () ^ b.sgn (),
			sgna = sgn (), sgnb = b.sgn ();
		if (sgna) negate ();
		const int n = size (), m = b.size ();
		if (sgnb) b = -b;
		raw_convo (b, n, m);
		if (rev) negate ();
		return shrink (), *this;
	}
	template <class T>
	inline friend bint operator * (bint a, const T &b) {
		return a *= b;
	}

	template <class T>
	inline static pair <bint, T> div (bint a, T b)
		requires (is_integral_v <T> && sizeof (T) <= sizeof (uint)) {
		make_unsigned_t <T> _b = b;
		const bool rev = a.sgn () ^ sgn (b),
			sgna = a.sgn (), sgnb = sgn (b);
		if (sgna) a = -a;
		if (sgnb) _b = -_b;
		ull c = 0;
		for (int i = a.size () - 1; ~i; --i) {
			(c <<= 32) += a.g[i];
			a.g[i] = c / _b, c %= _b;
		}
		if (rev) a = -a;
		if (sgna) c = -c;
		a.shrink ();
		return { a, (T) c };
	}
	inline static pair <bint, bint> div (bint a, bint b) {
		const bool rev = a.sgn () ^ b.sgn (),
			sgna = a.sgn (), sgnb = b.sgn ();
		if (sgna) a = -a;
		if (sgnb) b = -b;
		const int w_a = a.lg (), w_b = b.lg ();
		int k = w_a - w_b;
		if (w_b == -1) throw std::domain_error ("division by zero");
		if (k < 0) return { 0, sgna ? -a : a };
		b <<= k;
		bint q, s, _s;
		q.guarantee (bit_pad (k + 1));
		while (~k) {
			if (_s = s + b, _s <= a)
				s = _s, q.__set_bit (k, 1);
			b >>= 1; --k;
		}
		if (rev) q = -q;
		if (sgna) a = -a, s = -s;
		a -= s; a.shrink (), q.shrink ();
		return { q, a };
	}
	template <class T>
	inline bint friend operator / (const bint &a, const T &b) {
		return div (a, b).fst;
	}
	template <class T>
	inline T friend operator % (const bint &a, const T &b) {
		return div (a, b).scd;
	}
	template <class T>
	inline bint& operator /= (const T &b) {
		return *this = *this / b;
	}
	template <class T>
	inline bint& operator %= (const T &b) {
		return *this = *this % b;
	}
};
inline bint abs (const bint &x) { return x.abs (); }
uint64_t bint::h[BUF_SIZE];