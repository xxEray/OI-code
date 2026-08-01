#include <cstdio>
#include <algorithm>
#include <climits>
#include <cassert>

const int N = 1e5 + 5;
const int LOG_N = 23;
const int M = 5e5 + 5;

int n, m;
struct Node { int x, y, w, t; } a[2 * N];
struct Query { int l, r; } q[M];
struct Point { int x, y, w, id; } p[2 * N * LOG_N + M];
int cp;
int out[M];

void chkmax(int &x, int y) { if(x < y) x = y; }

int segmx;
struct SegmentTree {
	int t[(2 * N + M) << 2];
	void build(int x = 1, int l = 1, int r = segmx) {
		if(l == r) { t[x] = INT_MIN; return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = INT_MIN;
	}
	void modify(int qind, int qv, int x = 1, int l = 1, int r = segmx) {
		assert(qind <= segmx);
		if(l == r) { chkmax(t[x], qv); return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = segmx) {
		assert(1 <= ql && ql <= qr && qr <= segmx);
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1, ret = INT_MIN;
		if(ql <= mid) chkmax(ret, query(ql, qr, x << 1, l, mid));
		if(qr > mid) chkmax(ret, query(ql, qr, x << 1 | 1, mid + 1, r));
		return ret;
	}
} seg;

int tmp[N + M];
void discrete() {
	int c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i].x;
	for(int i = 1; i <= m; i++) tmp[++c] = q[i].l;
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i].x = std::lower_bound(tmp + 1, tmp + c + 1, a[i].x) - tmp;
	for(int i = 1; i <= m; i++) q[i].l = std::lower_bound(tmp + 1, tmp + c + 1, q[i].l) - tmp;
	c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[n + i].x;
	for(int i = 1; i <= m; i++) tmp[++c] = q[i].r;
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[n + i].x = std::lower_bound(tmp + 1, tmp + c + 1, a[n + i].x) - tmp;
	for(int i = 1; i <= m; i++) q[i].r = std::lower_bound(tmp + 1, tmp + c + 1, q[i].r) - tmp;
}

void cdq(int l, int r) {
	if(l >= r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid), cdq(mid + 1, r);
	int lid = 0, rid = 0;
	for(int i = l; i <= mid; i++) if(a[i].t == 0 && (!lid || a[lid].w < a[i].w)) lid = i;
	for(int i = mid + 1; i <= r; i++) if(a[i].t == 1 && (!rid || a[rid].w < a[i].w)) rid = i;
	if(lid) for(int i = mid + 1; i <= r; i++) if(a[i].t == 1) p[++cp] = {a[lid].x, a[i].x, a[lid].w + a[i].w, 0};
	if(rid) for(int i = l; i <= mid; i++) if(a[i].t == 0) p[++cp] = {a[i].x, a[rid].x, a[i].w + a[rid].w, 0};
}

int main() {
// #ifndef DEBUG
// 	freopen("sandwich.in", "r", stdin);
// 	freopen("sandwich.out", "w", stdout);
// #endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].w), a[i].t = 0;
	for(int i = 1; i <= n; i++) scanf("%d%d%d", &a[n + i].x, &a[n + i].y, &a[n + i].w), a[n + i].t = 1;
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) scanf("%d%d", &q[i].l, &q[i].r);
	discrete();
	std::sort(a + 1, a + 2 * n + 1, [](Node x, Node y) { return x.y < y.y; });
	cdq(1, 2 * n);
	for(int i = 1; i <= m; i++) p[++cp] = {q[i].l, q[i].r, 0, i};
	segmx = 2 * n + m;
	for(int i = 1; i <= m; i++) out[i] = INT_MIN;
	seg.build();
	std::sort(p + 1, p + cp + 1, [](Point x, Point y) { return x.x < y.x; });
	for(int i = 1; i <= cp; i++) {
		if(p[i].id) chkmax(out[p[i].id], seg.query(p[i].y, segmx));
		else seg.modify(p[i].y, p[i].w);
	}
	seg.build();
	std::sort(p + 1, p + cp + 1, [](Point x, Point y) { return x.x > y.x; });
	for(int i = 1; i <= cp; i++) {
		if(p[i].id) chkmax(out[p[i].id], seg.query(1, p[i].y));
		else seg.modify(p[i].y, p[i].w);
	}
	for(int i = 1; i <= m; i++)
		if(out[i] == INT_MIN) puts("-1");
		else printf("%d\n", out[i]);
	return 0;
}