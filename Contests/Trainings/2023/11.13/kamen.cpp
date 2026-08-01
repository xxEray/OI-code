#include <bits/stdc++.h>

const int N = 3e4 + 5;
const int M = 30 + 5;

int n, m, Q;
char s[N][M];

std::set<int> st[N][M];
std::pair<int, int> target[M];

void godown(int origin, int i, int j) {
	st[i][j].insert(origin);
	if(i == n || s[i + 1][j] == 'X') target[origin] = {i, j};
	else if(s[i + 1][j] == '.') godown(origin, i + 1, j);
	else if(s[i][j - 1] == '.' && s[i + 1][j - 1] == '.') godown(origin, i + 1, j - 1);
	else if(s[i][j + 1] == '.' && s[i + 1][j + 1] == '.') godown(origin, i + 1, j + 1);
	else target[origin] = {i, j};
}

int main() {
#ifndef DEBUG
	freopen("kamen.in", "r", stdin);
	freopen("kamen.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	for(int j = 1; j <= m; j++) godown(j, 1, j);
	scanf("%d", &Q);
	while(Q--) {
		int ori;
		scanf("%d", &ori);
		auto [x, y] = target[ori];
//		assert(s[x][y] == '.' && s[x - 1][y] == '.');
//		printf("(%d, %d)\n", x, y);
		s[x][y] = 'O', st[x][y].clear();
		if(s[x][y - 1] == 'O' && (y - 2 == 0 || s[x][y - 2] != '.' || s[x - 1][y - 2] != '.')) for(int z : st[x - 1][y - 1]) target[z] = {x - 1, y - 1};
		if(s[x][y + 1] == 'O') for(int z : st[x - 1][y + 1]) godown(z, x - 1, y + 1);
		for(int z : st[x - 1][y]) godown(z, x - 1, y);
	}
	for(int i = 1; i <= n; i++) printf("%s\n", s[i] + 1);
	return 0;
} /*
5 5
.....
.....
....X
.....
X....
5
3
2
4
3
3
*/
