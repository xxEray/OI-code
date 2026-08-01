#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 5e4 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

struct Edge { int to, nxt; LL w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, LL w) {
	static int k = 1;
	edge[k] = (Edge){v, head[u], w};
	head[u] = k++;
}

LL a[N];
int n, m;

LL f[N][2];
int last1[N], last0[N][2];

int out[N], top = 0;
int cnt = 0;
void getroadl(int u) {
	while(last1[u]) cnt++, out[top++] = u, u = last1[u];
	cnt++, out[top++] = u;
	std::reverse(out, out + top);
}
void getroadr(int u) {
	while(last1[u]) cnt++, out[top++] = u, u = last1[u];
	cnt++, out[top++] = u;
}
void getroad(int u, int id) {
	if(id == 0) {
		while(last0[u][0] == 0) u = last0[u][1];
		cnt++;
		getroadl(last0[u][0]);
		out[top++] = u;
		getroadr(last0[u][1]);
	} else {
		cnt++, out[top++] = u;
		if(last1[u]) getroadr(last1[u]);
	}
}

bool vis[N];

void dfs(int u, int fa) {
	vis[u] = true;
	LL mx1 = -LLINF, mx2 = -LLINF;
	int mx1id = 0, mx2id = 0;
	f[u][0] = -LLINF;
	f[u][1] = a[u];
	last1[u] = 0;
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa) {
			int v = edge[i].to;
			dfs(v, u);
			if(f[v][0] > f[u][0]) f[u][0] = f[v][0], last0[u][0] = 0, last0[u][1] = v;
			if(f[v][1] + edge[i].w + a[u] > f[u][1]) f[u][1] = f[v][1] + edge[i].w + a[u], last1[u] = v;
			if(f[v][1] + edge[i].w > mx1) mx2 = mx1, mx2id = mx1id, mx1 = f[v][1] + edge[i].w, mx1id = v;
			else if(f[v][1] + edge[i].w > mx2) mx2 = f[v][1] + edge[i].w, mx2id = v;
		}
	if(mx1 > -LLINF && mx2 > -LLINF && a[u] + mx1 + mx2 > f[u][0])
		f[u][0] = a[u] + mx1 + mx2, last0[u][0] = mx1id, last0[u][1] = mx2id;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= m; i++) {
		int u, v;
		LL w;
		scanf("%d%d%lld", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	if(m == 0) {
		LL mx = -LLINF;
		int mxid;
		for(int i = 1; i <= n; i++) if(a[i] > mx) mx = a[i], mxid = i;
		printf("%lld\n1\n%d ", mx, mxid);
		return 0;
	}
	LL ansv = -LLINF;
	int ansi = 1, ansj = 0;
	for(int i = 1; i <= n; i++)
		if(!vis[i]) {
			dfs(i, 0);
			if(f[i][0] > ansv) ansv = f[i][0], ansi = i, ansj = 0;
			if(f[i][1] > ansv) ansv = f[i][1], ansi = i, ansj = 1;
		}
	// printf("ans = f[%d][%d]\n", ansi, ansj);
	// for(int i = 1; i <= n; i++)
	// 	printf("last[%d] = %d %d, %d\n", i, last0[i][0], last0[i][1], last1[i]);
	printf("%lld\n", ansv);
	getroad(ansi, ansj);
	printf("%d\n", cnt);
	for(int i = 0; i < top; i++) printf("%d ", out[i]);
	return 0;
} /*
4 0
0 0 0 0
*/