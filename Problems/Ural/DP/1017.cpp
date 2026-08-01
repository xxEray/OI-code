#include <cstdio>

typedef long long LL;

const int N = 500 + 5;

int n;
LL f[N][N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) f[i][i] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= i; j++)
			for(int k = j + 1; k <= n - i; k++)
				f[i + k][k] += f[i][j];
	LL ans = 0;
	for(int i = 1; i <= n; i++) ans += f[n][i];
	printf("%lld\n", ans);
	return 0;
}