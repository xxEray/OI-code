#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 4e5 + 5;
const int INF = 0x3f3f3f3f;

struct Graph {
	struct Edge { int to, nxt; } edge[N << 1];
	int head[N], k;
	void init() { k = 1; }
	void add_edge(int u, int v) {
		edge[k] = (Edge){v, head[u]};
		head[u] = k++;
	}
} g, DAG;
int n, m;

int vis[N], dfn[N], low[N], stk[N], belong[N], size[N];
int top, time, tblock;
void tarjan(int u) {
	// printf("tarjan %d\n", u);
	dfn[u] = low[u] = ++time;
	stk[top++] = u;
	vis[u] = 1;
	for(int i = g.head[u]; i; i = g.edge[i].nxt) {
		int v = g.edge[i].to;
		// printf("tarjan %d->%d (i = %d)\n", u, v, i);
		if(vis[v] == 0) {
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
		} else if(vis[v] == 1) {
			low[u] = std::min(low[u], low[v]);
		}
	}
	if(low[u] == dfn[u]) {
		tblock++;
		do {
			top--;
			vis[stk[top]] = 2;
			belong[stk[top]] = tblock;
			size[tblock]++;
		} while(u != stk[top]);
	}
}

bool self[N];
int ind[N], f[N];
void toposort() {
	top = 0; // use stk[] again
	for(int i = 1; i <= tblock; i++) vis[i] = 0; // use vis[] again
	for(int i = 1; i <= tblock; i++) if(ind[i] == 0) stk[top++] = i, vis[i] = 1;
	for(int i = 1; i <= n; i++) if(self[i]) size[belong[i]] = 2;
	for(int i = 1; i <= tblock; i++) if(size[i] > 1) size[i] = 2;
	f[belong[1]] = (size[belong[1]] == 2 ? -1 : 1);
	while(top > 0) {
		int u = stk[--top];
		for(int i = DAG.head[u]; i; i = DAG.edge[i].nxt) {
			int v = DAG.edge[i].to;
			if(!vis[v]) {
				ind[v]--;
				if(f[u] == -1) f[v] = -1;
				else if(f[v] != -1) {
					f[v] += f[u];
					if(f[v] > 2) f[v] = 2;
				}
				if(f[v] && size[v] == 2) f[v] = -1;
				if(ind[v] == 0) {
					vis[v] = 1;
					stk[top++] = v;
				}
			}
		}
	}
}

int main() {
	// freopen("G.in", "r", stdin);
	// freopen("G.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while(T--) {
		g.init(), DAG.init();
		top = time = tblock = 0;
		if(scanf("%d%d", &n, &m) != 2) break;
		for(int i = 0; i <= std::max(n, m) + 1; i++)
			dfn[i] = low[i] = vis[i] = stk[i] = belong[i] = ind[i] = f[i] = size[i] = g.head[i] = DAG.head[i] = self[i] = 0;
		for(int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			if(u == v) self[u] = true;
			else g.add_edge(u, v);
		}
		for(int i = 1; i <= n; i++) if(vis[i] == 0) tarjan(i);
		for(int i = 1; i <= n; i++)
			for(int j = g.head[i]; j; j = g.edge[j].nxt)
				if(belong[i] != belong[g.edge[j].to])
					DAG.add_edge(belong[i], belong[g.edge[j].to]), ind[belong[g.edge[j].to]]++;
		// for(int i = 1; i <= n; i++) printf("belong[%d] = %d\n", i, belong[i]);
		toposort();
		// for(int i = 1; i <= tblock; i++) printf("f[%d] = %d\n", i, f[i]);
		for(int i = 1; i <= n; i++) {
			int ret = f[belong[i]];
			if(ret == 0) printf("0 ");
			else if(ret == 1) printf("1 ");
			else if(ret == -1) printf("-1 ");
			else printf("2 ");
		}
		puts("");
	}
	return 0;
} /*
*/