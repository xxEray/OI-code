#include <cstdio>

const int N = 3000 + 5;
const int MOD = 998244353;

int a[N];
int n, m;

int f[N][N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	f[0][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= m; j++) {
			f[i][j] = f[i - 1][j] * 2 % MOD;
			if(j >= a[i]) f[i][j] = (f[i][j] + f[i - 1][j - a[i]]) % MOD;
		}
	printf("%d\n", f[n][m]);
	return 0;
}