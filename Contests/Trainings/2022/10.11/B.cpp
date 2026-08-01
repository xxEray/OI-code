#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int N = 5e4 + 5;
const int INF = 0x3f3f3f3f;

int n, Q;
int a[N];
int rv[N * 2], q[N][4];

int tmp[N * 2], cnt;
void discrete() {
	for(int i = 1; i <= n; i++) tmp[++cnt] = a[i];
	for(int i = 1; i <= Q; i++) if(q[i][0] != 2) tmp[++cnt] = (q[i][0] == 3 ? q[i][2] : q[i][3]);
	std::sort(tmp + 1, tmp + cnt + 1);
	cnt = std::unique(tmp + 1, tmp + cnt + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) {
		int tp = a[i];
		a[i] = std::lower_bound(tmp + 1, tmp + cnt + 1, a[i]) - tmp;
		rv[a[i]] = tp;
	}
	for(int i = 1; i <= Q; i++) if(q[i][0] != 2) {
		auto &v = (q[i][0] == 3 ? q[i][2] : q[i][3]);
		int tp = v;
		v = std::lower_bound(tmp + 1, tmp + cnt + 1, v) - tmp;
		rv[v] = tp;
	}
}

int c[N * 60][2], sz[N * 60], v[N * 60], w[N * 60];
int tot;
struct FHQ {
	int root;
	int nw(int val) { tot++, c[tot][0] = c[tot][1] = 0, sz[tot] = 1, v[tot] = val, w[tot] = rand() * rand(); return tot; }
	void pushup(int x) { sz[x] = sz[c[x][0]] + sz[c[x][1]] + 1; }
	int merge(int x, int y) {
		if(!x || !y) return x ^ y;
		if(w[x] < w[y]) { c[x][1] = merge(c[x][1], y), pushup(x); return x; }
		else { c[y][0] = merge(x, c[y][0]), pushup(y); return y; }
	}
	void split(int rt, int val, int &x, int &y) {
		if(!rt) { x = y = 0; return; }
		if(v[rt] <= val) x = rt, split(c[x][1], val, c[x][1], y), pushup(x);
		else y = rt, split(c[y][0], val, x, c[y][0]), pushup(y);
	}
	void insert(int val) {
		int x, y;
		split(root, val - 1, x, y);
		root = merge(x, merge(nw(val), y));
	}
	void erase(int val) {
		int x, y, z;
		split(root, val - 1, x, y);
		split(y, val, y, z);
		if(y) y = merge(c[y][0], c[y][1]);
		root = merge(x, merge(y, z));
	}
	int count(int l, int r) {
		int x, y, z;
		split(root, l - 1, x, y);
		split(y, r, y, z);
		int ret = sz[y];
		root = merge(x, merge(y, z));
		return ret;
	}
};
struct SegmentTree {
	FHQ t[N << 3];
	void erase(int qind, int qv, int x = 1, int l = 1, int r = cnt) {
		if(l == r) { t[x].erase(qind); return; }
		int mid = (l + r) >> 1;
		if(qv <= mid) erase(qind, qv, x << 1, l, mid);
		else erase(qind, qv, x << 1 | 1, mid + 1, r);
		t[x].erase(qind);
	}
	void insert(int qind, int qv, int x = 1, int l = 1, int r = cnt) {
		if(l == r) { t[x].insert(qind); return; }
		int mid = (l + r) >> 1;
		if(qv <= mid) insert(qind, qv, x << 1, l, mid);
		else insert(qind, qv, x << 1 | 1, mid + 1, r);
		t[x].insert(qind);
	}
	int count(int ql, int qr, int qv, int x = 1, int l = 1, int r = cnt) {
		if(l == r) return t[x].count(ql, qr);
		int mid = (l + r) >> 1;
		if(qv <= mid) return count(ql, qr, qv, x << 1, l, mid);
		else return t[x << 1].count(ql, qr) + count(ql, qr, qv, x << 1 | 1, mid + 1, r);
	}
	int at(int ql, int qr, int qind, int x = 1, int l = 1, int r = cnt) {
		if(l == r) return rv[l];
		int mid = (l + r) >> 1, sz = t[x << 1].count(ql, qr);
		if(sz >= qind) return at(ql, qr, qind, x << 1, l, mid);
		else return at(ql, qr, qind - sz, x << 1 | 1, mid + 1, r);
	}
	int prev(int ql, int qr, int qind) { return at(ql, qr, count(ql, qr, qind - 1)); }
	int next(int ql, int qr, int qind) { return at(ql, qr, count(ql, qr, qind) + 1); }
} seg;

int main() {
	srand(time(0));
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= Q; i++)
		scanf("%d", &q[i][0]), q[i][0] == 3 ? scanf("%d%d", &q[i][1], &q[i][2]) : scanf("%d%d%d", &q[i][1], &q[i][2], &q[i][3]);
	discrete();
	for(int i = 1; i <= n; i++) seg.insert(i, a[i]);
	for(int i = 1; i <= Q; i++) {
		int type = q[i][0], l, r, p, x, k;
		if(type == 1) l = q[i][1], r = q[i][2], x = q[i][3], printf("%d\n", seg.count(l, r, x - 1) + 1);
		else if(type == 2) l = q[i][1], r = q[i][2], k = q[i][3], printf("%d\n", seg.at(l, r, k));
		else if(type == 3) p = q[i][1], x = q[i][2], seg.erase(p, a[p]), seg.insert(p, x), a[p] = x;
		else if(type == 4) l = q[i][1], r = q[i][2], x = q[i][3], printf("%d\n", seg.prev(l, r, x));
		else if(type == 5) l = q[i][1], r = q[i][2], x = q[i][3], printf("%d\n", seg.next(l, r, x));
		else return -1;
	}
	return 0;
}