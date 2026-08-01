#include <bits/stdc++.h>

const int N = 350 + 5;

int n, K;
char s[N];
int pre[N], suf[N];
bool f[N][N][N];

int main() {
#ifndef DEBUG
	freopen("vegetable.in", "r", stdin);
	freopen("vegetable.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%s", &n, &K, s + 1);
		pre[0] = suf[n + 1] = 0;
		for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] + (s[i] == 'V');
		for(int i = n; i >= 1; i--) suf[i] = suf[i + 1] + (s[i] == 'V');
		for(int len = 1; len <= n; len++)
			for(int i = 1; i + len - 1 <= n; i++) {
				int j = i + len - 1;
				for(int k = std::max(pre[i - 1] + suf[j + 1] - K + 1, 0); k <= std::min(K, pre[i - 1] + suf[j + 1]); k++)
					f[i][j][k] = (!f[i + 1][j][(pre[i - 1] + suf[j + 1] - k) + (s[i] == 'V')] && !f[i][j - 1][(pre[i - 1] + suf[j + 1] - k) + (s[j] == 'V')]) && (k < K);
			}
		// for(int i = 1; i <= n; i++) for(int j = i; j <= n; j++)
		// 	for(int k = std::max(pre[i - 1] + suf[j + 1] - K + 1, 0); k <= std::min(K, pre[i - 1] + suf[j + 1]); k++)
		// 		printf("f[%d][%d][%d] = %d\n", i, j, k, f[i][j][k]);
		puts((f[1][n - 1][(s[n] == 'V')] || f[2][n][(s[1] == 'V')]) ? "yes" : "no");
	}
	return 0;
} /*
1
5 1
FVFVF
*/