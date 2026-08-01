#include <cstdio>
#include <algorithm>
#include <deque>

const int N = 500 + 5;
const int M = N * N * 21;
const int INF = 0x3f3f3f3f;

char s[N][N];
int n, m;

inline int id(int x, int y) { return (x - 1) * m + y; }
const int d[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
inline bool check(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }

struct Edge { int to, nxt, w; } edge[M];
int head[N * N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

int dis[N * N];
std::deque<int> q;
void bfs(int st) {
	q.push_back(st);
	for(int i = 1; i <= n * m; i++) dis[i] = INF;
	dis[st] = 0;
	while(!q.empty()) {
		int u = q.front();
		q.pop_front();
		for(int i = head[u]; i; i = edge[i].nxt) if(dis[edge[i].to] == INF) {
			int v = edge[i].to;
			dis[v] = dis[u] + edge[i].w;
			// printf("(%d, %d) -> (%d, %d) [W=%d]\n", (u - 1) / m + 1, (u - 1) % m + 1, (v - 1) / m + 1, (v - 1) % m + 1, edge[i].w);
			if(edge[i].w == 0) q.push_front(v);
			else q.push_back(v);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	for(int x = 1; x <= n; x++)
		for(int y = 1; y <= m; y++) {
			for(int i = 0; i < 4; i++) {
				int dx = x + d[i][0], dy = y + d[i][1];
				if(check(dx, dy) && s[dx][dy] == '.') add_edge(id(x, y), id(dx, dy), 0);//, printf("(%d, %d) <- (%d, %d)\n", x, y, dx, dy);
			}
			for(int tx = -2; tx <= 2; tx++)
				for(int ty = -2; ty <= 2; ty++) {
					if((!tx && !ty) || (std::abs(tx) == 2 && std::abs(ty) == 2)) continue;
					int dx = x + tx, dy = y + ty;
					if(check(dx, dy) && s[dx][dy] == '#') add_edge(id(x, y), id(dx, dy), 1);//, printf("(%d, %d) <- (%d, %d)\n", x, y, dx, dy);
				}
		}
	bfs(id(n, m));
	printf("%d\n", dis[id(1, 1)]);
	return 0;
} /*
5 5
.####
#####
#####
#####
####.
*/