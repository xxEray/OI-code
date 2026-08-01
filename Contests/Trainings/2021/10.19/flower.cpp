#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e5 + 5;

int z1[N], z2[N];
int n;

struct Graph {
	struct Edge { int to, nxt; } edge[N << 1];
	int head[N], k;
	void add_edge(int u, int v) { edge[k] = (Edge){v, head[u]}, head[u] = k++; }
} G, DAG;

int low[N], dfn[N], vis[N];
int stk[N], top;
int bl[N], tot;
void tarjan(int u) {
	static int time = 0;
	dfn[u] = low[u] = ++time;
	stk[top++] = u;
	vis[u] = 1;
	for(int i = G.head[u]; i; i = G.edge[i].nxt) {
		int v = G.edge[i].to;
		if(vis[v] == 0) tarjan(v), low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
	}
	if(low[u] == dfn[u]) {
		tot++;
		do {
			top--;
			bl[stk[top]] = tot;
			vis[stk[top]] = 2;
		} while(stk[top] != u);
	}
}

bool uni;
int ind[N], cnt;
void toposort() {
	top = 0;
	for(int i = 1; i <= tot; i++) for(int j = DAG.head[i]; j; j = DAG.edge[j].nxt) ind[DAG.edge[j].to]++;
	for(int i = 1; i <= tot; i++) if(ind[i] == 0) stk[top++] = i;
	if(top > 1) { uni = false; return; }
	while(top) {
		int u = stk[--top];
		for(int i = DAG.head[u]; i; i = DAG.edge[i].nxt) {
			int v = DAG.edge[i].to;
			ind[v]--;
			if(ind[v] == 0) stk[top++] = v;
		}
		if(top > 1) { uni = false; return; }
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		memset(G.head, 0, sizeof(G.head));
		memset(DAG.head, 0, sizeof(DAG.head));
		memset(ind, 0, sizeof(ind));
		memset(vis, 0, sizeof(vis));
		G.k = DAG.k = 1;
		tot = cnt = top = 0, uni = true;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &z1[i]), z1[i]++;
		for(int i = 1; i <= n; i++) scanf("%d", &z2[i]), z2[i]++;
		for(int i = 1; i <= n; i++) {
			if(z1[i] != i) G.add_edge(i, z1[i]);
			if(z2[i] != i && z2[i] != z1[i]) G.add_edge(i, z2[i]);
		}
		tarjan(1);
		bool ok = true;
		for(int i = 1; i <= n; i++) if(vis[i] == 0) { ok = false; break; }
		if(!ok) { puts("No"); continue; }
//		for(int i = 1; i <= n; i++) printf("bl[%d] = %d\n", i, bl[i]);
		for(int i = 1; i <= n; i++) for(int j = G.head[i]; j; j = G.edge[j].nxt) if(bl[i] != bl[G.edge[j].to]) DAG.add_edge(bl[i], bl[G.edge[j].to]);
		toposort();
		puts(uni ? "Yes" : "No");
	}
	return 0;
} /*
2
2
0 1 
0 1
3
1 2 2
2 2 2
*/
