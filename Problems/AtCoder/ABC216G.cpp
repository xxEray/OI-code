#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

struct Edge { int to, nxt, w; } edge[N * 3];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }
int n, m;

int dis[N];
bool inq[N];
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> q;
void spfa(int st) {
	for(int i = 0; i <= n; i++) dis[i] = INF;
	dis[st] = 0;
	q.push({dis[st], st}), inq[st] = true;
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		if(!inq[u]) continue;
		inq[u] = false;
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(dis[v] > dis[u] + edge[i].w) {
				dis[v] = dis[u] + edge[i].w;
				// printf("%d -> %d with w=%d, dis[%d] = %d\n", u, v, edge[i].w, v, dis[v]);
				q.push({dis[v], v}), inq[v] = true;
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int l, r, c;
		scanf("%d%d%d", &l, &r, &c);
		add_edge(l - 1, r, r - l + 1 - c);
	}
	for(int i = 1; i <= n; i++) add_edge(i, i - 1, 0), add_edge(i - 1, i, 1);
	spfa(0);
	// for(int i = 0; i <= n; i++) printf("dis[%d] = %d\n", i, dis[i]);
	for(int i = 1; i <= n; i++) printf("%d ", !(dis[i] - dis[i - 1]));
	return 0;
} /*
6 3
1 4 3
2 2 1
4 6 2
*/