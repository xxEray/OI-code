#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long LL;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;
const LL MOD = 998244353;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int n;

std::queue<int> q;
int dis[N], vis[N], last[N];
void bfs(int st) {
	for(int i = 1; i <= n; i++) dis[i] = INF, vis[i] = 0;
	dis[st] = 0, q.push(st), vis[st] = 1;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
			int v = edge[i].to;
			dis[v] = dis[u] + 1;
			last[v] = u;
			q.push(v), vis[v] = 1;
		}
	}
}

int dep[N], g[N];
void dfs1(int u, int fa) {
	g[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs1(v, u);
		if(dep[v] + 1 > dep[u]) dep[u] = dep[v] + 1, g[u] = g[v];
		else if(dep[v] + 1 == dep[u]) g[u] += g[v];
	}
}
int tag[N];
void dfs2(int u, int fa, int tagv) {
	tag[u] = tagv;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dep[v] = dep[u] + 1;
		dfs2(v, u, tagv);
	}
}

int main() {
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	bfs(1);
	int x = 1;
	for(int i = 1; i <= n; i++) if(dis[i] > dis[x]) x = i;
	bfs(x);
	int y = 1;
	for(int i = 1; i <= n; i++) if(dis[i] > dis[y]) y = i;
	if(dis[y] & 1) {
		int rt = y;
		for(int o = 1; o <= dis[y] / 2; o++) rt = last[rt];
		x = last[rt], y = rt;
		dfs2(x, y, 0), dfs2(y, x, 1);
		int mx[2] = {0, 0};
		LL ret[2] = {0, 0};
		for(int i = 1; i <= n; i++) mx[tag[i]] = std::max(mx[tag[i]], dep[i]);
		for(int i = 1; i <= n; i++) if(dep[i] == mx[tag[i]]) ret[tag[i]]++;
		printf("%lld\n", ret[0] * ret[1] % MOD);
	} else {
		int rt = y;
		for(int o = 1; o <= dis[y] / 2; o++) rt = last[rt];
		dfs1(rt, 0);
		LL ans = 1, ret = 1;
		// for(int i = 1; i <= n; i++) printf("g[%d] = %d\n", i, g[i]);
		for(int i = head[rt]; i; i = edge[i].nxt) if(dep[edge[i].to] + 1 == dep[rt]) (ans *= g[edge[i].to] + 1) %= MOD, ret += g[edge[i].to]; //, printf("%d ", g[edge[i].to]);
		// printf("ret: %lld\n", ret - 1);
		(ans += MOD - ret) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
} /*
895048717
*/