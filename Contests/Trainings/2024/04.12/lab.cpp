#include <bits/stdc++.h>

const int N = 5e4 + 5;
const int INF = 0x3f3f3f3f;
const int FBD = 0x3f3f3ffb;
const int NONE = 0x3f3f3ffe;

int n, Q;
struct Node { int x, v; } a[N];
int tmp[N];
int cn;

struct Node2 { int d, l, r, vl, vr; } b[N];
int ver[N];

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

struct SegNode { int val, mn, mx; SegNode() : val(0), mn(NONE), mx(NONE) {} };
struct SegmentTree {
	SegNode t[N * 80];
	int ls[N * 80], rs[N * 80];
	int tot;
	int copy(int x) { tot++; t[tot] = t[x], ls[tot] = ls[x], rs[tot] = rs[x]; return tot; }
	SegNode calc(const SegNode &x, const SegNode &y) const {
		SegNode z;
		z.val = gcd(x.val, y.val);
		if(x.mx != NONE && x.mx != FBD && y.mn != NONE && y.mn != FBD) z.val = gcd(z.val, std::abs(y.mn - x.mx));
		if(x.mn != NONE) z.mn = x.mn;
		else z.mn = y.mn;
		if(y.mx != NONE) z.mx = y.mx;
		else z.mx = x.mx;
		return z;
	}
	int insert0(int qind, int qv, int y, int l = 1, int r = a[n].x) {
		int x = copy(y);
		if(l == r) {
			t[x].val = gcd(t[x].val, qv);
//			assert(t[x].mn == FBD && t[x].mx == FBD);
			return x;
		}
		int mid = (l + r) >> 1;
		if(qind <= mid) ls[x] = insert0(qind, qv, ls[x], l, mid);
		else rs[x] = insert0(qind, qv, rs[x], mid + 1, r);
		t[x] = calc(t[ls[x]], t[rs[x]]);
		return x;
	}
	int insertl(int qind, int qv, int y, int l = 1, int r = a[n].x) {
		int x = copy(y);
		if(l == r) {
			if(qv != FBD && t[x].mn != NONE && t[x].mn != FBD) t[x].val = gcd(t[x].val, std::abs(t[x].mn - qv));
			t[x].mn = qv;
			return x;
		}
		int mid = (l + r) >> 1;
		if(qind <= mid) ls[x] = insertl(qind, qv, ls[x], l, mid);
		else rs[x] = insertl(qind, qv, rs[x], mid + 1, r);
		t[x] = calc(t[ls[x]], t[rs[x]]);
		return x;
	}
	int insertr(int qind, int qv, int y, int l = 1, int r = a[n].x) {
		int x = copy(y);
		if(l == r) {
			if(qv != FBD && t[x].mx != NONE && t[x].mx != FBD) t[x].val = gcd(t[x].val, std::abs(t[x].mx - qv));
			t[x].mx = qv;
			return x;
		}
		int mid = (l + r) >> 1;
		if(qind <= mid) ls[x] = insertr(qind, qv, ls[x], l, mid);
		else rs[x] = insertr(qind, qv, rs[x], mid + 1, r);
		t[x] = calc(t[ls[x]], t[rs[x]]);
		return x;
	}
	SegNode query(int ql, int qr, int x, int l = 1, int r = a[n].x) const {
		if(!x) return SegNode();
		if(l == r) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, ls[x], l, mid);
		else if(ql > mid) return query(ql, qr, rs[x], mid + 1, r);
		else return calc(query(ql, qr, ls[x], l, mid), query(ql, qr, rs[x], mid + 1, r));
	}
} seg;

int main() {
//#ifndef DEBUG
	freopen("lab.in", "r", stdin);
	freopen("lab.out", "w", stdout);
//#endif
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i].v);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i].x);
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.x < y.x; });
	for(int i = 1; i <= n; i++) tmp[i] = a[i].x, a[i].x = a[i - 1].x + (i == 1 || tmp[i] != tmp[i - 1]);
	for(int i = 1; i < n; i++) b[i].l = a[i].x, b[i].r = a[i + 1].x, b[i].d = tmp[i + 1] - tmp[i], b[i].vl = a[i].v, b[i].vr = a[i + 1].v;
	std::sort(b + 1, b + n, [&](Node2 x, Node2 y) { return x.d < y.d; });
	for(int  i = 1; i <= n; i++) ver[0] = seg.insertl(a[i].x, FBD, ver[0]), ver[0] = seg.insertr(a[i].x, FBD, ver[0]);
	for(int i = 1; i < n; i++) {
		if(b[i].l == b[i].r) ver[i] = seg.insert0(b[i].l, std::abs(b[i].vl - b[i].vr), ver[i - 1]);
		else {
			ver[i] = seg.insertr(b[i].l, b[i].vl, ver[i - 1]);
			ver[i] = seg.insertl(b[i].r, b[i].vr, ver[i]);
		}
	}
//	for(int i = 1; i < n; i++) printf("[%d] %d %d %d %d\n", i, b[i].l, b[i].r, b[i].vl, b[i].vr);
	while(Q--) {
		int x, y, l, r;
		scanf("%d%d%d%d", &x, &y, &l, &r);
		l = a[std::lower_bound(tmp + 1, tmp + n + 1, l) - tmp].x;
		r = a[std::upper_bound(tmp + 1, tmp + n + 1, r) - tmp - 1].x;
		x = std::abs(x - y);
		if(x & 1) { printf("-1 "); continue; }
		x >>= 1;
		int lft = 1, rgt = n;
		while(lft < rgt) {
			int mid = (lft + rgt) >> 1;
			int v = seg.query(l, r, ver[mid]).val;
			if(v && x % v == 0) rgt = mid;
			else lft = mid + 1;
		}
//		printf("lft = %d\n", lft);
//		printf("val = %d\n", seg.query(l, r, ver[lft]).val);
		if(lft == n) printf("-1 ");
		else printf("%d ", b[lft].d);
	}
	return 0;
} /*
3 1
1 6 11
1 1 1
1 11 1 1
*/