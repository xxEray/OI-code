#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 10 + 3;
const int MOD = 998244353;

LL v[N];
int n;

struct Edge { int to, nxt; } edge[N << 1];
int head[N], fa[N];
void add_edge(int u, int v) {
	static int k = 1;
	edge[k] = (Edge){v, head[u]};
	head[u] = k++;
}

LL val[N];
int p[N];

void dfs(int u) {
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa[u]) {
			int v = edge[i].to;
			fa[v] = u;
			dfs(v);
		}
}

void add_subtree(int u, LL vl) {
	(val[u] += vl) %= MOD;
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa[u]) {
			int v = edge[i].to;
			add_subtree(v, vl);
		}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) scanf("%lld", &v[i]);
	for(int i = 1; i <= n; i++) p[i] = i;
	LL ans = 0;
	dfs(1);
	do {
		for(int i = 1; i <= n; i++) val[i] = v[i];
		for(int i = 1; i <= n; i++) {
			add_subtree(p[i], val[p[i]]);	
		}
		for(int i = 1; i <= n; i++) (ans += val[i]) %= MOD;
	} while(std::next_permutation(p + 1, p + n + 1));
	printf("%lld\n", ans);
	return 0;
}