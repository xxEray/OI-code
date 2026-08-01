#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dis[N];
void bfs(int st) {
	std::queue<int> q;
	for(int i = 1; i <= n; i++) dis[i] = INF;
	q.push(st), dis[st] = 0;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(dis[v] != INF) continue;
			dis[v] = dis[u] + 1;
			q.push(v);
		}
	}
}

int sz[N], hson[N];
bool flag;
void dfs(int u, int fa) {
	int cnt = 0, cntl = 0;
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		sz[u] += sz[v];
		if(sz[v] == 1) cntl++;
		else hson[u] = v;
		cnt++;
	}
	if(cntl < cnt - 1) flag = false;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	bfs(1);
	int du = std::max_element(dis + 1, dis + n + 1) - dis;
	flag = true;
	dfs(du, 0);
	if(!flag) { puts("No"); return 0; }
	puts("Yes");
	std::vector<int> dia;
	while(du) dia.push_back(du), du = hson[du];
	int siz = dia.size();
	for(int i = 0; i < siz; i++) {
		int u = dia[i];
		if(i & 1) printf("%d ", u);
		else for(int j = head[u]; j; j = edge[j].nxt) if(sz[edge[j].to] == 1) printf("%d ", edge[j].to);
	}
	for(int i = siz - 1; i >= 0; i--) {
		int u = dia[i];
		if(~i & 1) printf("%d ", u);
		else for(int j = head[u]; j; j = edge[j].nxt) if(sz[edge[j].to] == 1) printf("%d ", edge[j].to);
	}
	puts("");
	return 0;
} /*
8
1 2
2 3
2 4
3 5
3 6
4 7
4 8
*/