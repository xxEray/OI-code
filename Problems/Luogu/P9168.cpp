#include <cstdio>
#include <algorithm>
#include <array>
#include <set>
#include <vector>
#include <cassert>

typedef long long LL;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m, Q, cnt;
int fa[N];
std::vector<int> son[N];

int b[N * 2], c[N * 2];

LL out[N];

struct SegmentTree {
	int t[N << 2], id[N << 2], lazy[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		lazy[x] = 0, t[x] = 0, id[x] = r;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void setlazy(int x, int val) {
		t[x] += val, lazy[x] += val;
	}
	void lazydown(int x) {
		setlazy(x << 1, lazy[x]), setlazy(x << 1 | 1, lazy[x]);
		lazy[x] = 0;
	}
	void add(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		assert(1 <= ql && ql <= qr && qr <= n);
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]), id[x] = (t[x << 1 | 1] > t[x << 1] ? id[x << 1] : id[x << 1 | 1]);
	}
	int rmost_zero(int ql, int qr, int x = 1, int l = 1, int r = n) {
		assert(1 <= ql && ql <= qr && qr <= n);
		if(ql <= l && r <= qr) return t[x] == 0 ? id[x] : 0;
		int mid = (l + r) >> 1, ret = 0;
		lazydown(x);
		if(ql <= mid) ret = std::max(ret, rmost_zero(ql, qr, x << 1, l, mid));
		if(qr > mid) ret = std::max(ret, rmost_zero(ql, qr, x << 1 | 1, mid + 1, r));
		return ret;
	}
	std::pair<int, int> minpos(int ql, int qr, int x = 1, int l = 1, int r = n) {
		assert(1 <= ql && ql <= qr && qr <= n);
		if(ql <= l && r <= qr) return {t[x], id[x]};
		int mid = (l + r) >> 1;
		std::pair<int, int> ret = {INF, 0};
		lazydown(x);
		if(ql <= mid) ret = std::min(ret, minpos(ql, qr, x << 1, l, mid));
		if(qr > mid) ret = std::min(ret, minpos(ql, qr, x << 1 | 1, mid + 1, r));
		return ret;
	}
	// int get(int qind, int x = 1, int l = 1, int r = n) {
	// 	assert(1 <= qind && qind <= n);
	// 	if(l == r) return t[x];
	// 	int mid = (l + r) >> 1;
	// 	lazydown(x);
	// 	if(qind <= mid) return get(qind, x << 1, l, mid);
	// 	else return get(qind, x << 1 | 1, mid + 1, r);
	// }
	void set(int qind, int qv, int x = 1, int l = 1, int r = n) {
		assert(1 <= qind && qind <= n);
		if(l == r) { t[x] = qv; return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qind <= mid) set(qind, qv, x << 1, l, mid);
		else set(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]), id[x] = (t[x << 1 | 1] > t[x << 1] ? id[x << 1] : id[x << 1 | 1]);
	}
};
struct HeavyLightDecomposition {
	SegmentTree seg;
	int dfn[N], sz[N], top[N], dep[N], hson[N], idfn[N];
	int time_stamp;
	void init() {
		seg.build();
		dfs1(1), dfs2(1, 1);
	}
	void dfs1(int u) {
		sz[u] = 1;
		for(int v : son[u]) {
			dep[v] = dep[u] + 1;
			dfs1(v);
			sz[u] += sz[v];
		}
	}
	void dfs2(int u, int tp) {
		dfn[u] = ++time_stamp, idfn[dfn[u]] = u;
		top[u] = tp;
		for(int v : son[u]) if(!hson[u] || sz[hson[u]] < sz[v]) hson[u] = v;
		if(hson[u]) dfs2(hson[u], tp);
		for(int v : son[u]) if(hson[u] != v) dfs2(v, v);
	}
	int go(int u) {
		while(u) {
			int val = seg.rmost_zero(dfn[top[u]], dfn[u]);
			if(val) return idfn[val];
			u = fa[top[u]];
		}
		return 0;
	}
	std::pair<int, int> min(int u) { auto p = seg.minpos(dfn[u], dfn[u] + sz[u] - 1); return {p.first, idfn[p.second]}; }
	// int get(int u) { return seg.get(dfn[u]); }
	void set(int u, int val) { seg.set(dfn[u], val); }
	void add(int u, int v, int val) {
		while(top[u] != top[v]) {
			if(dep[top[u]] < dep[top[v]]) std::swap(u, v);
			seg.add(dfn[top[u]], dfn[u], val);
			u = fa[top[u]];
		}
		if(dep[u] > dep[v]) std::swap(u, v);
		seg.add(dfn[u], dfn[v], val);
	}
	int lca(int u, int v) {
		while(top[u] != top[v]) {
			if(dep[top[u]] < dep[top[v]]) std::swap(u, v);
			u = fa[top[u]];
		}
		return dep[u] < dep[v] ? u : v;
	}
} cap, hld;

std::multiset<int> vals[N];
std::vector<std::array<int, 5>> ops;
LL ans = 0;
void init() {
	for(int i = 1; i <= n; i++) vals[i].insert(0), hld.set(i, 0);
}
void undo() {
	// fprintf(stderr, "undo\n");
	auto p = ops.back();
	ops.pop_back();
	if(p[0] == 0 && p[1] == 0 && p[2] == 0 && p[3] == 0) return;
	int i = p[0], j = p[1], nv = p[2], jv = p[3];
	ans -= nv - jv;
	assert(vals[i].find(nv) != vals[i].end());
	vals[i].erase(vals[i].find(nv));
	hld.set(i, vals[i].empty() ? INF : *vals[i].begin());
	vals[j].insert(jv);
	hld.set(j, vals[j].empty() ? INF : *vals[j].begin());
	int lca = hld.lca(i, j);
	cap.add(i, lca, 1);
	cap.add(lca, j, -1);
	// fprintf(stderr, "    ans = %lld\n", ans);
}
void insert(int i) {
	// fprintf(stderr, "insert #%d (node=%d, v=%d)\n", i, b[i], c[i]);
	int nv = c[i];
	i = b[i];
	int f = cap.go(i);
	assert(f);
	auto p = hld.min(f);
	int jv = p.first, j = p.second;
	// fprintf(stderr, "    f=%d, to=%d, replace=%d\n", f, j, jv);
	if(nv - jv < 0) {
		ops.push_back({0, 0, 0, 0});
		// fprintf(stderr, "    skipped\n");
		return;
	}
	ops.push_back({i, j, nv, jv});
	ans += nv - jv;
	vals[i].insert(nv);
	hld.set(i, vals[i].empty() ? INF : *vals[i].begin());
	assert(vals[j].find(jv) != vals[j].end());
	vals[j].erase(vals[j].find(jv));
	hld.set(j, vals[j].empty() ? INF : *vals[j].begin());
	int lca = hld.lca(i, j);
	cap.add(i, lca, -1);
	cap.add(lca, j, 1);
	// fprintf(stderr, "    ans = %lld\n", ans);
}
LL getanswer() {
	// fprintf(stderr, "answer\n");
	return ans;
}

struct CdqByTime {
	std::vector<int> t[N << 2];
	void add(int ql, int qr, int qid, int x = 1, int l = 1, int r = Q) {
		if(ql <= l && r <= qr) { t[x].push_back(qid); return; }
		int mid = (l + r) >> 1;
		if(ql <= mid) add(ql, qr, qid, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qid, x << 1 | 1, mid + 1, r);
	}
	void solve(int x = 1, int l = 1, int r = Q) {
		for(int j : t[x]) insert(j);
		if(l == r) out[l] = getanswer();
		else {
			int mid = (l + r) >> 1;
			solve(x << 1, l, mid), solve(x << 1 | 1, mid + 1, r);
		}
		for(int j = 0; j < (int)t[x].size(); j++) undo();
	}
} cdq;

int st[N * 2], ed[N * 2];

int main() {
	// freopen("D:\\Temp\\transfer\\transfer9.in", "r", stdin);
	// freopen("D:\\Temp\\transfer\\transfer9.out", "w", stdout);
	scanf("%*d%d%d%d", &n, &m, &Q);
	for(int i = 2; i <= n; i++) scanf("%d", &fa[i]), son[fa[i]].push_back(i);
	for(int i = 1; i <= m; i++) scanf("%d%d", &b[i], &c[i]), st[i] = 1;
	cnt = m;
	Q++;
	for(int i = 2; i <= Q; i++) {
		int t;
		scanf("%d", &t);
		if(t == 1) {
			cnt++;
			scanf("%d%d", &b[cnt], &c[cnt]);
			st[cnt] = i;
		} else {
			int x;
			scanf("%d", &x);
			ed[x] = i - 1;
		}
	}
	for(int i = 1; i <= cnt; i++) if(ed[i] == 0) ed[i] = Q;
	for(int i = 1; i <= cnt; i++) cdq.add(st[i], ed[i], i);
	hld.init(), cap.init();
	init();
	cdq.solve();
	assert(ops.empty());
	for(int i = 1; i < Q; i++) printf("%lld ", out[i]);
	printf("%lld\n", out[Q]);
	return 0;
}