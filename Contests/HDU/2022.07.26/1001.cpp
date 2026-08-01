#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 500 + 5;
const LL MOD = 1e9 + 7;

int a[N];
int n;
LL m;

LL f[N][N], g[N][N];

inline LL mod(LL x) { return x >= MOD ? x - MOD : x; }
inline void mod_eq(LL &x) { x >= MOD ? x -= MOD : 0; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%lld", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 0; i <= n + 1; i++) for(int j = 0; j <= n + 1; j++) f[i][j] = g[i][j] = 0;
		for(int i = 1; i <= n + 1; i++) f[i][i - 1] = 1;
		for(int len = 1; len <= n; len++)
			for(int i = 1; i + len - 1 <= n; i++) {
				int j = i + len - 1;
				if(a[i] && a[j]) {
					if(a[i] > 0 && a[i] == -a[j]) f[i][j] = mod(f[i + 1][j - 1] + g[i + 1][j - 1]);
					else f[i][j] = 0;
				} else if(a[i] || a[j]) {
					if(a[i] < 0 || a[j] > 0) f[i][j] = 0;
					else f[i][j] = mod(f[i + 1][j - 1] + g[i + 1][j - 1]);
				} else {
					f[i][j] = mod(f[i + 1][j - 1] + g[i + 1][j - 1]) * m % MOD;
				}
				for(int k = i; k < j; k++) mod_eq(g[i][j] += f[i][k] * mod(f[k + 1][j] + g[k + 1][j]) % MOD);
			}
		// for(int i = 1; i <= n; i++) for(int j = i; j <= n; j++) printf("f[%d][%d] = %lld, %lld\n", i, j, f[i][j], g[i][j]);
		printf("%lld\n", mod(f[1][n] + g[1][n]));
	}
	return 0;
} /*
1
6 1
0 0 0 0 0 0
*/