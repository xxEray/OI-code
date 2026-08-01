#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 2000 + 5;

LL a[N];
int n, m;

LL f[N][N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	memset(f, ~0x3f, sizeof(f));
	for(int i = 0; i <= n; i++) f[i][0] = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
		f[i][j] = std::max(f[i - 1][j], f[i - 1][j - 1] + j * a[i]);
	printf("%lld\n", f[n][m]);
	return 0;
}