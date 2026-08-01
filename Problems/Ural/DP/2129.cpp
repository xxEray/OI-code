#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 200 + 5;
const int D = 200 + 5;
const LL MOD = 1e9 + 7;

LL value, m;
int n;
LL g[D];
int c;

LL f[D][N][N];

LL dfs(int i, int j, int k) {
	if(f[i][j][k] != -1) return f[i][j][k];
	if(i <= 0 || i > c || j < 0 || j > n || k < 0 || k > n) return 0;
	f[i][j][k] = 0;
	for(int t = k; t >= 0; t--)
		if(g[i - 1] + m * (k - t) <= j - t)
			(f[i][j][k] += dfs(i - 1, j - t, g[i - 1] + m * (k - t))) %= MOD;
		else break;
	return f[i][j][k];
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld%d", &value, &m, &n);
		memset(f, -1, sizeof(f));
		f[0][0][0] = 1;
		c = 0;
		while(value) g[++c] = value % m, value /= m;
		if(g[c] > n) puts("0");
		else printf("%lld\n", dfs(c, n, g[c]));
	}
	return 0;
} /*
3
12 3 4
7 2 5
7 2 2
*/