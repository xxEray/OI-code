#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 18 + 5;
const int MAXS = (1 << 18) + 5;
const LL MOD = 998244353;

int n, m;
char a[N][N];

LL f[N][MAXS], g[N][MAXS];

inline bool is(char x, char c) { return x == c || x == '?'; }

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		char s[N];
		scanf("%s", s + 1);
		for(int j = 1; j <= m; j++) a[i][j] = s[j];
	}
	int U = (1 << m) - 1;
	f[0][U] = 1;
	for(int i = 1; i <= n; i++) {
		for(int s = 0; s <= U; s++) g[m][s] = f[i - 1][s];
		for(int j = m - 1; j >= 0; j--) for(int s = 0; s <= U; s++)
			if(!(s >> (j + 1 - 1) & 1)) g[j][s] = is(a[i][j + 1], '0') * (g[j + 1][s] + g[j + 1][s | (1 << (j + 1 - 1))]) % MOD;
			else g[j][s] = is(a[i][j + 1], '1') * g[j + 1][s];
		// printf("i=%d:\n", i);
		// for(int j = 0; j <= m; j++) for(int s = 0; s <= U; s++) if(g[j][s]) printf("g[%d][%d] = %lld\n", j, s, g[j][s]);
		for(int s = 0; s <= U; s++) {
			bool flag = true;
			for(int j = 0; j <= m; j++) {
				flag &= (j == 0 || is(a[i][j], '1'));
				if(!flag) break;
				if(j == 0 || !(s >> (j - 1) & 1)) (f[i][s] += g[j][s]) %= MOD;
			}
		}
		// for(int s = 0; s <= U; s++) if(f[i][s]) printf("f[%d][%d] = %lld\n", i, s, f[i][s]);
	}
	LL ans = 0;
	for(int s = 0; s <= U; s++) (ans += f[n][s]) %= MOD;
	printf("%lld\n", ans);
	return 0;
} /*
2 2
??
??
*/