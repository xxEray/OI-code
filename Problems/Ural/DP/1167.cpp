#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

const int N = 500 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL pre[N][2];
int n, m;

LL f[N][N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		pre[i][x] = pre[i - 1][x] + 1;
		pre[i][!x] = pre[i - 1][!x];
	}
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= m; j++)
			f[i][j] = LLINF;
	f[0][0] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			for(int k = 1; k <= i - j + 1; k++)
				f[i][j] = std::min(f[i][j], f[i - k][j - 1] + (LL)(pre[i][0] - pre[i - k][0]) * (pre[i][1] - pre[i - k][1]));
	printf("%lld\n", f[n][m]);
	return 0;
}