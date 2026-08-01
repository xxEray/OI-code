#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e4 + 5;
const int V = 1e5 + 5;
const int MX = 2e4;

int n;

double a[N][4];
int b[N][4];
double valr[N], valc[N];
struct Node { int l, r, v; };
std::vector<Node> vct[N];

double tmp[N * 2];
bool cmp(double x, double y) { return x - y < -1e-8; }
bool eq(double x, double y) { return std::abs(x - y) < 1e-8; }
void discrete() {
	int c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i][0], tmp[++c] = a[i][2];
	std::sort(tmp + 1, tmp + c + 1, cmp);
	c = std::unique(tmp + 1, tmp + c + 1, eq) - tmp - 1;
	for(int i = 1; i <= n; i++) {
		b[i][0] = std::lower_bound(tmp + 1, tmp + c + 1, a[i][0], cmp) - tmp;
		b[i][2] = std::lower_bound(tmp + 1, tmp + c + 1, a[i][2], cmp) - tmp;
	}
	c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i][1], tmp[++c] = a[i][3];
	std::sort(tmp + 1, tmp + c + 1, cmp);
	c = std::unique(tmp + 1, tmp + c + 1, eq) - tmp - 1;
	for(int i = 1; i <= n; i++) {
		b[i][1] = std::lower_bound(tmp + 1, tmp + c + 1, a[i][1], cmp) - tmp;
		b[i][3] = std::lower_bound(tmp + 1, tmp + c + 1, a[i][3], cmp) - tmp;
	}
}

struct SegNode { int mn; double cnt, all; double val() const { return mn == 0 ? all - cnt : all; } };
SegNode calc(SegNode x, SegNode y) {
	SegNode z;
	z.mn = std::min(x.mn, y.mn);
	z.all = x.all + y.all;
	z.cnt = x.cnt * (z.mn == x.mn) + y.cnt * (z.mn == y.mn);
	return z;
}
struct SegmentTree {
	SegNode t[N << 2];
	int lazy[N << 2];
	void set_lazy(int x, int v) { t[x].mn += v, lazy[x] += v; }
	void lazy_down(int x) { set_lazy(x << 1, lazy[x]), set_lazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	void build(int x = 1, int l = 1, int r = MX) {
		lazy[x] = 0;
		if(l == r) { t[x].mn = 0, t[x].all = t[x].cnt = valc[l] - valc[l - 1]; return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	void modify(int ql, int qr, int qv, int x = 1, int l = 1, int r = MX) {
		if(ql <= l && r <= qr) { set_lazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	SegNode query(int ql, int qr, int x = 1, int l = 1, int r = MX) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int main() {
	int T = 0;
	while(scanf("%d", &n) == 1 && n) {
		for(int i = 1; i <= MX; i++) vct[i].clear();
		for(int i = 1; i <= n; i++) scanf("%lf%lf%lf%lf", &a[i][0], &a[i][1], &a[i][2], &a[i][3]);
		discrete();
		for(int i = 1; i <= n; i++) {
			vct[b[i][0]].push_back({b[i][1] + 1, b[i][3], 1});
			vct[b[i][2]].push_back({b[i][1] + 1, b[i][3], -1});
			valr[b[i][0]] = a[i][0], valr[b[i][2]] = a[i][2], valc[b[i][1]] = a[i][1], valc[b[i][3]] = a[i][3];
		}
		seg.build();
		double ans = 0;
		for(int i = 1; i <= MX; i++) {
			for(auto &p : vct[i]) seg.modify(p.l, p.r, p.v);
			ans += seg.query(1, MX).val() * (valr[i + 1] - valr[i]);
		}
		printf("Test case #%d\nTotal explored area: %.2f\n\n", ++T, ans);
	}
	return 0;
}