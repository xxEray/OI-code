#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n, m;
std::vector<int> to[N << 1];

int vis[N << 1], dfn[N << 1], low[N << 1], bl[N << 1], stk[N << 1];
int time_stamp, scc, top;
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	stk[top++] = u;
	vis[u] = 1;
	for(int v : to[u]) {
		if(vis[v] == 0) tarjan(v), low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
	}
	if(low[u] == dfn[u]) {
		scc++;
		do {
			top--;
			bl[stk[top]] = scc;
			vis[stk[top]] = 2;
		} while(stk[top] != u);
	}
}

std::vector<int> to2[N << 1];
int d[N << 1], order[N << 1];
int time_stamp2;
void topo() {
	for(int u = 1; u <= scc; u++) for(int v : to2[u]) d[v]++;
	std::vector<int> vct;
	for(int i = 1; i <= scc; i++) if(!d[i]) vct.emplace_back(i);
	while(!vct.empty()) {
		int u = vct.back();
		vct.pop_back();
		order[u] = ++time_stamp2;
		for(int v : to2[u]) if(d[v]) {
			d[v]--;
			if(!d[v]) vct.emplace_back(v);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int x, xv, y, yv;
		scanf("%d%d%d%d", &x, &xv, &y, &yv);
		to[x + !xv * n].emplace_back(y + yv * n);
		to[y + !yv * n].emplace_back(x + xv * n);
	}
	for(int i = 1; i <= 2 * n; i++) if(!vis[i]) tarjan(i);
	for(int i = 1; i <= n; i++) if(bl[i] == bl[i + n]) { puts("IMPOSSIBLE"); return 0; }
	for(int u = 1; u <= 2 * n; u++) for(int v : to[u]) if(bl[u] != bl[v]) to2[bl[u]].emplace_back(bl[v]);
	topo();
	// for(int i = 1; i <= 2 * n; i++) printf("%d ", order[i]);
	puts("POSSIBLE");
	for(int i = 1; i <= n; i++) printf("%d ", order[bl[i]] < order[bl[i + n]] ? 1 : 0);
	return 0;
}