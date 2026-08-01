#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dd[N];

LL ans = 0, anscnt = 0;
void update(LL val, LL cnt) {
	if(val > ans) ans = val, anscnt = cnt;
	else if(val == ans) anscnt += cnt;
}
int mx[N], cnt[N];
void dfs(int u, int fa, int d) {
	mx[u] = -INF, cnt[u] = 0;
	int sc = -INF;
	bool leaf = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		leaf = false;
		dfs(v, u, d + 1);
		if(mx[v] + 1 > mx[u]) sc = mx[u], mx[u] = mx[v] + 1, cnt[u] = cnt[v];
		else if(mx[v] + 1 == mx[u]) cnt[u] += cnt[v];
		else if(mx[v] + 1 > sc) sc = mx[v] + 1;
	}
	if(leaf) { mx[u] = 0, cnt[u] = 1; update(0, 1); return; }
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		if(mx[u] == mx[v] + 1 && cnt[u] == cnt[v]) { if(sc >= 0) update((LL)(mx[v] + d + 1) * sc, cnt[v]); }
		else update((LL)(mx[v] + d + 1) * mx[u], cnt[v]);
	}
}

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); dd[u]++, dd[v]++; }
	for(int i = 1; i <= n; i++) if(dd[i] == 1) dfs(i, 0, 0);
	printf("%lld %lld\n", ans, anscnt / 2);
	return 0;
}