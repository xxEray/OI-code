#include <bits/stdc++.h>

const int N = 14 + 3;
const int MAXS = (1 << 14) + 5;
const int MAXV = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
struct Point { int x, y; } a[N * N + N];

int U;

std::vector<int> b[MAXS];
std::set<std::pair<int, int>> exist;
int f[N * N + N][MAXS], g[N + N * N][MAXS];
bool cr[MAXV], cc[MAXV];

void preprocess() {
	std::vector<int> r, c;
	for(int i = 1; i <= n; i++) r.push_back(a[i].x), c.push_back(a[i].y), exist.insert({a[i].x, a[i].y});
	std::sort(r.begin(), r.end()), std::sort(c.begin(), c.end());
	r.erase(std::unique(r.begin(), r.end()), r.end()), c.erase(std::unique(c.begin(), c.end()), c.end());
	m = n;
	for(int x : r) for(int y : c) if(!exist.count({x, y})) a[++m] = {x, y};
	// for(int i = n + 1; i <= m; i++) printf("%d: (%d, %d)\n", i, a[i].x, a[i].y);
	for(int s = 0; s <= U; s++) {
		for(int i = 1; i <= n; i++) if(s >> (i - 1) & 1) b[s].push_back(i);
		for(int i = 1; i <= n; i++) if(s >> (i - 1) & 1) cr[a[i].x] = true, cc[a[i].y] = true;
		for(int i = n + 1; i <= m; i++) if(cr[a[i].x] && cc[a[i].y]) b[s].push_back(i);
		for(int i = 1; i <= n; i++) if(s >> (i - 1) & 1) cr[a[i].x] = false, cc[a[i].y] = false;
		// printf("b[%d]: ", s); for(int i : b[s]) printf("(%d, %d) ", a[i].x, a[i].y); puts("");
	}
}

int dist(int i, int j) { return std::abs(a[i].x - a[j].x) + std::abs(a[i].y - a[j].y); }

int main() {
#ifndef DEBUG
	freopen("connected.in", "r", stdin);
	freopen("connected.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	U = (1 << n) - 1;
	preprocess();
	for(int i = 1; i <= m; i++) for(int s = 0; s <= U; s++) f[i][s] = g[i][s] = INF;
	for(int i = 1; i <= m; i++) f[i][0] = 0;
	for(int i = 1; i <= n; i++) f[i][1 << (i - 1)] = 0;
	for(int s = 0; s <= U; s++) {
		for(int i : b[s]) {
			for(int t = s; (s ^ t) <= t; t = (t - 1) & s) g[i][s] = std::min(g[i][s], g[i][s ^ t] + g[i][t]);
			f[i][s] = std::min(f[i][s], g[i][s]);
		}
		for(int i = 1; i <= n; i++) if(s >> (i - 1) & 1) for(int j : b[s]) f[i][s] = std::min(f[i][s], f[j][s]);
		for(int i : b[s]) for(int j = 1; j <= m; j++) g[j][s] = std::min(g[j][s], f[i][s] + dist(i, j));
	}
	// printf("m = %d\n", m);
	int ans = INF;
	for(int i = 1; i <= m; i++) ans = std::min(ans, f[i][U]);
	printf("%d\n", ans + 1);
	// while(true) {
	// 	printf("< "), fflush(stdout);
	// 	int i, j;
	// 	scanf("%d%d", &i, &j);
	// 	printf("> %d\n", f[i][j]);
	// }
	return 0;
} /*
14
20751 28960
15592 71
66993 64958
72695 31085
65649 5280
10554 19993
9461 11444
52954 73130
4111 68883
55053 99130
78675 63118
33541 4998
39039 94770
6866 26883
*/