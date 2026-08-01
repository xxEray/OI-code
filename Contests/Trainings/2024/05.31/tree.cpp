#include <bits/stdc++.h>

#define msg(...) fprintf(stderr, __VA_ARGS__)

typedef long long LL;

const int N = 1e6 + 5;

int n, Q;
int fa[N];
std::set<int> son[N];

int fath[N], hson[N];
int find(int x) { return x == fath[x] ? x : fath[x] = find(fath[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fath[x] = y, hson[y] = hson[x] : 0; }

struct FHQ {
	int ls[N], rs[N], fa[N], sz[N], w[N];
	LL v[N], mx[N];
	void build() { for(int i = 1; i <= n; i++) sz[i] = 1, w[i] = rand(); }
	void pushup(int x) {
		fa[ls[x]] = fa[rs[x]] = x;
		sz[x] = sz[ls[x]] + sz[rs[x]] + 1;
		mx[x] = std::max({mx[ls[x]], mx[rs[x]], v[x]});
	}
	int merge(int x, int y) {
		if(!x || !y) return x ^ y;
		if(w[x] > w[y]) { rs[x] = merge(rs[x], y); pushup(x); return x; }
		else { ls[y] = merge(x, ls[y]); pushup(y); return y; }
	}
	void split(int rt, int size, int &x, int &y) {
		if(!rt) { x = y = 0; return; }
		if(sz[ls[rt]] >= size) y = rt, split(ls[rt], size, x, ls[y]), pushup(y), fa[y] = 0;
		else x = rt, split(rs[rt], size - sz[ls[rt]] - 1, rs[x], y), pushup(x), fa[x] = 0;
	}
	void modify(int x, LL val) {
		while(ls[x]) x = ls[x];
		v[x] = val;
		while(x) pushup(x), x = fa[x];
	}
	LL query(int x, int k) {
		int y, z;
		split(x, k, y, z);
		LL ret = mx[z];
		x = merge(y, z);
		return ret;
	}
	LL get(int x) const {
		while(ls[x]) x = ls[x];
		return v[x];
	}
	void traverse(int x) const {
		if(!x) return;
		traverse(ls[x]);
		printf("%lld(%d) ", v[x], x);
		traverse(rs[x]);
	}
} treap;

int dfn[N], idfn[N], dep[N], sz[N], time_stamp;
int id[N];
void dfs(int u) {
	dep[u] = dep[fa[u]] + 1;
	dfn[u] = ++time_stamp, idfn[dfn[u]] = u;
	sz[u] = 1;
	for(int v : son[u]) dfs(v), sz[u] += sz[v];
}

struct SegmentTree {
	LL t[N << 2];
	int mx;
	void build() { for(mx = 1; mx <= n; mx <<= 1); }
	void modify(int x, LL v) {
		x += mx;
		t[x] = v;
		for(x >>= 1; x; x >>= 1) t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	LL query(int l, int r) {
		LL ret = 0;
		for(l += mx - 1, r += mx + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
			if(~l & 1) ret = std::max(ret, t[l ^ 1]);
			if(r & 1) ret = std::max(ret, t[r ^ 1]);
		}
		return ret;
	}
} seg;

std::set<int> st;

int main() {
// #ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.ans", "w", stdout);
// #endif
	scanf("%d%d", &n, &Q);
	seg.build(), treap.build();
	for(int i = 1; i <= n; i++) id[i] = i, fath[i] = i, hson[i] = i;
	for(int i = 1; i <= n; i++) { LL w; scanf("%lld", &w); treap.modify(id[i], w); }
	for(int i = 2; i <= n; i++) scanf("%d", &fa[i]), son[fa[i]].emplace(i);
	dfs(1);
	for(int u = n; u >= 1; u--)
		if(u > 1 && son[u].size() <= 1 && son[fa[u]].size() <= 1)
			merge(u, fa[u]), id[fa[u]] = treap.merge(id[fa[u]], id[u]), son[fa[u]].erase(u);
	for(int i = 1; i <= n; i++) if(find(i) == i) seg.modify(dfn[i], treap.query(id[i], 0)), st.emplace(dfn[i]);
	// printf("seg: "); for(int i = 1; i <= n; i++) printf("[%d](%d)%lld ", i, idfn[i], seg.query(i, i)); puts("");
	// printf("st: "); for(int x : st) printf("%d ", idfn[x]); puts("");
	// for(int i = 1; i <= n; i++) {
	// 	printf("%d: ", i);
	// 	if(find(i) == i) treap.traverse(id[i]);
	// 	puts("");
	// }
	// puts("============");
	LL lastans = 0;
	while(Q--) {
		int t; LL u;
		scanf("%d%lld", &t, &u);
		// u ^= lastans;
		// printf("u = %d\n", u);
		if(t == 2) {
			std::vector<int> vct;
			for(auto it = st.lower_bound(dfn[u]); it != st.end() && *it <= dfn[u] + sz[u] - 1; it++) vct.emplace_back(idfn[*it]);
			std::sort(vct.begin(), vct.end(), [&](int x, int y) { return dep[x] < dep[y]; });
			if(find(u) != u) {
				int d = dep[u] - dep[find(u)];
				int p, q, r;
				treap.split(id[find(u)], d, p, q);
				treap.split(q, 1, q, r);
				if(!son[hson[find(u)]].empty()) {
					LL val = 0;
					for(int vv : son[hson[find(u)]]) val += treap.get(id[vv]);
					id[hson[find(u)]] = q;
					treap.modify(q, val);
					r = treap.merge(r, q);
				}
				id[find(u)] = treap.merge(p, r);
				seg.modify(dfn[find(u)], treap.query(id[find(u)], 0));
			}
			for(int v : vct) {
				LL val = 0;
				if(son[v].empty()) {
					int p, q;
					treap.split(id[v], 1, p, q);
					id[v] = q;
					if(!son[hson[v]].empty()) {
						LL val2 = 0;
						for(int vv : son[hson[v]]) val2 += treap.get(id[vv]);
						id[hson[v]] = p;
						treap.modify(id[hson[v]], val2);
						id[v] = treap.merge(id[v], id[hson[v]]);
					}
					val = treap.get(id[v]);
				} else for(int vv : son[v]) val += treap.get(id[vv]);
				// printf("v = %d, val = %lld\n", v, val);
				if(val || !son[v].empty()) {
					treap.modify(id[v], val);
					if(v > 1 && son[v].size() <= 1 && son[fa[v]].size() <= 1) {
						st.erase(dfn[v]);
						seg.modify(dfn[v], 0);
						merge(v, fa[v]);
						id[find(v)] = treap.merge(id[find(v)], id[v]);
						seg.modify(dfn[find(v)], treap.query(id[find(v)], 0));
						son[fa[v]].erase(v);
					} else {
						seg.modify(dfn[v], treap.query(id[v], 0));
					}
				} else {
					treap.modify(id[v], 0);
					st.erase(dfn[v]);
					seg.modify(dfn[v], 0);
					son[fa[v]].erase(v);
				}
			}
		} else {
			LL ret = seg.query(dfn[u], dfn[u] + sz[u] - 1);
			int d = dep[u] - dep[find(u)];
			ret = std::max(ret, treap.query(id[find(u)], d));
			lastans = ret;
			printf("%lld\n", ret);
		}
		// printf("find: "); for(int i = 1; i <= n; i++) printf("[%d]%d ", i, find(i)); puts("");
		// printf("seg: "); for(int i = 1; i <= n; i++) printf("[%d](%d)%lld ", i, idfn[i], seg.query(i, i)); puts("");
		// printf("st: "); for(int x : st) printf("%d ", idfn[x]); puts("");
		// for(int i = 1; i <= n; i++) {
		// 	printf("%d: ", i);
		// 	if(find(i) == i) treap.traverse(id[i]);
		// 	puts("");
		// }
		// puts("============");
	}
	return 0;
} /*
7 8
5 6 6 12 5 8 15 
1 2 3 4 4 6 
2 5
2 2
2 3
2 6
2 5
2 4
2 6
1 1
*/