#include <bits/stdc++.h>

const int N = 3e5 + 5;

int n;
int a[N], fa[N];
std::vector<int> son[N];

struct SegmentTree {
	int t[N << 2], lazy[N << 2];
	void setlazy(int x, int v) { t[x] += v, lazy[x] += v; }
	void lazydown(int x) { setlazy(x << 1, lazy[x]), setlazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	void build(int x = 1, int l = 1, int r = n) {
		t[x] = lazy[x] = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void add(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql > qr) return 0;
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::max(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int sz[N], dfn[N], time_stamp;
void predfs(int u) {
	if(son[u].empty()) dfn[u] = time_stamp++, sz[u] = 1;
	else dfn[u] = time_stamp, sz[u] = 0;
	for(int v : son[u]) predfs(v), sz[u] += sz[v];
}
std::map<int, std::vector<std::pair<int, int>>> mp[N];
long long ans;
void dfs(int u) {
	// printf("dfs %d\n", u);
	for(int v : son[u]) {
		dfs(v);
		if(mp[v].count(a[u])) {
			auto &vct = mp[v][a[u]];
			for(auto [l, r] : vct) seg.add(l, r, -1);
			mp[v].erase(a[u]);
		}
		ans = std::max(ans, (long long)(std::max(seg.query(dfn[u], dfn[v] - 1), seg.query(dfn[v] + sz[v], dfn[u] + sz[u] - 1)) + 1) *
			(seg.query(dfn[v], dfn[v] + sz[v] - 1) + 1));
		if(mp[v].size() > mp[u].size()) mp[u].swap(mp[v]);
		for(auto [c, vct2] : mp[v]) {
			auto &vct = mp[u][c];
			vct.insert(vct.end(), vct2.begin(), vct2.end());
		}
		mp[v].clear();
	}
	mp[u][a[u]].emplace_back(dfn[u], dfn[u] + sz[u] - 1);
	seg.add(dfn[u], dfn[u] + sz[u] - 1, 1);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) fa[i] = 0, son[i].clear(), mp[i].clear();
		for(int i = 2; i <= n; i++) scanf("%d", &fa[i]), son[fa[i]].emplace_back(i);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		time_stamp = 1;
		predfs(1);
		// for(int i = 1; i <= n; i++) printf("%d: dfn=%d, sz=%d\n", i, dfn[i], sz[i]);
		seg.build(), ans = 1;
		dfs(1);
		printf("%lld\n", ans);
	}
	return 0;
}