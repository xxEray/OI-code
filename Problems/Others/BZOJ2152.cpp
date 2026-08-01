#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e4 + 5;
const int INF = 0x3f3f3f3f;

struct Edge { int to, nxt; LL w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++;}
int n;

bool vis[N];
int size[N];
int root, rootwt, allsize;

void getroot(int u, int fa) {
	int mx = 0;
	size[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to] && edge[i].to != fa) {
		int v = edge[i].to;
		getroot(v, u);
		size[u] += size[v];
		mx = std::max(mx, size[v]);
	}
	mx = std::max(mx, allsize - size[u]);
	if(mx < rootwt) root = u, rootwt = mx;
}
LL g[N][3], ret[3];
int cnt;
void dfs(int u, int fa, LL dis) {
	g[cnt][dis % 3]++;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to] && edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u, dis + edge[i].w);
	}
}
void calc(int u) {
	// printf("calc %d, total = %lld\n", u, ret[0] + ret[1] + ret[2]);
	cnt = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) cnt++, g[cnt][0] = g[cnt][1] = g[cnt][2] = 0, dfs(edge[i].to, 0, edge[i].w);
	LL total[3] = {0, 0, 0};
	ret[0]++; // (u, u)
	for(int i = 1; i <= cnt; i++) for(int j = 0; j < 3; j++) ret[j] += g[i][j] * 2, total[j] += g[i][j];
	for(int i = 1; i <= cnt; i++) {
		for(int j = 0; j < 3; j++) total[j] -= g[i][j];
		for(int j = 0; j < 3; j++) for(int k = 0; k < 3; k++) ret[(j + k) % 3] += g[i][j] * total[k];
		for(int j = 0; j < 3; j++) total[j] += g[i][j];
	}
}
void solve(int u) {
	vis[u] = true, calc(u);
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		rootwt = INF, allsize = size[v], getroot(v, 0), solve(root);
	}
}

inline LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	rootwt = INF, allsize = n, getroot(1, 0), solve(root);
	int x = ret[0], y = ret[0] + ret[1] + ret[2];
	LL g = gcd(x, y);
	x /= g, y /= g;
	printf("%d/%d\n", x, y);
	return 0;
} /*
5
1 2 1
1 3 2
1 4 1
2 5 3
*/