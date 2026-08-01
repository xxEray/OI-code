#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int n, Q;
int a[N];

struct BIT {
	int t[N];
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	void add(int l, int r, int v) { add(l, v); add(r + 1, -v); }
} bit;

struct Edge { int to, nxt; } edge[N << 1];
int head[N], ek = 1;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }

int t[N], out[N], dep[N];
int time_stamp;
void dfs(int u, int fa) {
	t[u] = ++time_stamp;
	dep[u] = dep[fa] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
	}
	out[u] = time_stamp;
}

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0);
	for(int i = 1; i <= n; i++) bit.add(t[i], t[i], dep[i] & 1 ? a[i] : -a[i]);
	while(Q--) {
		int type, x, y;
		scanf("%d", &type);
		if(type == 1) {
			scanf("%d%d", &x, &y);
			bit.add(t[x], out[x], dep[x] & 1 ? y : -y);
		} else {
			scanf("%d", &x);
			printf("%d\n", (dep[x] & 1 ? 1 : -1) * bit.query(t[x]));
		}
	}
	return 0;
}