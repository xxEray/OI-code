#include <bits/stdc++.h>

const int N = 1000 + 5;

int n, m, R, C;
char s[N][N];
std::vector<std::pair<int, int>> vct;
char tmp[N];

int main() {
#ifndef DEBUG
	freopen("seal.in", "r", stdin);
	freopen("seal.out", "w", stdout);
#endif
	scanf("%d%d%d%d", &n, &m, &R, &C);
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	for(int i = 1; i <= R; i++) {
		scanf("%s", tmp + 1);
		for(int j = 1; j <= C; j++) if(tmp[j] == 'x') vct.emplace_back(i, j);
	}
	if(vct.empty()) {
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(s[i][j] == 'x') { puts("NIE"); return 0; }
		puts("TAK");
		return 0;
	}
	auto [fx, fy] = vct.front();
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(s[i][j] == 'x') {
		int sx = i - fx, sy = j - fy;
		for(auto [r, c] : vct) {
			// printf("i = %d, j = %d, sx = %d, sy = %d, r = %d, c = %d\n", i, j, sx, sy, r, c);
			if(sx + r < 1 || sx + r > n || sy + c < 1 || sy + c > m || s[sx + r][sy + c] == '.') { puts("NIE"); return 0; }
			s[sx + r][sy + c] = '.';
		}
	}
	puts("TAK");
	return 0;
}
