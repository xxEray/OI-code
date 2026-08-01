#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int MAXV = (1 << 16) + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

struct DS {
	LL t[MAXV];
	LL tag;
	std::vector<int> modifies;
	DS() { memset(t, 0x3f, sizeof(t)); }
	void clear() {
		// printf("clear\n");
		tag = 0;
		for(int x : modifies)
			for(int i = 0; i < (1 << 8); i++)
				t[(x & 0xff00) | i] = LLINF;
		modifies.clear();
	}
	void global_add(LL v) { /* printf("global add %lld\n", v); */ tag += v; }
	void insert(int x, LL v) {
		// printf("insert %d %lld\n", x, v);
		modifies.emplace_back(x);
		v -= tag;
		for(int i = 0; i < (1 << 8); i++)
			t[(x & 0xff00) | i] = std::min(t[(x & 0xff00) | i], ((x ^ i) & 0xff) + v);
	}
	LL query(int x) {
		LL ret = LLINF;
		for(int i = 0; i < (1 << 8); i++)
			ret = std::min(ret, t[(i << 8) | (x & 0xff)] + ((x ^ (i << 8)) & 0xff00));
		// printf("query %d = %lld\n", x, ret + tag);
		return ret + tag;
	}
} ds;
LL f[N];
LL vtag;
std::vector<std::pair<int, LL>> vct[N];

int sz[N], hson[N];
void predfs(int u, int fa) {
	a[u] ^= a[fa];
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		predfs(v, u);
		sz[u] += sz[v];
		if(!hson[u] || sz[hson[u]] < sz[v]) hson[u] = v;
	}
}

void dfs(int u, int fa) {
	std::vector<int> son;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && edge[i].to != hson[u]) {
		int v = edge[i].to;
		dfs(v, u);
		son.emplace_back(v);
		for(auto &[x, w] : vct[v]) w += vtag;
		vtag = 0;
		ds.clear();
	}
	if(hson[u]) {
		dfs(hson[u], u);
		vct[u].swap(vct[hson[u]]);
		vtag -= f[hson[u]];
		LL sum = f[hson[u]];
		ds.global_add(-f[hson[u]]);
		f[u] = ds.query(a[fa]);
		vct[u].emplace_back(u, -vtag);
		ds.insert(a[u], 0);
		for(int v : son) {
			sum += f[v];
			for(auto [x, w] : vct[v]) f[u] = std::min(f[u], ds.query(a[x] ^ a[u] ^ a[fa]) + w - f[v]);
			for(auto [x, w] : vct[v]) vct[u].emplace_back(x, w - f[v] - vtag), ds.insert(a[x], w - f[v]);
			vct[v].clear();
		}
		// printf("sum=%lld\n", sum);
		f[u] += sum, vtag += sum, ds.global_add(sum);
		f[u] = std::min(f[u], sum + (a[u] ^ a[fa]));
	} else {
		f[u] = a[u] ^ a[fa], vct[u].emplace_back(u, 0), ds.insert(a[u], 0);
	}
	// printf("%d: f=%lld, vct: ", u, f[u]); for(auto [x, w] : vct[u]) printf("[%d]=%lld ", x, w + vtag); puts("");
}

int main() {
#ifndef DEBUG
	freopen("arcanaeden.in", "r", stdin);
	freopen("arcanaeden.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	predfs(1, 0);
	// for(int i = 1; i <= n; i++) printf("hson[%d] = %d\n", i, hson[i]);
	dfs(1, 0);
	printf("%lld\n", f[1]);
	return 0;
} /*
5
4 2 1 5 4 
1 2
2 3
2 4
1 5

6
*/