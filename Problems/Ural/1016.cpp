#include <cstdio>
#include <algorithm>
#include <queue>
#include <assert.h>

const int N = 10 + 5;
const int GRAPH = 1e5 + 5;
const int INF = 0x3f3f3f3f;

struct Edge { int to, nxt, w; } edge[GRAPH];
int head[GRAPH];
void add_edge(int u,int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

char tmp[10];
int num[N];
int stx, sty, edx, edy;
char c1, c2;

int hash(int x, int y, int dn, int rt, int nr) { return (x - 1) * 1728 + (y - 1) * 216 + (dn - 1) * 36 + (rt - 1) * 6 + (nr - 1) + 1; }
bool isopp(int x, int y) { return x - y == 3 || y - x == 3; }
int opp(int x) { return x <= 3 ? x + 3 : x - 3; }
bool check(int x, int y, int z) { return !isopp(x, y) && !isopp(y, z) && !isopp(x, z) && x != y && y != z && x != z; }

int tot;

int dis[GRAPH], last[GRAPH];
bool vis[GRAPH];
#define pii std::pair<int, int>
std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
void dijkstra(int st) {
	for(int i = 0; i <= tot; i++) dis[i] = INF, vis[i] = false, last[i] = -1;
	dis[st] = 0;
	q.push({dis[st], st});
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = head[u]; i; i = edge[i].nxt) if(dis[edge[i].to] == INF) {
			int v = edge[i].to;
			dis[v] = dis[u] + edge[i].w;
			last[v] = u; //, printf("last[%d] = %d\n", v, u);
			q.push({dis[v], v});
		}
	}
}

void print(int hsh) {
	int x = (hsh - 1) / 1728 + 1, y = (hsh - 1) / 216 % 8 + 1;
	int dn = (hsh - 1) / 36 % 6 + 1, rt = (hsh - 1) / 6 % 6 + 1, nr = (hsh - 1) % 6 + 1;
	assert(x <= 8);
	if(x != stx || y != sty || dn != 1 || rt != 2 || nr != 3) print(last[hsh]);
	// for(int i = head[last[hsh]]; i; i = edge[i].nxt) if(edge[i].to == hsh) printf("(%d) ", edge[i].w);
	printf("%c%d ", x + 'a' - 1, y);
}

int main() {
	scanf("%c%d%*[ ]%c%d", &c1, &sty, &c2, &edy);
	stx = c1 - 'a' + 1, edx = c2 - 'a' + 1;
	scanf("%d%d%d%d%d%d", &num[3], &num[6], &num[4], &num[2], &num[1], &num[5]);
	for(int i = 1; i <= 8; i++)
		for(int j = 1; j <= 8; j++)
			for(int dn = 1; dn <= 6; dn++)
				for(int rt = 1; rt <= 6; rt++)
					for(int nr = 1; nr <= 6; nr++)
						if(check(dn, rt, nr)) {
							int now = hash(i, j, dn, rt, nr), lt = opp(rt), fr = opp(nr), up = opp(dn);
							if(i < 8) add_edge(now, hash(i + 1, j, rt, up, nr), num[rt]);
							if(i > 1) add_edge(now, hash(i - 1, j, lt, dn, nr), num[lt]);
							if(j < 8) add_edge(now, hash(i, j + 1, fr, rt, dn), num[fr]);
							if(j > 1) add_edge(now, hash(i, j - 1, nr, rt, up), num[nr]);
						}
	tot = hash(8, 8, 6, 6, 6);
	int ans = INF, ansid;
	dijkstra(hash(stx, sty, 1, 2, 3));
	for(int i = 1; i <= 6; i++)
		for(int j = 1; j <= 6; j++)
			for(int k = 1; k <= 6; k++)
				if(check(i, j, k) && ans > dis[hash(edx, edy, i, j, k)])
					ansid = hash(edx, edy, i, j, k), ans = dis[ansid];
	printf("%d ", ans + num[1]);
	print(ansid);
	// scanf("%*[ \n\r\t]");
	// assert(scanf("%[0-9a-z]", tmp) != 1);
	return 0;
} /*
e2 e3 0 8 1 2 1 1
*/