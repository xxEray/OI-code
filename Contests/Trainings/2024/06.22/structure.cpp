#include <bits/stdc++.h>

const int N = 1e5 + 5;
const int M = 5e5 + 5;

int n, m;
struct Node { int x, y, w; } a[N], b[N];
struct Query { int l, r, id; } q[M];

int cax, cbx, cy;
int tmp[M * 2];
void discrete() {
	int c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i].x;
	for(int i = 1; i <= m; i++) tmp[++c] = q[i].l;
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i].x = std::lower_bound(tmp + 1, tmp + c + 1, a[i].x) - tmp;
	for(int i = 1; i <= m; i++) q[i].l = std::lower_bound(tmp + 1, tmp + c + 1, q[i].l) - tmp;
	cax = c;
	c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = b[i].x;
	for(int i = 1; i <= m; i++) tmp[++c] = q[i].r;
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) b[i].x = std::lower_bound(tmp + 1, tmp + c + 1, b[i].x) - tmp;
	for(int i = 1; i <= m; i++) q[i].r = std::lower_bound(tmp + 1, tmp + c + 1, q[i].r) - tmp;
	cbx = c;
	c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i].y, tmp[++c] = b[i].y;
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i].y = std::lower_bound(tmp + 1, tmp + c + 1, a[i].y) - tmp;
	for(int i = 1; i <= n; i++) b[i].y = std::lower_bound(tmp + 1, tmp + c + 1, b[i].y) - tmp;
	cy = c;
}

std::vector<std::pair<int, int>> vct;

struct BIT {
	int t[N + M];
	void clear() { for(int i = 0; i <= cbx; i++) t[i] = 0; }
	void modify(int x, int v) { while(x <= cbx) t[x] = std::max(t[x], v), x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret = std::max(ret, t[r]), r -= r & -r; return ret; }
} bit;

int id[2 * N];
void cdq(int l, int r) {
	if(l == r) return;
	int mid = (l + r) >> 1;
	int mxl = 0, mxr = 0;
	for(int i = l; i <= mid; i++) if(id[i] < 0) if(!mxl || a[mxl].w < a[-id[i]].w) mxl = -id[i];
	for(int i = mid + 1; i <= r; i++) if(id[i] > 0) if(!mxr || b[mxr].w < b[id[i]].w) mxr = id[i];
	if(mxl && mxr) {
		for(int i = l; i <= mid; i++) if(id[i] < 0) vct.emplace_back(-id[i], mxr);
		for(int i = mid + 1; i <= r; i++) if(id[i] > 0) vct.emplace_back(mxl, id[i]);
	}
	cdq(l, mid), cdq(mid + 1, r);
}

int out[M];

int main() {
#ifndef DEBUG
	freopen("structure.in", "r", stdin);
	freopen("structure.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].w);
	for(int i = 1; i <= n; i++) scanf("%d%d%d", &b[i].x, &b[i].y, &b[i].w);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	discrete();
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.y < y.y; });
	std::sort(b + 1, b + n + 1, [&](Node x, Node y) { return x.y < y.y; });
	// for(int i = 1; i <= n; i++) printf("%d ", b[i].x);
	for(int i = 1; i <= n; i++) id[a[i].y] = -i;
	for(int i = 1; i <= n; i++) id[b[i].y] = i;
	cdq(1, cy);
	std::sort(q + 1, q + m + 1, [&](Query x, Query y) { return x.l < y.l; });
	std::sort(vct.begin(), vct.end(), [&](std::pair<int, int> x, std::pair<int, int> y) {
		return std::make_pair(a[x.first].x, b[x.second].x) < std::make_pair(a[y.first].x, b[y.second].x);
	});
	vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
	// for(auto [x, y] : vct) printf("(%d, %d)\n", x, y);
	for(int i = 1, j = 0; i <= m; i++) {
		while(j < (int)vct.size() && a[vct[j].first].x < q[i].l) bit.modify(cbx - b[vct[j].second].x + 1, a[vct[j].first].w + b[vct[j].second].w), j++;
		out[q[i].id] = std::max(out[q[i].id], bit.query(cbx - q[i].r + 1));
	}
	bit.clear();
	std::reverse(q + 1, q + m + 1), std::reverse(vct.begin(), vct.end());
	for(int i = 1, j = 0; i <= m; i++) {
		while(j < (int)vct.size() && a[vct[j].first].x > q[i].l) bit.modify(b[vct[j].second].x, a[vct[j].first].w + b[vct[j].second].w), j++;
		out[q[i].id] = std::max(out[q[i].id], bit.query(q[i].r));
	}
	for(int i = 1; i <= m; i++) printf("%d\n", out[i] ? out[i] : -1);
	return 0;
} /*
2
-3 1 1s
-6 3 10
5 2 1000
3 4 100
5
-5 4
-2 6
-4 1
-10 10
-1 2
*/