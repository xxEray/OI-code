#include <cstdio>
#include <algorithm>
#include <cassert>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m, Q;

int c;
struct Node { int sx, sy, tx, ty, d, t, id; } a[N * 2];
struct Point { int x, y; } st[N * 2], ed[N * 2];
int goi[N * 2][51], d[N * 2];
LL gov[N * 2][51], qt[N];

const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // U, R, D, L

struct SegmentTree {
	int t[N << 2], lazy[N << 2];
	void build(int x = 1, int l = 0, int r = m) {
		if(l == r) { t[x] = 0, lazy[x] = -1; return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = 0, lazy[x] = -1;
	}
	void set_lazy(int x, int v) { if(v != -1) t[x] = lazy[x] = v; }
	void lazy_down(int x) {
		set_lazy(x << 1, lazy[x]), set_lazy(x << 1 | 1, lazy[x]);
		lazy[x] = -1;
	}
	void set(int ql, int qr, int qv, int x = 1, int l = 0, int r = m) {
		if(ql > qr) std::swap(ql, qr);
		if(ql <= l && r <= qr) { set_lazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(ql <= mid) set(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) set(ql, qr, qv, x << 1 | 1, mid + 1, r);
	}
	int query(int qind, int x = 1, int l = 0, int r = m) {
		if(l == r) return t[x];
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(qind <= mid) return query(qind, x << 1, l, mid);
		else return query(qind, x << 1 | 1, mid + 1, r);
	}
} seg;

bool in(int x, int y, int z) { return std::min(x, z) <= y && y <= std::max(x, z); }
int dist(int x1, int y1, int x2, int y2) { return std::abs(x1 - x2) + std::abs(y1 - y2); }
void solve(bool (*cmp)(Node, Node), int dd, bool type) {
	std::sort(a + 1, a + c + 1, cmp);
	seg.build();
	for(int i = 1; i <= c; i++) {
		if(a[i].d == dd) {
			assert(type ? (a[i].sx == a[i].tx) : (a[i].sy == a[i].ty));
			goi[a[i].id + a[i].t * n][0] = seg.query(type ? a[i].sx : a[i].sy);
			int ii = goi[a[i].id + a[i].t * n][0];
			if(ii && a[i].t == 1 && in(st[ii].x, a[i].sx, ed[ii].x) && in(st[ii].y, a[i].sy, ed[ii].y))
				d[a[i].id + n] = d[ii];
			if(ii) gov[a[i].id + a[i].t * n][0] = dist(a[i].tx, a[i].ty, ed[ii].x, ed[ii].y);
		}
		if(a[i].t == 0) {
			seg.set(type ? a[i].sx : a[i].sy, type ? a[i].tx : a[i].ty, a[i].id);
		}
	}
}

bool double_key(int x, int y, int p, int q, int t) { return x == y ? p < q : ((x < y) ^ t); }

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		c++;
		scanf("%d%d%d%d", &a[c].sx, &a[c].sy, &a[c].tx, &a[c].ty), a[c].id = i, a[c].t = 0;
		if(a[c].sx == a[c].tx) a[c].d = a[c].sy < a[c].ty ? 0 : 2;
		else a[c].d = a[c].sx < a[c].tx ? 1 : 3;
		st[i] = {a[c].sx, a[c].sy}, ed[i] = {a[c].tx, a[c].ty}, d[i] = a[c].d;
	}
	scanf("%d", &Q);
	for(int i = 1; i <= Q; i++) {
		char ch[2];
		c++;
		scanf("%d%d%s%lld", &a[c].sx, &a[c].sy, ch, &qt[i]), a[c].tx = a[c].sx, a[c].ty = a[c].sy, a[c].t = 1, a[c].id = i;
		if(ch[0] == 'U') a[c].d = 0;
		else if(ch[0] == 'R') a[c].d = 1;
		else if(ch[0] == 'D') a[c].d = 2;
		else a[c].d = 3;
		ed[i + n] = {a[c].tx, a[c].ty}, d[i + n] = a[c].d;
	}
	assert(c == n + Q);
	for(int i = 1; i <= c; i++) goi[i][0] = 0, gov[i][0] = LLINF;
	solve([](Node x, Node y) { return double_key(std::max(x.sy, x.ty), std::max(y.sy, y.ty), x.t, y.t, 1); }, 0, 1);
	solve([](Node x, Node y) { return double_key(std::max(x.sx, x.tx), std::max(y.sx, y.tx), x.t, y.t, 1); }, 1, 0);
	solve([](Node x, Node y) { return double_key(std::min(x.sy, x.ty), std::min(y.sy, y.ty), x.t, y.t, 0); }, 2, 1);
	solve([](Node x, Node y) { return double_key(std::min(x.sx, x.tx), std::min(y.sx, y.tx), x.t, y.t, 0); }, 3, 0);
	for(int j = 1; j <= 50; j++)
		for(int i = 1; i <= c; i++) {
			goi[i][j] = goi[goi[i][j - 1]][j - 1];
			gov[i][j] = std::min(gov[i][j - 1] + gov[goi[i][j - 1]][j - 1], LLINF);
		}
	for(int o = 1; o <= Q; o++) {
		int i = o + n;
		LL t = qt[o];
		for(int k = 50; k >= 0; k--)
			if(gov[i][k] <= t)
				t -= gov[i][k], i = goi[i][k];
		assert(i);
		int j = goi[i][0], x = ed[i].x, y = ed[i].y;
		if(j == 0) {
			t = std::min(t, (LL)m);
			int tx = std::min((LL)m, std::max(x + dir[d[i]][0] * t, 0LL));
			int ty = std::min((LL)m, std::max(y + dir[d[i]][1] * t, 0LL));
			printf("%d %d\n", tx, ty);
		} else {
			int tt = std::min({t, (LL)m, (LL)(d[i] % 2 ? std::abs(ed[j].x - ed[i].x) : std::abs(ed[j].y - ed[i].y))});
			x += tt * dir[d[i]][0], y += tt * dir[d[i]][1];
			t -= tt;
			x += t * dir[d[j]][0], y += t * dir[d[j]][1];
			printf("%d %d\n", x, y);
		}
	}
	return 0;
} /*
7 10
1 10 1 6
4 7 4 8
6 10 6 8
0 4 0 9
5 1 2 1
5 7 5 2
3 8 2 8
1
5 1 R 1
*/