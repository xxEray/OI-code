#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) {
	static int k = 1;
	edge[k] = (Edge){v, head[u], w};
	head[u] = k++;
}

int n;

int f[N][2], last[N], tag[N];

void dfs(int u, int fa) {
	int mx = 0;
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa) {
			int v = edge[i].to;
			dfs(v, u);
			f[u][1] += f[v][0];
			f[u][0] += f[v][0];
			if(mx < f[v][1] + 1 - f[v][0])
				mx = f[v][1] + 1 - f[v][0], last[u] = v, tag[u] = edge[i].w;
		}
	f[u][0] += mx;
}

void print(int u, int fa, int t) {
	if(t == 0 && last[u]) {
		if(tag[u]) printf("%d %d\n", last[u], u);
		else printf("%d %d\n", u, last[u]);
		print(last[u], u, 1);
		for(int i = head[u]; i; i = edge[i].nxt)
			if(edge[i].to != fa && edge[i].to != last[u])
				print(edge[i].to, u, 0);
	} else {
		for(int i = head[u]; i; i = edge[i].nxt)
			if(edge[i].to != fa)
				print(edge[i].to, u, 0);
	}
}

int main() {
	scanf("%d%*d", &n);
	for(int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v, 0);
		add_edge(v, u, 1);
	}
	dfs(1, 0);
	printf("%d\n", f[1][0]);
	print(1, 0, 0);
	return 0;
}