#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline long long qread() {
	char c = getchar();
	int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline long long Abs(const long long& x) {return (x > 0 ? x : -x);}
inline long long Max(const long long& x, const long long& y) {return (x > y ? x : y);}
inline long long Min(const long long& x, const long long& y) {return (x < y ? x : y);}

const int N = 300005, M = 600005;
const long long MINF = -0x3f3f3f3f3f3f3f3f;

struct Point {
	long long x, y;
	Point(long long x = 0, long long y = 0) : x(x), y(y) {}
	inline Point operator + (const Point& b) const {return Point(x + b.x, y + b.y);}
	inline Point operator - (const Point& b) const {return Point(x - b.x, y - b.y);}
	inline long long operator * (const Point& b) const {return x * b.y - y * b.x;}
	inline bool operator <= (const Point& b) const {return (*this) * b >= 0;}
};

long long addv, a[N], ans[M];

struct Hull {
	vector <Point> vc;
	int pnt;
	Hull() {pnt = 0;}
	inline Point operator [](const int& idx) const {return vc[idx];}
	inline void Insert(const Point& a) {vc[a.x].y = Max(vc[a.x].y, a.y);}
	inline void Pushback(const Point& a) {vc.push_back(a);}
	inline void Empty(int len) {
		vc.clear();
		vc.push_back(Point(0, 0));
		for (int i = 1;i <= len;i++) vc.push_back(Point(i, MINF));
	}
	inline void Convex() {
		int siz = vc.size();
		if (siz <= 2) return;
		int top = 1;
		for (int i = 2;i < siz;i++) {
			if (vc[i].y == MINF) continue;
			while (top > 0 && vc[top] - vc[top - 1] <= vc[i] - vc[top - 1]) top--;
			vc[++top] = vc[i];
		}
		for (int i = 1;i < siz - top;i++) vc.pop_back();
	}
	inline long long Maxv() {
		int siz = vc.size();
		while (pnt < siz - 1 && addv * (vc[pnt + 1].x - vc[pnt].x) + vc[pnt + 1].y - vc[pnt].y > 0) pnt++;
		return addv * vc[pnt].x + vc[pnt].y;
	}
};

struct Result {
	long long lmax, rmax, midmax, sum;
	Result(long long lmax = 0, long long rmax = 0, long long midmax = 0, long long sum = 0)
		: lmax(lmax), rmax(rmax), midmax(midmax), sum(sum) {}
	Result operator + (const Result& b) const {
		return Result(Max(lmax, sum + b.lmax), Max(b.rmax, b.sum + rmax), Max(Max(midmax, b.midmax), rmax + b.lmax), sum + b.sum);
	}
};

struct Segtree {
	Hull lmax[N << 2], rmax[N << 2], ans[N << 2];
	long long sum[N << 2];
	inline void preSufMerge(Hull& c, Hull& a, Hull& b, Point addb) {
		int siza = a.vc.size(), sizb = b.vc.size();
		for (int i = 0;i < siza;i++) c.Pushback(a[i]);
		for (int i = 0;i < sizb;i++) c.Pushback(addb + b[i]);
		c.Convex();
	}
	inline void Minkowski(Hull& c, Hull& a, Hull& b) {
		int i = 0, j = 0, siza = a.vc.size(), sizb = b.vc.size();
		c.Insert(a[i] + b[j]);
		while (i < siza - 1 && j < sizb - 1) {
			if (a[i + 1] - a[i] <= b[j + 1] - b[j]) {
				j++;
				c.Insert(a[i] + b[j]);
			} else {
				i++;
				c.Insert(a[i] + b[j]);
			}
		}
		while (i < siza - 1) {
			i++;
			c.Insert(a[i] + b[j]);
		}
		while (j < sizb - 1) {
			j++;
			c.Insert(a[i] + b[j]);
		}
	}
	inline void Build(int p, int l, int r) {
		if (l == r) {
			lmax[p].Pushback(Point(0, 0));
			lmax[p].Pushback(Point(1, a[l]));
			rmax[p].Pushback(Point(0, 0));
			rmax[p].Pushback(Point(1, a[l]));
			ans[p].Pushback(Point(0, 0));
			ans[p].Pushback(Point(1, a[l]));
			sum[p] = a[l];
			return;
		}
		int mid = l + r >> 1;
		Build(p << 1, l, mid);
		Build(p << 1 | 1, mid + 1, r);
		// Calculate Prefix
		preSufMerge(lmax[p], lmax[p << 1], lmax[p << 1 | 1], Point(mid - l + 1, sum[p << 1]));
		// Calculate Suffix
		preSufMerge(rmax[p], rmax[p << 1 | 1], rmax[p << 1], Point(r - mid, sum[p << 1 | 1]));
		// Calculate Ans
		ans[p].Empty(r - l + 1);
		int siz = ans[p << 1].vc.size();
		for (int i = 0;i < siz;i++) ans[p].Insert(ans[p << 1][i]);
		siz = ans[p << 1 | 1].vc.size();
		for (int i = 0;i < siz;i++) ans[p].Insert(ans[p << 1 | 1][i]);
		Minkowski(ans[p], rmax[p << 1], lmax[p << 1 | 1]);
		ans[p].Convex();
		// Calculate Sum
		sum[p] = sum[p << 1] + sum[p << 1 | 1];
	}
	inline Result Query(int p, int pl, int pr, int l, int r) {
		if (pl == l && pr == r) return Result(lmax[p].Maxv(), rmax[p].Maxv(), ans[p].Maxv(), sum[p] + 1ll * (r - l + 1) * addv);
		int mid = pl + pr >> 1;
		if (mid >= r) return Query(p << 1, pl, mid, l, r);
		else if (mid + 1 <= l) return Query(p << 1 | 1, mid + 1, pr, l, r);
		else return Query(p << 1, pl, mid, l, mid) + Query(p << 1 | 1, mid + 1, pr, mid + 1, r);
	}
};

struct Query {
	int l, r, idx;
	long long addv;
	bool operator < (const Query& b) const {return addv < b.addv;}
};

int n, m, q;
Segtree sgt;
Query qry[M];

inline void Read() {
	n = qread(); m = qread();
	for (int i = 1;i <= n;i++) a[i] = qread();
	for (int i = 1;i <= m;i++) {
		int opt = qread();
		if (opt == 1) addv += qread();
		else {q++; qry[qry[q].idx = q].l = qread(); qry[q].r = qread(); qry[q].addv = addv;}
	}
	m = q;
}

inline void Solve() {
	sort(qry + 1, qry + m + 1);
	for (int i = 1;i <= n;i++) a[i] += qry[1].addv;
	for (int i = m;i >= 1;i--) qry[i].addv -= qry[1].addv;
	sgt.Build(1, 1, n);
	for (int i = 1;i <= m;i++) {
		addv = qry[i].addv;
		ans[qry[i].idx] = sgt.Query(1, 1, n, qry[i].l, qry[i].r).midmax;
	}
	for (int i = 1;i <= m;i++) printf("%lld\n", ans[i]);
}

int main() {
	Read();
	Solve();
	return 0;
}