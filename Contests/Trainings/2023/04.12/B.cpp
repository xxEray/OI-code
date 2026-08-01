#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <cassert>

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m, Q;
int c[N];
struct Node { int l, r, id; } a[N];
bool operator<(Node x, Node y) { return x.l == y.l ? x.r > y.r : x.l < y.l; }
std::set<int> st[N];

struct SegmentTree {
	int t[N << 2];
	int e;
	int (*calc)(int, int);
	void build(int x = 1, int l = 1, int r = n) {
		t[x] = e;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
	void modify(int qind, int qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = qv; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
} segl, segr;
int mymin(int x, int y) { return x < y ? x : y; }
int mymax(int x, int y) { return x > y ? x : y; }

std::vector<int> sons[N];
int fa[N];
void build_tree() {
	std::vector<int> stk;
	for(int i = 1; i <= m; i++) {
		while(!stk.empty() && a[stk.back()].r < a[i].r) stk.pop_back();
		fa[i] = (stk.empty() ? 0 : stk.back());
		if(!stk.empty()) sons[stk.back()].push_back(i);
		stk.push_back(i);
	}
//	for(int i = 1; i <= m; i++) {
//		printf("%d(fa=%d): sons, ", i, fa[i]);
//		for(int j : sons[i]) printf("%d ", j);
//		puts("");
//	}
}

struct DSU {
	int fath[N];
	void init() { for(int i = 1; i <= m; i++) fath[i] = i; }
	int find(int x) { return x == fath[x] ? x : fath[x] = find(fath[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fath[x] = y : 0; }
} dsu;

int tmp[N], belong[N];
void preprocess() {
	for(int i = 0; i <= n; i++) tmp[i] = i + 1;
	for(int i = m; i >= 1; i--) {
		for(int j = tmp[a[i].l - 1]; j <= a[i].r; j = tmp[j]) assert(belong[j] == 0), belong[j] = i;
		tmp[a[i].l - 1] = tmp[a[i].r];
	}
	// printf("belong: "); for(int i = 1; i <= n; i++) printf("%d ", belong[i]); puts("");
}

int ans[N];
int done[N];

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= n; i++) { scanf("%d", &c[i]); st[c[i]].insert(i); }
	for(int i = 1; i <= m; i++) scanf("%d%d", &a[i].l, &a[i].r), a[i].id = i;
	std::sort(a + 1, a + m + 1);
	// for(int i = 1; i <= m; i++) printf("%d: [%d, %d]\n", i, a[i].l, a[i].r);
	segl.e = -INF, segl.calc = mymax, segr.e = INF, segr.calc = mymin;
	segl.build(), segr.build();
	build_tree();
	for(int i = 1; i <= n; i++) {
		int last = 0;
		for(int j : st[i]) segl.modify(j, last), last = j;
		last = n + 1;
		for(auto it = st[i].rbegin(); it != st[i].rend(); it++) segr.modify(*it, last), last = *it;
	}
	preprocess();
	dsu.init();
	for(int i = 1; i <= m; i++)
		ans[i] = (segl.query(a[i].l, a[i].r) >= a[i].l || segr.query(a[i].l, a[i].r) <= a[i].r ? Q + 1 : 0);
	for(int i = 1; i <= m; i++) if(ans[i] != Q + 1) done[fa[i]]++, dsu.merge(i, fa[i]);
	for(int tm = 1; tm <= Q; tm++) {
		int k, x;
		scanf("%d%d", &k, &x);
		st[c[k]].erase(k);
		auto it = st[c[k]].upper_bound(k);
		int q = (it == st[c[k]].end() ? n + 1 : *it);
		int p = (it == st[c[k]].begin() ? 0 : *--it);
		// printf("old: p=%d, q=%d\n", p, q);
		if(p != 0) segr.modify(p, q);
		if(q != n + 1) segl.modify(q, p);
		c[k] = x;
		it = st[c[k]].upper_bound(k);
		q = (it == st[c[k]].end() ? n + 1 : *it);
		p = (it == st[c[k]].begin() ? 0 : *--it);
		// printf("new: p=%d, q=%d\n", p, q);
		segl.modify(k, p), segr.modify(k, q);
		if(p != 0) segr.modify(p, k);
		if(q != n + 1) segl.modify(q, k);
		st[c[k]].insert(k);
		// printf("segl: "); for(int i = 1; i <= n; i++) printf("%d ", segl.query(i, i)); puts("");
		// printf("segr: "); for(int i = 1; i <= n; i++) printf("%d ", segr.query(i, i)); puts("");
		int u = belong[k];
		// printf("u = %d\n", u);
		if(done[u] != (int)sons[u].size()) continue;
		u = dsu.find(u);
		while(u) {
			if(done[u] != (int)sons[u].size()) break;
			if(segl.query(a[u].l, a[u].r) >= a[u].l || segr.query(a[u].l, a[u].r) <= a[u].r) break;
			// printf("update %d\n", u);
			dsu.merge(u, fa[u]);
			ans[u] = std::min(ans[u], tm), done[fa[u]]++;
			u = fa[u];
		}
	}
	for(int i = 1; i <= m; i++) if(fa[i]) ans[i] = std::min(ans[i], ans[fa[i]]);
	int out = 0;
	// printf("ans: "); for(int i = 1; i <= m; i++) printf("%d ", ans[i]); puts("");
	for(int i = 1; i <= m; i++) ans[i] = (ans[i] == Q + 1 ? m + a[i].id : ans[i]), out ^= ans[i];
	// printf("ans: "); for(int i = 1; i <= m; i++) printf("%d ", ans[i]); puts("");
	printf("%d\n", out);
	return 0;
} /*
6 6 5
1 2 1 2 1 2 
1 6
5 5
4 5
3 5
2 5
1 5
5 2
4 3
2 1
3 4
1 5
*/