#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 500 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL a[N], d[N];
int n, m;

LL f[N][N];

int main() {
	memset(f, 0x3f, sizeof(f));
	scanf("%d", &n), scanf("%lld", &d[n + 1]), scanf("%d", &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &d[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	f[1][1] = 0;
	for(int i = 2; i <= n + 1; i++)
		for(int j = 1; j <= i; j++)
			for(int k = 1; k < i; k++)
				f[i][j] = std::min(f[i][j], f[k][j - 1] + (d[i] - d[k]) * a[k]);
	// for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= n; j++) printf("%d %d -> %lld\n", i, j, f[i][j]);
	LL ans = LLINF;
	for(int i = n - m; i <= n; i++) ans = std::min(ans, f[n + 1][i + 1]);
	printf("%lld\n", ans);
	return 0;
} /*
4 10 2
0 3 4 8
5 8 3 6

*/