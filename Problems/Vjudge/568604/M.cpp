#include <bits/stdc++.h>

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int n, K;
struct Graph {
	struct Edge { int to, nxt; } edge[N];
	int head[N], ek;
	Graph() : ek(1) {}
	void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }
} G, R;

std::vector<int> circle[N];
int cc;

int vis[N];
std::vector<int> stk;
void get_circle(int u) {
	if(vis[u] == 2) return;
	if(vis[u] == 1) {
		cc++;
		int i = 0;
		while(stk[i] != u) i++;
		for(; i < (int)stk.size(); i++) circle[cc].push_back(stk[i]);
		return;
	}
	vis[u] = 1;
	stk.push_back(u);
	for(int i = G.head[u]; i; i = G.edge[i].nxt) get_circle(G.edge[i].to);
	stk.pop_back();
	vis[u] = 2;
}

int ans;
int f[N];
void dfs(int u, bool flag) {
	vis[u] = 1;
	for(int i = R.head[u]; i; i = R.edge[i].nxt) {
		int v = R.edge[i].to;
		if(vis[v]) continue;
		dfs(v, true);
		f[u] = std::max(f[u], f[v] - 1);
	}
	if(u == 1) f[u] = K + 1;
	if(f[u] == 0 && flag) ans++, f[u] = K;
}

bool legal[N];
int nxt[N];

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) { int u, v; scanf("%d%d", &u, &v); G.add_edge(u, v), R.add_edge(v, u); }
	// if(n == 499989) return 0;
	for(int i = 1; i <= n; i++) get_circle(i);
	// printf("cc = %d\n", cc);
	// for(int i = 1; i <= cc; i++, puts("")) for(int u : circle[i]) printf("%d ", u);
	for(int i = 1; i <= n; i++) vis[i] = 0;
	for(int i = 1; i <= cc; i++) for(int u : circle[i]) vis[u] = 1;
	for(int i = 1; i <= cc; i++) for(int u : circle[i]) dfs(u, false);
	// for(int i = 1; i <= n; i++) printf("f[%d] = %d\n", i, f[i]);
	for(int i = 1; i <= cc; i++) {
		int sz = circle[i].size();
		int ff = 0;
		for(int u : circle[i]) ff = std::max(std::max(ff - 1, f[u]), 0);
		// printf("ff = %d\n", ff);
		for(int u : circle[i]) {
			ff = std::max(std::max(ff - 1, f[u]), 0);
			if(ff == 0) legal[u] = false;
			else legal[u] = true;
		}
		// for(int u : circle[i]) printf("legal[%d] = %d\n", u, legal[u]);
		int last = 0;
		for(int j = 0; j < sz; j++) nxt[j] = 0;
		for(int j = sz - 1; j >= 0; j--) if(!legal[circle[i][j]]) last = j;
		for(int j = sz - 1; j >= 0; j--) {
			if(!legal[circle[i][j]]) last = j;
			nxt[j] = last;
		}
		int st = 0;
		while(st < sz && legal[circle[i][st]]) st++;
		if(st == sz) continue;
		if(sz <= K) { ans++; continue; }
		int ret = INF;
		for(int j = st, c = 0; c < K; c++, j = nxt[(j + 1) % sz]) {
			int cnt = 0, d = 0;
			for(int k = j; d < sz; ) {
				cnt++;
				#define trim(x) ((x) > sz ? (x) - sz : (x))
				d += trim(nxt[(k + K) % sz] - k + sz);
				k = nxt[(k + K) % sz];
			}
			ret = std::min(ret, cnt);
		}
		// printf("i = %d, ret = %d\n", i, ret);
		ans += ret;
	}
	printf("%d\n", ans);
	return 0;
} /*
14 4
1 2
2 3
3 4
4 5
7 5
5 6
6 3
8 10
10 9
9 8
14 13
13 12
12 11
11 14
*/