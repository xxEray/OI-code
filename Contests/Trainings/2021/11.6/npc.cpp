#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 20 + 5;
const int S = (1 << 20) + 1;

bool e[N][N];
int n, m;

bool check(int st) {
	for(int i = 1; i <= n; i++)
		if(st >> (i - 1) & 1)
			for(int j = 1; j <= n; j++)
				if(st >> (j - 1) & 1)
					if(!e[i][j]) return false;
	return true;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) e[i][j] = (i == j);
		for(int i = 1; i <= m; i++) { int x, y; scanf("%d%d", &x, &y); e[x][y] = e[y][x] = true; }
		int ans = 0;
		for(int s = 0; s < (1 << n); s++) ans = (check(s) ? std::max(ans, __builtin_popcount(s)) : ans);
		printf("%d\n", ans);
	}
	return 0;
} /*
2
3 2
1 2
2 3
4 4
1 2
1 3
2 3
1 4
*/