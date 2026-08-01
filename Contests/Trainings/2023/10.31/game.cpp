#include <bits/stdc++.h>

typedef long long LL;

const int N = 500 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
bool is[N], it[N];
struct Edge { int to, nxt; LL w; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v, LL w) { edge[ek] = (Edge){v, head[u], w}, head[u] = ek++; }

LL lows[N], lowt[N];

void predfs(int u, int fa) {
	lows[u] = lowt[u] = LLINF;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		predfs(v, u);
		lows[u] = std::min(lows[u], lows[v] + edge[i].w);
		lowt[u] = std::min(lowt[u], lowt[v] + edge[i].w);
	}
	if(is[u]) lows[u] = 0;
	if(it[u]) lowt[u] = 0;
}

LL dfs(int u, int fa) {
	if(is[u]) return /* printf("dfs %d (return %d)\n", u, 0),  */0;
	if(it[u]) return /* printf("dfs %d (return %lld)\n", u, std::min(lows[u] + 1, LLINF)),  */std::min(lows[u] + 1, LLINF);
	LL ret = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		ret += std::max(dfs(v, u) - edge[i].w, 0LL);
		ret = std::min(ret, LLINF);
	}
	if(u != 1) ret = std::min(ret, lows[u] + 1);
	// printf("dfs %d (return %lld)\n", u, ret);
	return ret;
}

int main() {
#ifndef DEBUG
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		ek = 2;
		int cs, ct;
		scanf("%d%d%d", &n, &cs, &ct);
		for(int i = 1; i <= n; i++) head[i] = 0, is[i] = it[i] = false;
		for(int i = 1; i < n; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); add_edge(u, v, w + 1), add_edge(v, u, w + 1); }
		for(int i = 1; i <= cs; i++) { int x; scanf("%d", &x); is[x] = true; }
		for(int i = 1; i <= ct; i++) { int x; scanf("%d", &x); it[x] = true; }
		if(it[1]) { puts("Impossible"); continue; }
		predfs(1, 0);
		// for(int i = 1; i <= n; i++) printf("%d: lows = %lld, lowt = %lld\n", i, lows[i], lowt[i]);
		LL ret = dfs(1, 0);
		if(ret >= LLINF / 2) puts("Impossible");
		else printf("%lld\n", ret);
	}
	return 0;
}