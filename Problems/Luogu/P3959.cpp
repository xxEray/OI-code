#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long LL;

const int N = 12 + 5;
const int M = 1e3 + 5;
const int MAXS = (1 << 12) + 5;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
struct Edge { int to, nxt; LL w; } edge[M << 1];
int head[N], ek = 1;
void add_edge(int u, int v, LL w) { edge[ek] = (Edge){v, head[u], w}, head[u] = ek++; }

LL f[MAXS];

int dis[N];
bool vis[N];
void bfs(int st, int s) {
	std::queue<int> q;
	for(int i = 1; i <= n; i++) dis[i] = INF, vis[i] = false;
	dis[st] = 1, q.push(st), vis[st] = true;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(!(s >> (v - 1) & 1) || vis[v]) continue;
			dis[v] = dis[u] + 1, vis[v] = true, q.push(v);
		}
	}
}

void chkmin(LL &x, LL y) { if(x > y) x = y; }

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); if(u != v) add_edge(u, v, w), add_edge(v, u, w); }
	LL ans = LLINF;
	int U = (1 << n) - 1;
	for(int st = 2; st <= 2; st++) {
		for(int s = 0; s <= U; s++) f[s] = LLINF;
		f[1 << (st - 1)] = 0;
		for(int s = 0; s <= U; s++) if(s >> (st - 1) & 1) {
			bfs(st, s);
			for(int u = 1; u <= n; u++) if((s >> (u - 1) & 1))
				for(int i = head[u]; i; i = edge[i].nxt) {
					int v = edge[i].to;
					if(s >> (v - 1) & 1) continue;
					chkmin(f[s | (1 << (v - 1))], f[s] + dis[u] * edge[i].w);
				}
		}
		for(int s = 0; s <= U; s++) printf("f[%d] = %lld\n", s, f[s]);
		chkmin(ans, f[U]);
	}
	printf("%lld\n", ans);
	return 0;
} /*
5 6
1 2 7
1 3 3
2 4 3
2 5 3
4 5 9
4 1 1
*/