#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 10000 + 5;
const int M = 700 + 5;
const LL MOD = 993244353;

const char t1[] = "sakana"; // j = 1,2,3,4,5,0
const char t2[] = "chinanago"; // j = 6,7,8,9,10,11,12,13,0

int n, m;
char s[N];

LL f[2][2 * M][20];

int main() {
#ifndef DEBUG
	freopen("lycoris.in", "r", stdin);
	freopen("lycoris.out", "w", stdout);
#endif
	scanf("%d%s", &n, s + 1);
	m = (n + 14) / 15;
	f[0][m][0] = 1;
	for(int i = 1; i <= n; i++) {
		int t = i & 1;
		for(int j = 0; j <= 2 * m; j++) {
			f[t][j][0] = f[t ^ 1][j][0] * (s[i] == '?' ? 24 : (s[i] != 's' && s[i] != 'c'));
			for(int k = 1; k <= 5; k++) f[t][j][0] += f[t ^ 1][j][k] * (s[i] == '?' ? 23 : (s[i] != t1[k] && s[i] != 's' && s[i] != 'c'));
			for(int k = 6; k <= 13; k++) f[t][j][0] += f[t ^ 1][j][k] * (s[i] == '?' ? 23 : (s[i] != t2[k - 5] && s[i] != 's' && s[i] != 'c'));
			if(j > 0) f[t][j][0] += f[t ^ 1][j - 1][5] * (s[i] == '?' || s[i] == 'a');
			if(j < 2 * m) f[t][j][0] += f[t ^ 1][j + 1][13] * (s[i] == '?' || s[i] == 'o');
			f[t][j][0] %= MOD;
			f[t][j][1] = 0, f[t][j][6] = 0;
			if(s[i] == 's' || s[i] == '?') {
				for(int k = 0; k <= 13; k++) f[t][j][1] += f[t ^ 1][j][k];
				f[t][j][1] %= MOD;
			}
			if(s[i] == 'c' || s[i] == '?') {
				for(int k = 0; k <= 13; k++) f[t][j][6] += f[t ^ 1][j][k];
				f[t][j][6] %= MOD;
			}
			for(int k = 2; k <= 5; k++) f[t][j][k] = f[t ^ 1][j][k - 1] * (s[i] == '?' || s[i] == t1[k - 1]);
			for(int k = 7; k <= 13; k++) f[t][j][k] = f[t ^ 1][j][k - 1] * (s[i] == '?' || s[i] == t2[k - 6]);
//			for(int k = 0; k <= 13; k++) if(f[t][j][k]) printf("f[%d][%d][%d] = %lld\n", i, j - m, k, f[t][j][k]);
		}
	}
	LL ans = 0;
	for(int k = 0; k <= 13; k++) ans += f[n & 1][m][k];
	printf("%lld\n", ans % MOD);
	return 0;
} /*
n * (n / 15) * (15 + 1) * 2

7
???????
*/
