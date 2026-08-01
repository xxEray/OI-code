#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <functional>

const int N = 20 + 3;
const int STATE = N * N * N * N + 5;
const int INF = 0x3f3f3f3f;

char tmp[N];
int a[N][N], len[N];
int n, start_of_all;
int hash(int i, int j, int p, int q) { return (i - 1) * 8000 + (j - 1) * 400 + (p - 1) * 20 + q; }
struct Edge { int to, nxt, w; } edge[STATE << 2];
int head[STATE], ek;
void add_edge(int u, int v, int w) { edge[ek] = (Edge){v, head[u], w}, head[u] = ek++; }

struct DP { int len; std::string str; };
bool operator<(DP x, DP y) { return x.len == y.len ? x.str < y.str : x.len < y.len; }
DP operator+(DP dp, int bit) { return (DP){dp.len + 1, dp.str + (char)(bit + '0')}; }
DP dis[STATE];
int vis[STATE];
void dijkstra(int st) {
	#define PQT std::pair<DP, int>
	std::priority_queue<PQT, std::vector<PQT>, std::greater<PQT>> q;
	for(int i = 0; i <= hash(n, n, 20, 20); i++) dis[i] = (DP){INF, ""}, vis[i] = 0;
	dis[st] = DP(), vis[st] = 0, q.push({dis[st], st});
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to] && dis[u] + edge[i].w < dis[edge[i].to]) {
			int v = edge[i].to;
			// printf("%d: (%d, %s) -> %d: (%d, %s)\n", u, dis[u].len, dis[u].str.c_str(), v, dis[v].len, dis[v].str.c_str());
			dis[v] = dis[u] + edge[i].w;
			q.push({dis[v], v});
		}
	}
}

int main() {
	// freopen("out.txt", "w", stdout);
	start_of_all = hash(20, 20, 20, 20) + 1;
	int Case = 0;
	while(scanf("%d", &n) == 1 && n) {
		for(int i = 1; i <= hash(n, n, 20, 20); i++) head[i] = 0;
		head[start_of_all] = 0;
		ek = 1;
		for(int i = 1; i <= n; i++) {
			scanf("%s", tmp + 1);
			len[i] = strlen(tmp + 1);
			for(int j = 1; j <= len[i]; j++) a[i][j] = tmp[j] - '0';
		}
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++) {
				for(int p = 1; p < len[i]; p++)
					for(int q = 1; q < len[j]; q++)
						if(a[i][p + 1] == a[j][q + 1])
							add_edge(hash(i, j, p, q), hash(i, j, p + 1, q + 1), a[i][p + 1]);
				for(int i_ = 1; i_ <= n; i_++)
					for(int q = 1; q <= len[j]; q++)
						if(a[i_][1] == a[j][q + 1])
							add_edge(hash(i, j, len[i], q), hash(i_, j, 1, q + 1), a[i_][1]);
				for(int p = 1; p <= len[i]; p++)
					for(int j_ = 1; j_ <= n; j_++)
						if(a[i][p + 1] == a[j_][1])
							add_edge(hash(i, j, p, len[j]), hash(i, j_, p + 1, 1), a[j_][1]);
			}
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				if(i != j && a[i][1] == a[j][1]) add_edge(start_of_all, hash(i, j, 1, 1), a[i][1]);
		dijkstra(start_of_all);
		DP ans = {INF, ""};
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++) {
				DP ret = dis[hash(i, j, len[i], len[j])];
				// if(ret.len < INF) printf("update with (%d, \"%s\") [ans=%d, ansstr=\"%s\"]\n", ret.len, ret.str.c_str(), ans.len, ans.str.c_str());
				ans = std::min(ans, dis[hash(i, j, len[i], len[j])]);
			}
		if(ans.len == INF) { printf("Code %d: \n", ++Case); continue; } // impossible
		printf("Code %d: %d bits\n", ++Case, ans.len);
		for(int i = 0; i < (int)ans.str.size(); i += 20) std::printf("%s\n", ans.str.substr(i, 20).c_str());
		puts("");
	}
	return 0;
} /*
13
010001
10011111001011100110
1100011111
1101000111111011010
001000111110
0011100
01011
00101110100
00110101001
001
011010
0
1101111011011000000
*/