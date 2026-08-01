#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e4 + 5;
const int M = 10 + 3;
const int MAXS = (1 << 10) + 5;
const int MOD = 998244353;

int n, m;

int a[N][M], b[N][M];
int size[MAXS];

LL f[2][MAXS];

int main() {
#ifndef DEBUG
	freopen("sabotage.in", "r", stdin);
	freopen("sabotage.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int x; scanf("%d", &x);
		if(x) a[2][i] |= 1;
	}
	for(int i = 3; i <= n - 1; i++)
		for(int j = 1; j <= m; j++) for(int k = 1; k <= m; k++) {
			int x; scanf("%d", &x);
			if(x) a[i][k] |= 1 << (j - 1), b[i][j] |= 1 << (k - 1);
		}
	for(int i = 1; i <= m; i++) {
		int x; scanf("%d", &x);
		if(x) a[n][1] |= 1 << (i - 1);
	}
	int U = (1 << m) - 1;
	for(int s = 0; s <= U; s++) for(int j = 0; j < m; j++) size[s] ^= (s >> j & 1);
	// i = 1
	f[1][1] = 1;
	// i = 2
	{
		int t = 0;
		for(int j = 1; j <= m; j++) t |= a[2][j] << (j - 1);
		f[0][t] = 1;
	}
	// i = 3 .. n - 1
	for(int i = 3; i <= n - 1; i++) {
		int bit = i & 1;
		for(int s = 0; s <= U; s++) f[bit][s] = 0;
		for(int s = 0; s <= U; s++) {
			int t1 = 0, t2 = 0;
			for(int j = 1; j <= m; j++) {
				t1 |= (size[s & a[i][j]]) << (j - 1);
				t2 |= (size[s & b[i][j]]) << (j - 1);
			}
			f[bit][t1] += f[bit ^ 1][s];
			f[bit][t2] += f[bit ^ 1][s];
		}
		for(int s = 0; s <= U; s++) f[bit][s] %= MOD;
	}
	// i = n
	f[n & 1][0] = 0;
	for(int s = 0; s <= U; s++) f[n & 1][size[s & a[n][1]]] += f[(n & 1) ^ 1][s];
	printf("%lld\n", f[n & 1][0] % MOD);
	return 0;
}
