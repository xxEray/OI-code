#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e6 + 5;
const LL MOD = 998244353;

int n, m, K;
struct Edge { int to, nxt, id; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int id) { static int k = 2; edge[k] = (Edge){v, head[u], id}, head[u] = k++; }

bool vis[N], vise[N << 1];

int out[N];

std::vector<int> circle;
std::vector<std::pair<int, int>> stk;
int cntv, cnte, cntr;
void dfs(int u) {
	// printf("dfs %d: ", u); for(auto [v, e] : stk) printf("(%d, %d) ", v, edge[e].id); puts("");
	vis[u] = true;
	cntv++;
	if(u > n) cntr++;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vise[i ^ 1]) {
		int v = edge[i].to;
		vise[i ^ 1] = vise[i] = true;
		out[edge[i].id] = (u <= n);
		// printf("out[%d] = %d\n", edge[i].id, (u <= n));
		if(!vis[v]) {
			cnte++;
			stk.emplace_back(v, i);
			dfs(v);
			stk.pop_back();
		} else {
			circle.emplace_back(u);
			cnte++;
			out[edge[i].id] = 0; // , printf("force %d 0\n", edge[i].id);
			for(int j = (int)stk.size() - 1, t = 1; j >= 0 && stk[j].first != v; j--, t ^= 1) {
				out[edge[stk[j].second].id] = t; // , printf("force %d %d\n", edge[stk[j].second].id, t);
			}
		}
	}
}

int main() {
#ifndef DEBUG
	freopen("flow.in", "r", stdin);
	freopen("flow.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= K; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v + n, i), add_edge(v + n, u, i); }
	LL ans = 1;
	for(int i = n + m; i >= 1; i--) if(!vis[i]) {
		cntv = cnte = cntr = 0;
		dfs(i);
		// printf("cntv = %d, cnte = %d, cntr = %d\n", cntv, cnte, cntr);
		if(cnte > cntv) { puts("-1"); return 0; }
		else if(cnte == cntv) (ans *= 2) %= MOD;
		else (ans *= cntr) %= MOD;
	}
	stk.clear();
	for(int i = 1; i <= n + m; i++) vis[i] = false, out[i] = 0;
	for(int i = 1; i <= 2 * (n + m); i++) vise[i] = false;
	for(int u : circle) printf("u = %d\n", u);
	for(int u : circle) if(!vis[u]) dfs(u);
	// for(int i = n + m; i >= 1; i--) if(!vis[i]) dfs(i);
	printf("%lld\n", ans);
	for(int i = 1; i <= K; i++) printf("%d", out[i]);
	puts("");
	return 0;
} /*
10 5 15
5 1
3 1
5 2
2 4
10 3
3 5
6 3
10 4
6 4
6 2
4 3
8 4
1 5
7 2
9 5

2 2 4
1 1
1 2
2 1
2 2
*/