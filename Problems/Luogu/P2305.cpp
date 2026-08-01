#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int V = 1e6;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
LL wfa[N], a[N], b[N], lim[N];
int fa[N];
std::vector<int> son[N];

int rdfn[N], time_stamp;
void prerdfs(int u) {
	rdfn[u] = ++time_stamp;
	for(int i = (int)son[u].size() - 1; i >= 0; i--) {
		int v = son[u][i];
		prerdfs(v);
	}
}
std::vector<std::pair<LL, int>> anc;
LL dep[N];
void predfs(int u) {
	dep[u] = dep[fa[u]] + wfa[u];
	anc.emplace_back(dep[u], u);
	lim[u] = std::lower_bound(anc.begin(), anc.end(), std::make_pair(dep[u] - lim[u], 0))->second;
	for(int v : son[u]) predfs(v);
	anc.pop_back();
}

struct Line {
	LL k, b;
	Line() : k(0), b(LLINF) {}
	Line(LL k_, LL b_) : k(k_), b(b_) {}
	LL at(LL x) const { return k * x + b; }
};
struct SegNode { int ls, rs; Line v; };
struct LiChaoTree {
	SegNode t[N * 20];
	int nw() { static int cnt = 0; return ++cnt; }
	void insert(Line qv, int &x, int l = 0, int r = V) {
		if(!x) x = nw();
		if(l == r) {
			if(t[x].v.at(l) > qv.at(l)) t[x].v = qv;
			return;
		}
		int mid = (l + r) >> 1;
		if(qv.at(mid) < t[x].v.at(mid)) std::swap(t[x].v, qv);
		if(qv.at(l) < t[x].v.at(l)) insert(qv, t[x].ls, l, mid);
		if(qv.at(r) < t[x].v.at(r)) insert(qv, t[x].rs, mid + 1, r);
	}
	LL query(int qx, int x, int l = 0, int r = V) {
		if(!x) return LLINF;
		if(l == r) return t[x].v.at(qx);
		int mid = (l + r) >> 1;
		if(qx <= mid) return std::min(query(qx, t[x].ls, l, mid), t[x].v.at(qx));
		else return std::min(query(qx, t[x].rs, mid + 1, r), t[x].v.at(qx));
	}
};
struct SegmentTree {
	LiChaoTree tr;
	int t[N << 2];
	int mx;
	void build() { for(mx = 1; mx <= n; mx <<= 1); }
	void modify(int x, Line v) { for(x += mx; x; x >>= 1) tr.insert(v, t[x]); }
	LL query(int l, int r, int x) {
		LL ret = LLINF;
		for(l += mx - 1, r += mx + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
			if(~l & 1) ret = std::min(ret, tr.query(x, t[l ^ 1]));
			if(r & 1) ret = std::min(ret, tr.query(x, t[r ^ 1]));
		}
		return ret;
	}
} seg;
LL ans[N];
void dfs(int u) {
	if(u > 1) ans[u] = seg.query(rdfn[lim[u]], rdfn[u], a[u]) + dep[u] * a[u] + b[u];
	seg.modify(rdfn[u], Line(-dep[u], ans[u]));
	for(int v : son[u]) dfs(v);
}

int main() {
	scanf("%d%*d", &n);
	for(int i = 2; i <= n; i++) scanf("%d%lld%lld%lld%lld", &fa[i], &wfa[i], &a[i], &b[i], &lim[i]), son[fa[i]].emplace_back(i);
	seg.build();
	prerdfs(1), predfs(1);
	// for(int i = 1; i <= n; i++) printf("%d: lim=%d, rdfn=%d\n", i, lim[i], rdfn[i]);
	dfs(1);
	for(int i = 2; i <= n; i++) printf("%lld\n", ans[i]);
	return 0;
}