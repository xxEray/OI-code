#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2000 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

struct Node { LL val; int pos; } a[N];
int n;

LL dp[N][N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i].val), a[i].pos = i;
	std::sort(a + 1, a + n + 1, [](Node x, Node y) { return x.val > y.val; });
	for(int i = 0; i <= n + 1; i++) dp[0][i] = dp[i][n + 1] = -LLINF;
	for(int len = n - 1; len >= 1; len--)
		for(int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			int k = n - len;
			dp[i][j] = std::max(dp[i - 1][j] + std::abs(a[k].pos - (i - 1)) * a[k].val,
			dp[i][j + 1] + std::abs(a[k].pos - (j + 1)) * a[k].val);
		}
	// for(int i = 1; i <= n; i++)
	// 	for(int j = i; j <= n; j++)
	// 		printf("dp[%d][%d] = %lld\n", i, j, dp[i][j]);
	LL ans = 0;
	for(int i = 1; i <= n; i++) ans = std::max(ans, dp[i][i] + std::abs(a[n].pos - i) * a[n].val);
	printf("%lld\n", ans);
	return 0;
}