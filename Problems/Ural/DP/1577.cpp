#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 2000 + 5;
const LL MOD = 1e9 + 7;

char a[N], b[N];
int n, m;

LL f[N][N], cnt[N][N];

int main() {
	scanf("%s%s", a + 1, b + 1);
	n = strlen(a + 1), m = strlen(b + 1);
	for(int i = 1; i <= n; i++) f[i][0] = i, cnt[i][0] = 1;
	for(int i = 1; i <= m; i++) f[0][i] = i, cnt[0][i] = 1;
	f[0][0] = 0, cnt[0][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(a[i] == b[j]) {
				f[i][j] = f[i - 1][j - 1];
				cnt[i][j] = cnt[i - 1][j - 1];
			} else if(f[i][j - 1] == f[i - 1][j]) {
				f[i][j] = f[i][j - 1] + 1;
				cnt[i][j] = (cnt[i][j - 1] + cnt[i - 1][j]) % MOD;
			} else if(f[i][j - 1] < f[i - 1][j]) {
				f[i][j] = f[i][j - 1] + 1;
				cnt[i][j] = cnt[i][j - 1];
			} else if(f[i - 1][j] < f[i][j - 1]) {
				f[i][j] = f[i - 1][j] + 1;
				cnt[i][j] = cnt[i - 1][j];
			}
	// for(int i = 1; i <= n; i++)
	// 	for(int j = 1; j <= m; j++)
	// 		printf("f[%d][%d] = %d\n", i, j, f[i][j]);
	printf("%lld\n", cnt[n][m]);
	return 0;
}