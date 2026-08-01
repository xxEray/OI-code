#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 2e5 + 5;
const int M = 3e5 + 5;
const int MAXQ = 5e5 + 5;

int n, m, Q;
int a[N];
struct Edge { int u, v; } e[M];
bool exist[M];

struct Query { int t, u, l, r; } q[MAXQ];

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int prv[N], nxt[N], lft[N], rgt[N];
void merge(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) return;
	nxt[rgt[x]] = lft[y], prv[lft[y]] = rgt[x];
	fa[x] = y;
	lft[y] = lft[x];
}

int id[N];

struct SegmentTree {
	int t[N << 2], tid[N << 2];
	void modify(int qind, int qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = qv, tid[x] = l; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
		tid[x] = (t[x << 1] == t[x] ? tid[x << 1] : tid[x << 1 | 1]);
	}
	std::pair<int, int> query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return {t[x], tid[x]};
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::max(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

void get_id() {
	int c = 0;
	for(int i = 1; i <= n; i++) if(!id[i])
		for(int j = lft[find(i)]; j; j = nxt[j])
			id[j] = ++c;
	assert(c == n);
}

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) scanf("%d%d", &e[i].u, &e[i].v);
	for(int i = 1; i <= Q; i++) scanf("%d%d", &q[i].t, &q[i].u);
	for(int i = 1; i <= m; i++) exist[i] = true;
	for(int i = 1; i <= n; i++) fa[i] = i, prv[i] = nxt[i] = 0, lft[i] = rgt[i] = i;
	for(int i = 1; i <= Q; i++) if(q[i].t == 2) exist[q[i].u] = false;
	for(int i = 1; i <= m; i++) if(exist[i]) merge(e[i].u, e[i].v);
	for(int i = Q; i >= 1; i--) if(q[i].t == 2) merge(e[q[i].u].u, e[q[i].u].v);
	get_id();
	// for(int i = 1; i <= n; i++) printf("id[%d] = %d\n", i, id[i]);
	for(int i = 1; i <= n; i++) fa[i] = i, prv[i] = nxt[i] = 0, lft[i] = rgt[i] = i;
	for(int i = 1; i <= m; i++) if(exist[i]) merge(e[i].u, e[i].v);
	for(int i = Q; i >= 1; i--)
		if(q[i].t == 2) merge(e[q[i].u].u, e[q[i].u].v);
		else q[i].l = id[lft[find(q[i].u)]], q[i].r = id[rgt[find(q[i].u)]];
	for(int i = 1; i <= n; i++) seg.modify(id[i], a[i]);
	for(int i = 1; i <= Q; i++) if(q[i].t == 1) {
		// printf("q[%d]: [%d .. %d]\n", i, q[i].l, q[i].r);
		auto p = seg.query(q[i].l, q[i].r);
		printf("%d\n", p.first);
		seg.modify(p.second, 0);
	}
	return 0;
} /*
6 5 8
1 2 6 3 4 5
2 4
1 3
1 6
3 5
2 5
1 1
1 4
1 1
2 1
2 5
2 2
2 3
1 4
*/