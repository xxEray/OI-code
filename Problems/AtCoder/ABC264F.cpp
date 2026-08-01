#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2000 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
int a[N][N];
LL costr[N], costc[N];
LL f[N][N][2][2];

void chkmin(LL &x, LL y) { if(x > y) x = y; }

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &costr[i]);
	for(int i = 1; i <= m; i++) scanf("%lld", &costc[i]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%1d", &a[i][j]);
	for(int i = 0; i <= n; i++) for(int j = 0; j <= m; j++) for(int k = 0; k <= 1; k++) for(int ki = 0; ki <= 1; ki++) f[i][j][k][ki] = LLINF;
	f[1][1][a[1][1]][0] = 0, f[1][1][a[1][1] ^ 1][0] = costc[1], f[1][1][a[1][1] ^ 1][1] = costr[1], f[1][1][a[1][1]][1] = costr[1] + costc[1];
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) for(int k = 0; k <= 1; k++) for(int ki = 0; ki <= 1; ki++) {
		int kj = a[i][j] ^ ki ^ k;
		chkmin(f[i][j][k][ki], f[i - 1][j][k][a[i - 1][j] ^ kj ^ k] + (ki ? costr[i] : 0));
		chkmin(f[i][j][k][ki], f[i][j - 1][k][ki] + (kj ? costc[j] : 0));
	}
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) for(int ki = 0; ki <= 1; ki++) printf("f[%d][%d][%d][%d] = %lld\n", i, j, ki, a[i][j] ^ ki, f[i][j][ki]);
	printf("%lld\n", std::min({f[n][m][0][0], f[n][m][0][1], f[n][m][1][0], f[n][m][1][1]}));
	return 0;
}