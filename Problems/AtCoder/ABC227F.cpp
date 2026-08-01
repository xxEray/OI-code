#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 30 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL a[N][N];
int n, m, K;

LL t[N * N];
LL f[N][N][N * 2];

#define val(x) ((x) >= pivot ? (x) : 0)

int main() {
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%lld", &a[i][j]), t[(i - 1) * m + j] = a[i][j];
	for(int i = 0; i <= n; i++) for(int k = 0; k <= n + m - 1; k++) f[i][0][k] = LLINF;
	for(int j = 0; j <= m; j++) for(int k = 0; k <= n + m - 1; k++) f[0][j][k] = LLINF;
	std::sort(t + 1, t + n * m + 1);
	LL ans = LLINF;
	for(int r = 1; r <= n * m; r++) {
		int pivot = t[r];
		for(int i = 0; i <= n; i++) for(int j = 0; j <= m; j++) for(int k = 0; k <= n + m - 1; k++) f[i][j][k] = LLINF;
		f[1][1][a[1][1] >= pivot] = val(a[1][1]);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				for(int k = 0; k <= K; k++) {
					if(i == 1 && j == 1 && k <= 1) continue;
					if(k - (a[i][j] >= pivot) >= 0) f[i][j][k] = std::min(f[i][j - 1][k - (a[i][j] >= pivot)], f[i - 1][j][k - (a[i][j] >= pivot)]) + val(a[i][j]);
					if(a[i][j] == pivot) f[i][j][k] = std::min({f[i][j][k], f[i][j - 1][k], f[i - 1][j][k]});
				}
		// printf("pivot = %d, ret = %lld\n", pivot, f[n][m][K]);
		ans = std::min(ans, f[n][m][K]);
	}
	printf("%lld\n", ans);
	return 0;
}