#include <cstdio>
#include <algorithm>
#include <map>

const int N = 2e6 + 5;

int a[N];
int n;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

std::map<int, int> v2i;
int i2v[N];
int cn;
int id(int x) { return v2i.find(x) != v2i.end() ? v2i[x] : (cn++, v2i[x] = cn, i2v[cn] = x); }

int dep[N];
void dfs(int u, int fa) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		dep[u] = std::max(dep[u], dep[v] + 1);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
		while(a[i]) {
			int k = 1;
			while(k < a[i]) k <<= 1;
			printf("%d(%d) <-> %d(%d)\n", a[i], id(a[i]), k - a[i], id(k - a[i]));
			add_edge(id(k - a[i]), id(a[i])), add_edge(id(a[i]), id(k - a[i]));
			a[i] = k - a[i];
		}
	int st = 1, ed = 1;
	for(int i = 1; i <= cn; i++) dep[i] = 0;
	dfs(1, 0);
	for(int i = 1; i <= cn; i++) if(dep[st] < dep[i]) st = i;
	for(int i = 1; i <= cn; i++) dep[i] = 0;
	dfs(st, 0);
	for(int i = 1; i <= cn; i++) if(dep[ed] < dep[i]) ed = i;
	printf("%d %d %d\n", i2v[st], i2v[ed], dep[ed]);
	return 0;
}