#include <cstdio>
#include <algorithm>
#include "biginteger"

typedef BigInteger bign;

const int N = 50 + 5;

int n, m;

int la, lb;
int a[N], b[N];
bign f[N][N * N], g[N][N * N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i += 2) a[i] = a[i + 1] = i;
	for(int i = 1; i <= n; i += 2) b[i] = b[i + 1] = i + 1;
	la = n, lb = n - 1;
	f[0][0] = g[0][0] = 1;
	for(int i = 1; i <= la; i++) for(int j = 0; j <= m; j++) f[i][j] = f[i - 1][j] + f[i - 1][j - 1] * std::max(a[i] - j + 1, 0);
	for(int i = 1; i <= lb; i++) for(int j = 0; j <= m; j++) g[i][j] = g[i - 1][j] + g[i - 1][j - 1] * std::max(b[i] - j + 1, 0);
	bign ans = 0;
	for(int i = 0; i <= m; i++) ans += f[la][i] * g[lb][m - i];
	ans.print('\n');
	return 0;
}