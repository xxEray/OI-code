#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 3e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

LL a[N];
int n;

LL f[N][25];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), a[i] /= 100;
	for(int j = 1; j <= 20; j++) f[0][j] = LLINF;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= 20; j++) {
			f[i][j] = LLINF;
			if(j - a[i] / 10 >= 0) f[i][j] = std::min(f[i][j], f[i - 1][j - a[i] / 10] + a[i]);
			for(int k = 1; k <= a[i] && j + k <= 20; k++)
				f[i][j] = std::min(f[i][j], f[i - 1][j + k] + a[i] - k);
			// if(f[i][j] < INF) printf("f[%d][%d] = %d\n", i, j, f[i][j]);
		}
	LL ans = LLINF;
	for(int i = 0; i <= 20; i++) ans = std::min(ans, f[n][i]);
	printf("%lld\n", ans * 100LL);
	return 0;
}