#include <bits/stdc++.h>

typedef long long LL;

const int N = 19 + 3;
const int MAXS = (1 << 19) + 5;
const LL MOD = 1e9 + 7;

int n, m, K;
int a[N][N];

int f[2][N][MAXS];

inline int lowbit(int x) { return x & -x; }

int main() {
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= m; i++) for(int j = 1; j <= n; j++) a[i][j] = -1;
	for(int i = 1; i <= K; i++) { int x, y, v; scanf("%d%d%d", &x, &y, &v); a[x][y] = !v; }
	int U = (1 << (n - 1)) - 1;
	f[1][1][0] = 1;
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) for(int s = 0; s <= U; s++) f[~i & 1][j][s] = 0;
		for(int j = 1; j < n; j++)
			for(int s = 0; s <= U; s++) {
				int v = (s >> (j - 1) & 1);
				if(a[i][j] != v) (f[i & 1][j + 1][s] += f[i & 1][j][s]) %= MOD;
				if(v == 0 && a[i][j] != 1) {
					int t = lowbit(s >> j) << j;
					(f[i & 1][j + 1][s ^ (1 << (j - 1)) ^ t] += f[i & 1][j][s]) %= MOD;
				}
			}
		for(int s = 0; s <= U; s++) (f[~i & 1][1][s] += f[i & 1][n][s]) %= MOD;
	}
	int ans = 0;
	for(int s = 0; s <= U; s++) (ans += f[m & 1][n][s]) %= MOD;
	printf("%d\n", ans);
	return 0;
}