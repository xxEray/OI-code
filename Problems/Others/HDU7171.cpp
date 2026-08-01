#include <cstdio>
#include <algorithm>
#include <vector>
#include <bitset>
#include <cassert>

const int N = 5e4 + 5;
const int M = 1e5 + 5;
const int D = 16;

int n, m, Q;

struct Edge { int to, nxt, id; } edge[M];
int head[N], ek;
void add_edge(int u, int v, int id) { edge[ek] = (Edge){v, head[u], id}, head[u] = ek++; }

std::bitset<N> f[N];
std::bitset<N> s[M / D + 5];

int q[N][2];
std::vector<int> d[M];
void preprocess() {
	std::bitset<N> now;
	now.reset();
	for(int i = 1; i <= m + 1; i++) {
		for(int j : d[i]) now[j].flip();
		if(i % D == 0) s[i / D] = now;
	}
	assert(now.count() == 0);
}

std::bitset<N> get(int ind) {
	std::bitset<N> now = s[ind / D];
	for(int i = ind / D * D + 1; i <= ind; i++)
		for(int j : d[i]) now[j].flip();
	// printf("get(%d): ", ind);
	// for(int i = 1; i <= Q; i++) printf("%d", (int)now[i]);
	// puts("");
	return now;
}

int main() {
	// freopen("D:\\Useless\\Temp\\1010.in", "r", stdin);
	// freopen("D:\\Useless\\Temp\\1010.myout", "w", stdout);
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1;
		scanf("%d%d%d", &n, &m, &Q);
		for(int i = 1; i <= n; i++) head[i] = 0;
		for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v, i); };
		for(int i = 1; i <= m + 1; i++) d[i].clear(), d[i].shrink_to_fit();
		for(int i = 1; i <= Q; i++) {
			int l, r;
			scanf("%d%d%d%d", &q[i][0], &q[i][1], &l, &r);
			d[l].push_back(i), d[r + 1].push_back(i);
		}
		for(int i = 1; i <= n; i++) f[i].reset();
		// for(int i = 0; i <= (m + 1) / D; i++) s[i].reset();
		for(int i = 1; i <= Q; i++) f[q[i][1]][i] = 1;
		preprocess();
		for(int u = n; u >= 1; u--)
			for(int i = head[u]; i; i = edge[i].nxt) {
				int v = edge[i].to;
				f[u] |= f[v] & get(edge[i].id);
			}
		for(int i = 1; i <= Q; i++) puts(f[q[i][0]][i] ? "YES" : "NO");
	}
	return 0;
}