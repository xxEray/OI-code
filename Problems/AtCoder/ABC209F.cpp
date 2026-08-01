#include <cstdio>
#include <algorithm>

const int N = 4000 + 5;
const int MOD = 1e9 + 7;

int a[N];
int n;

int f[N][N];
int presum[N][N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	f[1][1] = 1;
	for(int i = 1; i <= n; i++) presum[1][i] = (presum[1][i - 1] + f[1][i]) % MOD;
	for(int i = 2; i <= n; i++) {
		for(int j = 1; j <= i; j++) {
			if(a[i] <= a[i - 1]) (f[i][j] += (presum[i - 1][j - 1] - presum[i - 1][0] + MOD) % MOD) %= MOD;
			if(a[i] >= a[i - 1]) (f[i][j] += (presum[i - 1][i - 1] - presum[i - 1][j - 1] + MOD) % MOD) %= MOD;
			presum[i][j] = (presum[i][j - 1] + f[i][j]) % MOD;
		}
		for(int j = i + 1; j <= n; j++) presum[i][j] = presum[i][j - 1];
	}
	// for(int i = 1; i <= n; i++)
	// 	for(int j = 1; j <= i; j++)
	// 		printf("f[%d][%d] = %d\n", i, j, f[i][j]);
	printf("%d\n", presum[n][n]);
	return 0;
}