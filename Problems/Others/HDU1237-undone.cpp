// https://acm.hdu.edu.cn/contest/problem?cid=1237&pid=1006
#include <bits/stdc++.h>

typedef long long LL;

const int N = 500 + 5;

int n;
LL a[2 * N];

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }
struct Fraction {
	LL up, dn;
	Fraction() : up(0), dn(1) {}
	Fraction(LL v) : up(v), dn(1) {}
	Fraction(LL u, LL d) : up(u), dn(d) { LL g = gcd(u, d); up /= g, dn /= g; }
};
Fraction operator+(const Fraction &x, const Fraction &y) { return {x.up * y.dn + y.up * x.dn, x.dn * y.dn}; }
Fraction operator-(const Fraction &x, const Fraction &y) { return {x.up * y.dn - y.up * x.dn, x.dn * y.dn}; }
Fraction operator*(const Fraction &x, const Fraction &y) { return {x.up * y.up, x.dn * y.dn}; }
Fraction operator/(const Fraction &x, const Fraction &y) { return {x.up * y.dn, x.dn * y.up}; }

std::pair<Fraction, Fraction> intersect(LL k1, LL b1, LL k2, LL b2) {
	if(k1 == k2) return {{1, 0}, {1, 0}}; // no intersection OR overlap
	// y = k1 x + b1 & y = k2 x + b2
	// => (k1-k2) x + (b1-b2) = 0 => x = (b2-b1) / (k1-k2)
	Fraction x = {b2 - b1, k1 - k2};
	Fraction y = k1 * x + b1;
	return {x, y};
}

struct DSU {
	int cnt[N], ld[N];
	void init() { for(int i = 1; i <= n; i++) cnt[i] = 1, ld[i] = i; }
	int find(int x) { return x == ld[x] ? x : ld[x] = find(ld[x]); }
	void merge(int x, int y) {
		x = find(x), y = find(y);
		if(cnt[x] > cnt[y]) std::swap(x, y);
		ld[x] = y, cnt[y] += cnt[x], cnt[x] = 0;
	}
} dsu;

bool check(std::pair<Fraction, Fraction> &&point) {
	auto &[px, py] = point;
	if(px.dn == 0) return false;
	for(int i = 1; i <= n; i++) {
		
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= 2 * n; i++) scanf("%lld", &a[i]);
		std::sort(a + 1, a + 2 * n + 1);
		auto check_overlap = []() {
			bool fl = true;
			for(int i = 2; i <= n; i++) fl &= (a[i] == a[1] && a[n + i] == a[n + 1]);
			return fl;
		};
		bool flag = check_overlap();
		if(flag) { puts("YES"); continue; }
		auto find_diff = []() {
			int i = 2;
			for(; i <= 2 * n; i++) if(a[i] != a[1]) break;
			if(i <= 2 * n) std::swap(a[i], a[2]), i++;
			for(; i <= 2 * n; i++) if(a[i] != a[2]) break;
			if(i <= 2 * n) std::swap(a[i], a[3]);
		};
		find_diff();
		auto permu = [&flag](int i, int j, int k, int l) {
			flag |= check(intersect(a[i], a[j], a[k], a[l]));
			flag |= check(intersect(a[i], a[j], a[l], a[k]));
			flag |= check(intersect(a[j], a[i], a[k], a[l]));
			flag |= check(intersect(a[j], a[i], a[l], a[k]));
		};
		for(int j = 4; j <= 2 * n; j++) permu(1, 2, 3, j);
		for(int i = 3; i <= 2 * n; i++) for(int j = 3; j <= 2 * n; j++) if(i != j) permu(1, i, 2, j);
		if(a[3] != a[2]) {
			for(int j = 5; j <= 2 * n; j++) permu(2, 3, 4, j);
			for(int i = 4; i <= 2 * n; i++) for(int j = 3; j <= 2 * n; j++) if(i != j) permu(2, i, 3, j);
		}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}