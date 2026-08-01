#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <bits/extc++.h>
using namespace __gnu_pbds;

typedef tree<int, null_type, std::less<int>, rb_tree_tag, tree_order_statistics_node_update> Treap;

const int N = 2e5 + 5;

int n, Q;
int a[N], b[N], pa[N], pb[N];

// int c[N * 50][2], w[N * 50], v[N * 50], sz[N * 50];
// int nw(int val) { static int tot = 0; tot++; w[tot] = rand() << 15 | rand(); v[tot] = val; sz[tot] = 1; return tot; }
// struct FHQ {
// 	int rt;
// 	void pushup(int x) { sz[x] = sz[c[x][0]] + sz[c[x][1]] + 1; }
// 	void split(int rt, int val, int &x, int &y) {
// 		if(!rt) { x = y = 0; return; }
// 		if(v[rt] <= val) x = rt, split(c[rt][1], val, c[x][1], y), pushup(x);
// 		else y = rt, split(c[rt][0], val, x, c[y][0]), pushup(y);
// 	}
// 	int merge(int x, int y) {
// 		if(!x || !y) return x ^ y;
// 		if(w[x] > w[y]) { c[x][1] = merge(c[x][1], y), pushup(x); return x; }
// 		else { c[y][0] = merge(x, c[y][0]), pushup(y); return y; }
// 	}
// 	void insert(int val) {
// 		int x, y;
// 		split(rt, val, x, y);
// 		rt = merge(x, merge(nw(val), y));
// 	}
// 	void erase(int val) {
// 		int x, y, z;
// 		split(rt, val - 1, x, y);
// 		split(y, val, y, z);
// 		rt = merge(x, z);
// 	}
// 	int query(int vl, int vr) {
// 		int x, y, z;
// 		split(rt, vl - 1, x, y);
// 		split(y, vr, y, z);
// 		int ret = sz[y];
// 		rt = merge(x, merge(y, z));
// 		return ret;
// 	}
// };
struct BIT {
	Treap t[N << 2];
	void insert(int qx, int qy) {
		while(qx <= n) {
			t[qx].insert(qy);
			qx += qx & -qx;
		}
	}
	void erase(int qx, int qy) {
		while(qx <= n) {
			t[qx].erase(qy);
			qx += qx & -qx;
		}
	}
	int query(int qxr, int qyl, int qyr) {
		int ret = 0;
		while(qxr) {
			ret += t[qxr].order_of_key(qyr + 1) - t[qxr].order_of_key(qyl);
			qxr -= qxr & -qxr;
		}
		return ret;
	}
	int query(int qxl, int qxr, int qyl, int qyr) { return query(qxr, qyl, qyr) - (qxl > 1 ? query(qxl - 1, qyl, qyr) : 0); }
} seg;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), pa[a[i]] = i;
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]), pb[b[i]] = i;
	for(int i = 1; i <= n; i++) seg.insert(pa[i], pb[i]);
	while(Q--) {
		int t;
		scanf("%d", &t);
		if(t == 1) {
			int xl, xr, yl, yr;
			scanf("%d%d%d%d", &xl, &xr, &yl, &yr);
			printf("%d\n", seg.query(xl, xr, yl, yr));
		} else {
			int x, y;
			scanf("%d%d", &x, &y);
			seg.erase(pa[b[x]], pb[b[x]]), seg.erase(pa[b[y]], pb[b[y]]);
			std::swap(b[x], b[y]);
			pb[b[x]] = x, pb[b[y]] = y;
			seg.insert(pa[b[x]], pb[b[x]]), seg.insert(pa[b[y]], pb[b[y]]);
		}
	}
	return 0;
}