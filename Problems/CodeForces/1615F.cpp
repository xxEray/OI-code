#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2000 + 5;
const LL MOD = 1e9 + 7;

int n;
char s[N], t[N];

LL f[N][N], sumf[N][N], g[N][N], sumg[N][N];
int lpi[N], lpj[N], rpi[N], rpj[N];

inline bool is(char c, char c2) { return c == c2 || c == '?'; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%s%s", &n, s + 1, t + 1);
		for(int i = 1; i <= n; i++) if(i & 1) s[i] = (s[i] == '?' ? '?' : ('0' + '1' - s[i]));
		for(int i = 1; i <= n; i++) if(i & 1) t[i] = (t[i] == '?' ? '?' : ('0' + '1' - t[i]));
		for(int i = 0; i <= n + 1; i++) for(int j = 0; j <= n + 1; j++) f[i][j] = g[i][j] = sumf[i][j] = sumg[i][j] = 0;
		f[0][0] = g[n + 1][n + 1] = 1;
		// for(int i = 0; i <= n + 1; i++) f[0][i] = f[i][0] = g[n + 1][i] = g[i][n + 1] = 1;
		// sumf[0][0] = f[0][0];
		// for(int i = 1; i <= n; i++) sumf[i][0] = sumf[i - 1][0] + f[i][0], sumf[0][i] = sumf[0][i - 1] + f[0][i];
		// sumg[n + 1][n + 1] = g[n + 1][n + 1];
		// for(int i = n; i >= 1; i--) sumg[i][n + 1] = sumg[i + 1][n + 1] + g[i][n + 1], sumg[n + 1][i] = sumg[n + 1][i + 1] + g[n + 1][i];
		for(int i = 0, pi = 0; i <= n; i++) {
			lpi[i] = pi;
			for(int j = 0, pj = 0; j <= n; j++) {
				lpj[j] = pj;
				if(is(s[i], '1') && is(t[j], '1') && (i || j))
					f[i][j] = (sumf[i - 1][j - 1] - (pi ? sumf[pi - 1][j - 1] : 0) - (pj ? sumf[i - 1][pj - 1] : 0) + (pi && pj ? sumf[pi - 1][pj - 1] : 0) + 2 * MOD) % MOD;
				sumf[i][j] = ((i ? sumf[i - 1][j] : 0) + (j ? sumf[i][j - 1] : 0) - (i && j ? sumf[i - 1][j - 1] : 0) + f[i][j] + MOD) % MOD;
				if(!is(t[j], '0')) pj = j;
			}
			if(!is(s[i], '0')) pi = i;
		}
		for(int i = n + 1, pi = n + 1; i >= 1; i--) {
			rpi[i] = pi;
			for(int j = n + 1, pj = n + 1; j >= 1; j--) {
				rpj[j] = pj;
				if(is(s[i], '1') && is(t[j], '1') && (i <= n || j <= n))
					g[i][j] = (sumg[i + 1][j + 1] - (pi <= n ? sumg[pi + 1][j + 1] : 0) - (pj <= n ? sumg[i + 1][pj + 1] : 0) + (pi <= n && pj <= n ? sumg[pi + 1][pj + 1] : 0) + 2 * MOD) % MOD;
				sumg[i][j] = ((i <= n ? sumg[i + 1][j] : 0) + (j <= n ? sumg[i][j + 1] : 0) - (i <= n && j <= n ? sumg[i + 1][j + 1] : 0) + g[i][j] + MOD) % MOD;
				if(!is(t[j], '0')) pj = j;
			}
			if(!is(s[i], '0')) pi = i;
		}
		// for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) printf("f[%d][%d] = %lld (%lld, %d, %d)\n", i, j, f[i][j], sumf[i][j], lpi[i], lpj[j]);
		// for(int i = n + 1; i >= 1; i--) for(int j = n + 1; j >= 1; j--) printf("g[%d][%d] = %lld (%lld, %d, %d)\n", i, j, g[i][j], sumg[i][j], rpi[i], rpj[j]);
		LL ans = 0;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				if(is(s[i], '1') && is(t[j], '1')) {
					LL ansl = (sumf[i - 1][j - 1] - (lpi[i] ? sumf[lpi[i] - 1][j - 1] : 0) - (lpj[j] ? sumf[i - 1][lpj[j] - 1] : 0) + (lpi[i] && lpj[j] ? sumf[lpi[i] - 1][lpj[j] - 1] : 0) + 2 * MOD) % MOD;
					LL ansr = (sumg[i + 1][j + 1] - (rpi[i] <= n ? sumg[rpi[i] + 1][j + 1] : 0) - (rpj[j] <= n ? sumg[i + 1][rpj[j] + 1] : 0) + (rpi[i] <= n && rpj[j] <= n ? sumg[rpi[i] + 1][rpj[j] + 1] : 0) + 2 * MOD) % MOD;
					(ans += std::abs(i - j) * ansl % MOD * ansr % MOD) %= MOD;
					// if(std::abs(i - j) && ansl && ansr) printf("(%d, %d): ans += %d * %lld * %lld\n", i, j, std::abs(i - j), ansl, ansr);
				}
		printf("%lld\n", ans);
	}
	return 0;
} /*
6
2
00
11
3
???
???
3
??1
0?0
4
??0?
??11
5
?????
0??1?
10
?01??01?1?
??100?1???

1
2
??
00
*/