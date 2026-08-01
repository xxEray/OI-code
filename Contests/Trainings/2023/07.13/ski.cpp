#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e3 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
char a[N][N];

int hash(int x, int y) { return (x - 1) * m + y; }

std::vector<std::pair<int, int>> to[N * N];

LL dis[N * N];
bool vis[N * N];
void bfs(int st) {
	std::priority_queue<std::pair<LL, int>, std::vector<std::pair<LL, int>>, std::greater<std::pair<LL, int>>> q;
	for(int i = 1; i <= n * m; i++) dis[i] = LLINF;
	dis[st] = 0, q.push({0, st});
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(auto &p : to[u]) {
			int v = p.first, w = p.second;
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				q.push({dis[v], v});
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
	for(int i = 1; i <= n; i++) {
		int last = 1;
		for(int j = 1; j <= m; j++) {
			if(a[i][j] == '#') last = j;
			if(last < j) to[hash(i, j)].push_back({hash(i, last + 1), 1});
		}
		last = m;
		for(int j = m; j >= 1; j--) {
			if(a[i][j] == '#') last = j;
			if(last > j) to[hash(i, j)].push_back({hash(i, last - 1), 1});
		}
	}
	for(int j = 1; j <= m; j++) {
		int last = 1;
		for(int i = 1; i <= n; i++) {
			if(a[i][j] == '#') last = i;
			if(last < i) to[hash(i, j)].push_back({hash(last + 1, j), 1});
		}
		last = n;
		for(int i = n; i >= 1; i--) {
			if(a[i][j] == '#') last = i;
			if(last > i) to[hash(i, j)].push_back({hash(last - 1, j), 1});
		}
	}
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
		if(i < n && a[i][j] == '.' && a[i + 1][j] == '.') to[hash(i, j)].push_back({hash(i + 1, j), 2}), to[hash(i + 1, j)].push_back({hash(i, j), 2});
		if(j < m && a[i][j] == '.' && a[i][j + 1] == '.') to[hash(i, j)].push_back({hash(i, j + 1), 2}), to[hash(i, j + 1)].push_back({hash(i, j), 2});
	}
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
	// 	printf("(%d, %d): ", i, j);
	// 	for(auto &p : to[hash(i, j)]) {
	// 		int u = p.first, w = p.second;
	// 		int ui = (u - 1) / m + 1, uj = (u - 1) % m + 1;
	// 		printf("%d(%d, %d) ", w, ui, uj);
	// 	}
	// 	puts("");
	// }
	int stx, sty, edx, edy;
	scanf("%d%d%d%d", &stx, &sty, &edx, &edy);
	bfs(hash(stx, sty));
	printf("%lld\n", dis[hash(edx, edy)] >= LLINF ? -1LL : dis[hash(edx, edy)]);
	return 0;
} /*
10 10
##########
#..#.....#
#....#.#.#
##..#.##.#
##......##
##.#...#.#
#..#.##..#
#..###...#
##...#..##
##########
4 9
5 6
*/