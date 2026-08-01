#include <bits/stdc++.h>

const int N = 500 + 5;
const int MOD = 998244353;

int n, m;
char s[N][N];

int w[2 * N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	int ans = 1;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
		if(s[i][j] != '.') {
			if(w[i + j] && w[i + j] != s[i][j]) ans = 0;
			else w[i + j] = s[i][j];
		}
	for(int i = 2; i <= n + m; i++) if(!w[i]) (ans *= 2) %= MOD;
	printf("%d\n", ans);
	return 0;
}