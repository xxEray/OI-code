// Don't kill monsters, you dolphin!
// Authored by E-ray from team CDFLS: OPJ BLOCK

#include <bits/stdc++.h>

typedef long long LL;

const int N = 400 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n; LL X, Y;
int a[N];

LL f[2][N][N];

int main() {
	scanf("%d%lld%lld", &n, &X, &Y);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::reverse(a + 1, a + n + 1);
	memset(f, 0x3f, sizeof(f));
	for(int len = 1; len <= n; len++)
		for(int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			bool same = true;
			for(int k = i; k <= j; k++) same &= (a[k] == a[i]);
			if(same) f[1][i][j] = X, f[0][i][j] = (j - i + 1) * Y + X;
			for(int k = i; k < j; k++) {
				f[0][i][j] = std::min({f[0][i][j], f[0][i][k] + f[0][k + 1][j], f[1][i][k] + f[0][k + 1][j]});
				f[1][i][j] = std::min({f[1][i][j], f[0][i][k] + f[1][k + 1][j], f[1][i][k] + f[1][k + 1][j]});
			}
			int cnt = 0;
			for(int k = j; k >= i; k--)
				if(a[j] == a[k]) cnt++;
				else break;
			for(int k = i; k < j - cnt; k++) if(a[k] == a[j]) {
				f[1][i][j] = std::min({f[1][i][j], f[1][i][k] + f[0][k + 1][j - cnt] + 2 * cnt * Y, f[1][i][k] + f[1][k + 1][j - cnt] + 2 * cnt * Y});
				f[0][i][j] = std::min({f[0][i][j], f[0][i][k] + f[0][k + 1][j - cnt] + cnt * Y, f[0][i][k] + f[1][k + 1][j - cnt] + cnt * Y});
			}
		}
	// for(int i = 1; i <= n; i++) for(int j = i; j <= n; j++) printf("f[%d][%d] = %lld,%lld\n", i, j, f[0][i][j], f[1][i][j]);
	printf("%lld\n", std::min(f[0][1][n], f[1][1][n]));
	return 0;
}