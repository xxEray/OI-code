#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const int M = 7;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL a[M][N];
int n, m;

int main() {
// #ifndef DEBUG
	// freopen("sort.in", "r", stdin);
	// freopen("sort.out", "w", stdout);
// #endif
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= m; i++) for(int j = 1; j <= n; j++) scanf("%lld", &a[i][j]);
	LL sum = 0;
	for(int i = 1; i <= m; i++) for(int j = 1; j <= n; j++) sum += a[i][j];
	if(m == 2) {
		printf("%lld\n", sum * n * 2);
		return 0;
	} else if(n <= 5000) {
		LL ans = 0;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) {
			LL mn = LLINF, mx = -LLINF;
			for(int k = 1; k <= m; k++) mn = std::min(mn, a[k][i] + a[k][j]), mx = std::max(mx, a[k][i] + a[k][j]);
			ans += mx + mn;
		}
		printf("%lld\n", ans);
	}
	return 0;
}