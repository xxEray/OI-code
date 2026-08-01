#include <bits/stdc++.h>

const int N = 1e6 + 5;
const int INF = 0x3f3f3f3f;

int n;
char s[N], t[N];

int f[N][3];

int main() {
	scanf("%d%s%s", &n, s + 1, t + 1);
	for(int i = 1; i <= n; i++) s[i] -= '0', t[i] -= '0';
	for(int i = 0; i <= n; i++) f[i][0] = f[i][1] = f[i][2] = INF;
	f[0][2] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= 2; j++) {
			int fj = (t[i] != (j == 2 ? s[i] : j));
			for(int k = 0; k <= 2; k++) {
				int fk = (i == 1 ? 0 : (t[i - 1] != (k == 2 ? s[i - 1] : k)));
				f[i][j] = std::min(f[i][j], f[i - 1][k] + (fk == 0 && fj == 1) + (j != 2 && j != k));
			}
			// printf("f[%d][%d] = %d (fj = %d)\n", i, j, f[i][j], fj);
		}
	int ans = INF;
	for(int j = 0; j <= 2; j++) ans = std::min(ans, f[n][j]);
	printf("%d\n", ans);
	return 0;
}