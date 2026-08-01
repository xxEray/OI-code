#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 5e3 + 5;

LL a[N], b[N];
int n, m;

LL f[N][N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= m; i++) {
		int x; LL y;
		scanf("%d%lld", &x, &y);
		b[x] += y;
	}
	f[0][0] = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= i - 1; j++) f[i][0] = std::max(f[i][0], f[i - 1][j] + b[0]);
		for(int j = 1; j <= n; j++) f[i][j] = f[i - 1][j - 1] + a[i] + b[j];
	}
	LL ans = 0;
	for(int j = 0; j <= n; j++) ans = std::max(ans, f[n][j]);
	printf("%lld\n", ans);
	return 0;
}