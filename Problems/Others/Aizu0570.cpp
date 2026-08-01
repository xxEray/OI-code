#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 500 + 5;
const int MOD = 10000;

int m;
char s1[N], s2[N];

int f[N][N][10][2][2][2];
int calc(char *s, int mx) {
	memset(f, 0, sizeof(f));
	int n = strlen(s + 1);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) for(int k = 0; k <= 9; k++)
			for(int k1 = 0; k1 <= 1; k1++) for(int k2 = 0; k2 <= 1; k2++) for(int k3 = 0; k3 <= 1; k3++)
				for(int t = 0; t <= 9; t++) if((k2 ? (k < t) : (k > t)) && (k1 == 0 || t <= s[i + 1] - '0'))
					(f[i + 1][(j * 10 + t) % m][t][k1 && t == s[i + 1] - '0'][!k2][1] += f[i][j][k][k1][k2][k3]) %= MOD;
		for(int k = 1; k <= 9; k++) if(i || k <= s[1] - '0') for(int k2 = 0; k2 <= 1; k2++) (f[i + 1][k % m][k][i == 0 && k == s[1] - '0'][k2][0] += 1) %= MOD;
	}
	// for(int i = 0; i <= n; i++) for(int j = 0; j < m; j++) for(int k = 0; k <= 9; k++) for(int k1 = 0; k1 <= 1; k1++) for(int k2 = 0; k2 <= 1; k2++) for(int k3 = 0; k3 <= 1; k3++)
	// 	if(f[i][j][k][k1][k2][k3]) printf("f[%d][%d][%d][%d][%d] = %d\n", i, j, k, k1, k2, f[i][j][k][k1][k2][k3]);
	int ans = 0;
	for(int k = 0; k <= 9; k++) for(int k1 = 0; k1 <= mx; k1++) (ans += f[n][0][k][k1][0][0] + f[n][0][k][k1][0][1] + f[n][0][k][k1][1][1]) %= MOD;
	// printf("%s: %d\n", s + 1, ans);
	return ans;
}

int main() {
	scanf("%s%s%d", s1 + 1, s2 + 1, &m);
	printf("%d\n", (calc(s2, 1) - calc(s1, 0) + MOD) % MOD);
	// scanf("%s%d", s1 + 1, &m);
	// printf("%d\n", calc(s1, 1));
	return 0;
}