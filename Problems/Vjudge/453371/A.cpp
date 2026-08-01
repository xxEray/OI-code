#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 3000 + 5;
const int MOD = 1e9 + 7;
const int inv2 = (MOD + 1) / 2;

int a[N];
int n, m;

int f[N][N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) f[i][j] = (a[i] < a[j]);
	int power = 1;
	for(int i = 1; i <= m; i++) {
		(power <<= 1) %= MOD;
		int x, y;
		scanf("%d%d", &x, &y);
		f[x][y] = f[y][x] = (f[x][y] + f[y][x]) % MOD * (LL)inv2 % MOD;
		for(int j = 1; j <= n; j++)
			if(j != x && j != y) {
				f[x][j] = f[y][j] = (f[x][j] + f[y][j]) % MOD * (LL)inv2 % MOD;
				f[j][x] = f[j][y] = (f[j][x] + f[j][y]) % MOD * (LL)inv2 % MOD;
			}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= i - 1; j++) (ans += f[i][j]) %= MOD;
	printf("%lld\n", (LL)ans * power % MOD);
	return 0;
}