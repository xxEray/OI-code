#include <bits/stdc++.h>

typedef long long LL;

const int N = 300 + 5;
const LL MOD = 998244353;
const LL inv2 = (MOD + 1) / 2;

int a[N * N];
int n, m;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL power2[N * N], val[N * N], invpower2[N * N];

int occur[N][N], cnt[N];
int vct[N];

int fl[N][N * N], fr[N][N * N];
int flu[N][N * N], fru[N][N * N];

template<typename T> inline void mod(T &x) { if(x >= MOD) x -= MOD; }

int main() {
#ifndef DEBUG
	freopen("intermediate.in", "r", stdin);
	freopen("intermediate.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n * m; i++) scanf("%d", &a[i]), occur[a[i]][++cnt[a[i]]] = i;
	power2[0] = 1, invpower2[0] = 1;
	for(int i = 1; i <= n * m; i++) power2[i] = power2[i - 1] * 2 % MOD, invpower2[i] = invpower2[i - 1] * inv2 % MOD, val[i] = (power2[i] + MOD - 1) % MOD;
	LL ans = 0;
	// 1
	(ans += n * val[m]) %= MOD;
	// 2
	(ans += (LL)n * (n - 1) / 2 % MOD * val[m] % MOD * val[m] % MOD) %= MOD;
	// printf("ans_1 + ans_2 = %lld\n", ans);
	// 3 (partial, the others are calculated in 4)
	for(int i = 1; i <= n * m; i++) fl[a[i]][i]++, fr[a[i]][i]++;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n * m; j++) fl[i][j] += fl[i][j - 1];
	for(int i = 1; i <= n; i++) for(int j = n * m; j >= 1; j--) fr[i][j] += fr[i][j + 1];
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n * m; j++) mod(flu[i][j] = val[fl[i][j]] + flu[i - 1][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n * m; j++) mod(fru[i][j] = val[fr[i][j]] + fru[i - 1][j]);
	for(int i = 1; i <= n * m; i++) mod(ans += flu[a[i] - 1][i - 1] * (flu[n][i - 1] - flu[a[i]][i - 1] + MOD) % MOD * power2[fr[a[i]][i + 1]] % MOD);
	for(int i = 1; i <= n * m; i++) mod(ans += fru[a[i] - 1][i + 1] * (fru[n][i + 1] - fru[a[i]][i + 1] + MOD) % MOD * power2[fl[a[i]][i - 1]] % MOD);
	// printf("ans_1 + ans_2 + ans_3 = %lld\n", ans);
	// 4 (and also the rest of 3)
	for(int p = 1; p <= n; p++)
		for(int q = p + 1; q <= n; q++) {
			for(int i = 1, j = 1, k = 1; i <= m || j <= m; )
				if(j > m || (i <= m && occur[p][i] < occur[q][j])) vct[k++] = occur[p][i++];
				else vct[k++] = occur[q][j++];
			// (flu[q - 1][i - 1] - flu[p][i - 1]) * invpower2[fl[p][i]] * invpower2[fl[q][i]]
			// (fru[q - 1][j + 1] - fru[p][j + 1]) * power2[fl[p][j - 1]] * power2[fl[q][j - 1]]
			LL sum1 = 0, sum2 = 0, sum3 = 0;
			for(int o = 1; o <= 2 * m; o++) {
				int i = vct[o];
				mod(ans += sum1 * (fru[q - 1][i + 1] - fru[p][i + 1] + MOD) % MOD * power2[fl[p][i - 1]] % MOD * power2[fl[q][i - 1]] % MOD);
				mod(sum1 += (flu[q - 1][i - 1] - flu[p][i - 1] + MOD) * invpower2[fl[p][i]] % MOD * invpower2[fl[q][i]] % MOD);
			}
			for(int o = 1; o <= m; o++) {
				int i = occur[p][o];
				mod(ans += MOD - sum2 * (fru[q - 1][i + 1] - fru[p][i + 1] + MOD) % MOD * power2[fl[p][i - 1]] % MOD);
				mod(sum2 += (flu[q - 1][i - 1] - flu[p][i - 1] + MOD) * invpower2[fl[p][i]] % MOD);
			}
			for(int o = 1; o <= m; o++) {
				int i = occur[q][o];
				mod(ans += MOD - sum3 * (fru[q - 1][i + 1] - fru[p][i + 1] + MOD) % MOD * power2[fl[q][i - 1]] % MOD);
				mod(sum3 += (flu[q - 1][i - 1] - flu[p][i - 1] + MOD) * invpower2[fl[q][i]] % MOD);
			}
		}
	printf("%lld\n", ans);
	return 0;
} /*
3 2
2 1 3 2 1 3
*/