#include <bits/stdc++.h>

const int N = 2e6 + 5;

int n, m;
struct Edge { int to, nxt; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }

int vis[N], dfn[N], low[N], bl[N];
int stk[N], top;
int cc, time_stamp;
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	stk[top++] = u;
	vis[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(vis[v] == 0) tarjan(v), low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
	}
	if(dfn[u] == low[u]) {
		cc++;
		do {
			top--;
			bl[stk[top]] = cc;
			vis[stk[top]] = 2;
		} while(stk[top] != u);
	}
}
std::vector<int> to[N];
int ord[N], d[N];
void toposort() {
	for(int i = 1; i <= cc; i++) d[i] = 0;
	for(int u = 1; u <= cc; u++) for(int v : to[u]) d[v]++;
	std::vector<int> vct;
	for(int i = 1; i <= cc; i++) if(!d[i]) vct.push_back(i);
	int c = 0;
	while(!vct.empty()) {
		int u = vct.back();
		vct.pop_back();
		ord[u] = ++c;
		for(int v : to[u]) {
			d[v]--;
			if(!d[v]) vct.push_back(v);
		}
	}
}

int main() {
	ek = 1, cc = time_stamp = 0;
	scanf("%d%d", &n, &m);
	while(m--) {
		int i, a, j, b;
		scanf("%d%d%d%d", &i, &a, &j, &b);
		add_edge(!a * n + i, b * n + j), add_edge(!b * n + j, a * n + i);
	}
	for(int i = 1; i <= 2 * n; i++) if(!vis[i]) tarjan(i);
	bool flag = true;
	for(int i = 1; i <= n; i++) if(bl[i] == bl[i + n]) flag = false;
	if(!flag) { puts("IMPOSSIBLE"); return 0; }
	puts("POSSIBLE");
	// printf("bl: "); for(int i = 1; i <= 2 * n; i++) printf("%d ", bl[i]); puts("");
	for(int u = 1; u <= 2 * n; u++)
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			// printf("%d -> %d\n", u, v);
			if(bl[u] != bl[v]) to[bl[u]].push_back(bl[v]);
		}
	toposort();
	for(int i = 1; i <= n; i++) printf("%d ", ord[bl[i + n]] > ord[bl[i]]);
	puts("");
	return 0;
} /*
3 1
1 1 3 0
*/