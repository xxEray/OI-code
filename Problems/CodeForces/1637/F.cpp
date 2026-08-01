#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int a[N];
int n;

int val[N], mxid[N], son[N];
void dfs(int u, int fa) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		son[u]++;
		if(mxid[u] == 0 || val[mxid[v]] > val[mxid[u]]) mxid[u] = mxid[v];
	}
	if(!son[u]) { mxid[u] = u, val[u] = a[u]; return; }
	val[mxid[u]] = std::max(val[mxid[u]], a[u]);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	if(n == 2) { printf("%d\n", std::max(a[1], a[2]) * 2); return 0; }
	int rt = 0;
	for(int i = 1; i <= n; i++) {
		int cnt = 0;
		for(int j = head[i]; j; j = edge[j].nxt) cnt++;
		if(cnt > 1) { rt = i; break; }
	}
	// printf("rt = %d\n", rt);
	dfs(rt, 0);
	int mxa = 0;
	for(int i = 1; i <= n; i++) mxa = std::max(mxa, a[i]);
	int mx = 0, scmx = 0;
	for(int i = head[rt]; i; i = edge[i].nxt) {
		int v = mxid[edge[i].to];
		if(mx == 0 || val[v] > val[mx]) scmx = mx, mx = v;
		else if(scmx == 0 || val[v] >= val[scmx]) scmx = v;
	}
	// for(int i = 1; i <= n; i++) printf("val[%d] = %d\n", i, val[i]);
	val[mx] = val[scmx] = mxa;
	// printf("mx = %d, scmx = %d\n", mx, scmx);
	// for(int i = 1; i <= n; i++) printf("val[%d] = %d\n", i, val[i]);
	LL ans = 0;
	for(int i = 1; i <= n; i++) ans += val[i];
	printf("%lld\n", ans);
	return 0;
} /*
8
1 1 16 16 1 1 7 7
1 3
4 6
4 8
2 4
2 1
7 4
5 7
*/