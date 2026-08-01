#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 500 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

LL a[N][N], b[N][N];
int n;

LL sa[N][N], sb[N][N];
LL f[N][N];

inline LL sum(LL t[][N], int l1, int r1, int l2, int r2) { return l1 > r1 || l2 > r2 ? 0 : t[r1][r2] - t[l1 - 1][r2] - t[r1][l2 - 1] + t[l1 - 1][l2 - 1]; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= i - 1; j++) scanf("%lld", &b[j][i]);
		for(int j = i + 1; j <= n; j++) scanf("%lld", &a[i][j]);
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			sa[i][j] = sa[i - 1][j] + sa[i][j - 1] - sa[i - 1][j - 1] + a[i][j];
			sb[i][j] = sb[i - 1][j] + sb[i][j - 1] - sb[i - 1][j - 1] + b[i][j];
		}
	for(int i = 1; i < n; i++) for(int j = i + 1; j < n; j++) f[i][j] = LLINF;
	for(int i = 1; i < n; i++) for(int j = i + 1; j < n; j++) f[i][j] = sum(sa, 1, i, 1, i) + sum(sa, i + 1, j, i + 1, j);
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) printf("sa[%d][%d] = %lld, sb[%d][%d] = %lld\n", i, j, sa[i][j], i, j, sb[i][j]);
	for(int i = 1; i < n; i++)
		for(int j = i + 1; j < n; j++)
			for(int k = j + 1; k < n; k++)
				f[j][k] = std::min(f[j][k], f[i][j] + sum(sa, j + 1, k, j + 1, k) + sum(sb, 1, i, j + 1, k));
	// for(int i = 1; i < n; i++) for(int j = i + 1; j < n; j++) printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
	LL ans = sum(sa, 1, n, 1, n);
	for(int i = 1; i < n; i++) ans = std::min(ans, sum(sa, 1, i, 1, i) + sum(sa, i + 1, n, i + 1, n));
	for(int i = 1; i < n; i++) for(int j = i + 1; j < n; j++) ans = std::min(ans, f[i][j] + sum(sa, j + 1, n, j + 1, n) + sum(sb, 1, i, j + 1, n));
	printf("%lld\n", ans);
	return 0;
}