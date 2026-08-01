#include <bits/stdc++.h>

const int N = 1e5 + 5;
const double eps = 1e-6;

int n, m;
struct Node { int t, x, i1, i2, id; } a[N];

double val1[N], val2[N];
int c1, c2;
void discrete(double v) {
	auto cmp = [&](double x, double y) { return x < y - eps; };
	c1 = 0;
	for(int i = 1; i <= n; i++) val1[++c1] = a[i].x - v * a[i].t;
	std::sort(val1 + 1, val1 + c1 + 1);
	c1 = std::unique(val1 + 1, val1 + c1 + 1, [&](double x, double y) { return std::abs(x - y) <= eps; }) - val1 - 1;
	for(int i = 1; i <= n; i++) a[i].i1 = std::lower_bound(val1 + 1, val1 + c1 + 1, a[i].x - v * a[i].t, cmp) - val1;
	c2 = 0;
	for(int i = 1; i <= n; i++) val2[++c2] = a[i].x + v * a[i].t;
	std::sort(val2 + 1, val2 + c2 + 1);
	c2 = std::unique(val2 + 1, val2 + c2 + 1, [&](double x, double y) { return std::abs(x - y) <= eps; }) - val2 - 1;
	for(int i = 1; i <= n; i++) a[i].i2 = std::lower_bound(val2 + 1, val2 + c2 + 1, a[i].x + v * a[i].t, cmp) - val2;
}

struct SegmentTree {
	int t[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		t[x] = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int qind, int qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = std::max(t[x], qv); return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql > qr) return 0;
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::max(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int f[N];
bool check(double v) {
	// printf("check %.6f\n", v);
	discrete(v);
	// printf("val1: "); for(int i = 1; i <= c1; i++) printf("%.2f ", val1[i]); puts("");
	// printf("val2: "); for(int i = 1; i <= c2; i++) printf("%.2f ", val2[i]); puts("");
	// printf("i1: "); for(int i = 1; i <= n; i++) printf("%d ", a[i].i1); puts("");
	// printf("i2: "); for(int i = 1; i <= n; i++) printf("%d ", a[i].i2); puts("");
	seg.build();
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.i1 < y.i1; });
	int ans = 0;
	for(int i = 1; i <= n; ) {
		int oi = i;
		while(i <= n && a[i].i1 == a[oi].i1) {
			f[i] = seg.query(1, a[i].i2 - 1) + 1;
			// printf("f[%d] = %d\n", a[i].id, f[i]);
			i++;
		}
		i = oi;
		while(i <= n && a[i].i1 == a[oi].i1) {
			ans = std::max(ans, f[i]);
			seg.modify(a[i].i2, f[i]);
			i++;
		}
	}
	bool flag = true;
	for(int i = 1; i <= n; i++) flag &= (a[i].t * v >= std::abs(a[i].x) - eps);
	return ans <= m + 1 && flag;
}

int main() {
#ifndef DEBUG
	freopen("avatar.in", "r", stdin);
	freopen("avatar.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	n++, a[1].t = a[1].x = 0;
	for(int i = 2; i <= n; i++) scanf("%d%d", &a[i].t, &a[i].x), a[i].id = i;
	double l = 0, r = 2.01e6;
	int cnt = 0;
	while(l + eps < r && ++cnt <= 40) {
		double mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid;
	}
	printf("%.6f\n", l);
	return 0;
}