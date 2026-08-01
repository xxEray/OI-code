#include <bits/stdc++.h>

const int N = 2e4 * 10 * 2 + 5;

int n, m, K;
struct Edge { int to, nxt; } edge[N * 10];
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

int hash(int x, int y) { assert(1 <= x && x <= n && 1 <= y && y <= K); return (x - 1) * K + y; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1, top = cc = time_stamp = 0;
		scanf("%d%d%d", &n, &m, &K);
		for(int i = 1; i <= n * K * 2; i++) head[i] = 0, vis[i] = 0, to[i].clear();
		for(int i = 1; i <= n; i++) add_edge(hash(i, 1) + n * K, hash(i, 1));
		for(int i = 1; i < n; i++) for(int j = 1; j <= K; j++) add_edge(hash(i, j), hash(i + 1, j)), add_edge(hash(i + 1, j) + n * K, hash(i, j) + n * K);
		for(int i = 1; i <= n; i++) for(int j = 2; j <= K; j++) add_edge(hash(i, j), hash(i, j - 1)), add_edge(hash(i, j - 1) + n * K, hash(i, j) + n * K);
		while(m--) {
			int t, i, j, x;
			scanf("%d", &t);
			if(t == 1) {
				scanf("%d%d", &i, &x);
				if(x == K) add_edge(hash(i, x), hash(i, x) + n * K), add_edge(hash(i, x) + n * K, hash(i, x));
				else add_edge(hash(i, x), hash(i, x + 1)), add_edge(hash(i, x + 1) + n * K, hash(i, x) + n * K);
			} else if(t == 2) {
				scanf("%d%d%d", &i, &j, &x);
				for(int ki = 1; ki <= K; ki++) for(int kj = 1; kj <= K; kj++) if(ki + kj > x)
					add_edge(hash(i, ki), hash(j, kj) + n * K), add_edge(hash(j, kj), hash(i, ki) + n * K);
			} else if(t == 3) {
				scanf("%d%d%d", &i, &j, &x);
				for(int ki = 1; ki <= K; ki++) for(int kj = 1; kj <= K; kj++) if(ki - 1 + kj - 1 < x)
					add_edge(hash(i, ki) + n * K, hash(j, kj)), add_edge(hash(j, kj) + n * K, hash(i, ki));
			}
		}
		for(int i = 1; i <= 2 * n * K; i++) if(!vis[i]) tarjan(i);
		bool flag = true;
		for(int i = 1; i <= n * K; i++) if(bl[i] == bl[i + n * K]) flag = false;
		if(!flag) { puts("-1"); continue; }
		// printf("bl: "); for(int i = 1; i <= 2 * n * K; i++) printf("%d ", bl[i]); puts("");
		for(int u = 1; u <= 2 * n * K; u++)
			for(int i = head[u]; i; i = edge[i].nxt) {
				int v = edge[i].to;
				// printf("%d %d\n", u, v);
				if(bl[u] != bl[v]) to[bl[u]].push_back(bl[v]);
			}
		toposort();
		// for(int i = 1; i <= cc; i++) for(int j : to[i]) printf("%d -> %d\n", i, j), assert(ord[i] < ord[j]);
		// printf("ord: "); for(int i = 1; i <= 2 * n * K; i++) printf("%d ", ord[bl[i]]); puts("");
		// for(int i = 1; i <= n; i++) for(int j = 1; j <= K; j++) printf("(%d, %d) = %d\n", i, j, ord[bl[hash(i, j) + n * K]] > ord[bl[hash(i, j)]] ? 0 : 1);
		for(int i = 1; i <= n; i++) {
			int val = K;
			for(int j = 1; j <= K; j++) if(ord[bl[hash(i, j) + n * K]] > ord[bl[hash(i, j)]]) { val = j - 1; break; }
			printf("%d ", val);
		}
		puts("");
	}
	return 0;
} /*
1
5 5 5
3 2 5 7
2 4 5 10
3 4 5 6
3 3 4 7
2 1 5 7
*/