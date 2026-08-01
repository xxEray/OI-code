#include <bits/stdc++.h>

const int N = 5e4 + 5;
const int M = 1e6 + 5;

int L, n, m, Q;
char s[M];
char a[11][N];

namespace Solve_sub123 {
	typedef long long LL;
	const LL MOD1 = 1e9 + 21;
	const LL BASE1 = 239;
	const LL MOD2 = 1e9 + 33;
	const LL BASE2 = 307;
	LL power1[M], power2[M];
	template<int size> struct String {
		LL hsh1[size], hsh2[size];
		int sz;
		void init(const char *str, int sz_) {
			sz = sz_;
			for(int i = 1; i <= sz; i++) hsh1[i] = (hsh1[i - 1] * BASE1 + str[i]) % MOD1;
			for(int i = 1; i <= sz; i++) hsh2[i] = (hsh2[i - 1] * BASE2 + str[i]) % MOD2;
		}
		LL hash(int l, int r) const {
			LL h1 = (hsh1[r] - hsh1[l - 1] * power1[r - l + 1] % MOD1 + MOD1) % MOD1;
			LL h2 = (hsh2[r] - hsh2[l - 1] * power2[r - l + 1] % MOD2 + MOD2) % MOD2;
			// printf("%d: hash(%d, %d) = (%lld,%lld)\n", size, l, r, h1, h2);
			return h1 << 31 | h2;
		}
	};
	String<M> hs;
	String<N> ha[11];
	template<int size1, int size2> int lcp(const String<size1> &s1, const String<size2> &s2, int p1, int p2) {
		int l = 0, r = std::min(s1.sz - p1 + 1, s2.sz - p2 + 1) + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(s1.hash(p1, p1 + mid - 1) == s2.hash(p2, p2 + mid - 1)) l = mid + 1;
			else r = mid;
		}
		return l - 1;
	}
	template<int size1, int size2> int rlcp(const String<size1> &s1, const String<size2> &s2, int p1, int p2) {
		int l = 0, r = std::min(p1, p2) + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(s1.hash(p1 - mid + 1, p1) == s2.hash(p2 - mid + 1, p2)) l = mid + 1;
			else r = mid;
		}
		return l - 1;
	}
	struct BIT {
		int t[N];
		void add(int x, int v) { while(x <= m) t[x] += v, x += x & -x; }
		int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
		int query(int l, int r) { return l > r ? 0 : query(r) - query(l - 1); }
	} bit1[11], bit2[11];
	int solve_n1(int x, int y, int p) { return lcp(hs, ha[x], p, y); }
	int solve_n2(int x, int y, int p) {
		int k = lcp(hs, ha[x], p, y);
		if(!k) return 0;
		int q = lcp(hs, ha[x + 1], p + k, y + k - 1);
		return k + q;
	}
	int solve_n3(int x, int y, int p) {
		if(p > L) return 0;
		int k = lcp(hs, ha[x], p, y);
		if(!k) return 0;
		int q = lcp(hs, ha[x + 1], p + k, y + k - 1);
		if(q) {
			int r = lcp(hs, ha[x + 2], p + k + q, y + k + q - 2);
			return k + q + r;
		} else {
			int r1 = rlcp(hs, ha[x + 2], p + k, y + k - 2);
			if(!r1) return k;
			int r2 = lcp(hs, ha[x + 2], p + k, y + k - 2);
			if(bit1[x].query(std::max(y, y + k - 2 - r1 + 1), y + k - 2)) return k + r2;
			else return k;
		}
	}
	int solve_n4(int x, int y, int p) {
		int k = lcp(hs, ha[x], p, y);
		if(!k) return 0;
		int ret = solve_n3(x, y, p);
		ret = std::max(ret, solve_n3(x + 1, y + k - 1, p + k) + k);
		int r1 = rlcp(hs, ha[x + 3], p + k, y + k - 3);
		if(r1) {
			int r2 = lcp(hs, ha[x + 3], p + k, y + k - 3);
			if(bit2[x].query(std::max(y, y + k - 3 - r1 + 1), y + k - 3)) ret = std::max(ret, k + r2);
		}
		if(k >= 2 && a[x + 1][y + k - 2] == s[p + k - 1] && a[x + 2][y + k - 2] == s[p + k]) {
			int r2 = lcp(hs, ha[x + 3], p + k + 1, y + k - 2);
			ret = std::max(ret, k + r2 + 1);
		}
		return ret;
	}
	void main() {
		power1[0] = power2[0] = 1;
		for(int i = 1; i <= 1000000; i++) power1[i] = power1[i - 1] * BASE1 % MOD1;
		for(int i = 1; i <= 1000000; i++) power2[i] = power2[i - 1] * BASE2 % MOD2;
		hs.init(s, L);
		for(int i = 1; i <= n; i++) ha[i].init(a[i], m);
		for(int i = 1; i < n; i++) for(int j = 1; j < m; j++) if(a[i + 1][j] == a[i][j + 1]) bit1[i].add(j, 1);
		for(int i = 1; i < n - 1; i++) for(int j = 1; j < m; j++)
			if(a[i + 1][j] == a[i][j + 1] && a[i + 2][j] == a[i][j + 2]) bit2[i].add(j, 1);
		while(Q--) {
			int x, y, p;
			scanf("%d%d%d", &x, &y, &p);
			if(n - x + 1 == 1) printf("%d\n", solve_n1(x, y, p));
			else if(n - x + 1 == 2) printf("%d\n", solve_n2(x, y, p));
			else if(n - x + 1 == 3) printf("%d\n", solve_n3(x, y, p));
			else if(n - x + 1 == 4) printf("%d\n", solve_n4(x, y, p));
		}
	}
}

namespace Solve_sub4 {
	bool f[11][N];
	void main() {
		while(Q--) {
			int x, y, p;
			scanf("%d%d%d", &x, &y, &p);
			f[x][y] = (a[x][y] == s[p]);
			int ret = 0;
			for(int i = x; i <= n; i++) for(int j = y; j <= m && p + (i - x) + (j - y) <= L; j++) {
				f[i][j] = (i == x && j == y && a[x][y] == s[p]);
				if(i > x) f[i][j] |= f[i - 1][j] && (a[i][j] == s[p + (i - x) + (j - y)]);
				if(j > y) f[i][j] |= f[i][j - 1] && (a[i][j] == s[p + (i - x) + (j - y)]);
				if(f[i][j]) ret = std::max(ret, (i - x) + (j - y) + 1);
			}
			printf("%d\n", ret);
		}
	}
}

int main() {
#ifdef DEBUG
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	scanf("%d%d%d%d", &L, &n, &m, &Q);
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
	if(n <= 4) Solve_sub123::main();
	else if(L <= 20000 && m <= 20000 && Q <= 20000) Solve_sub4::main();
	return 0;
}