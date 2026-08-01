#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1000 + 5;
const LL MOD = 998244353;

int n, m, argc, argf;
int a[N][N];

int rmost[N][N], dmost[N][N];

int main() {
#ifndef DEBUG
	freopen("plant.in", "r", stdin);
	freopen("plant.out", "w", stdout);
#endif
	int T; scanf("%d%*d", &T);
	while(T--) {
		scanf("%d%d%d%d", &n, &m, &argc, &argf);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%1d", &a[i][j]);
		for(int i = 1; i <= n; i++) {
			rmost[i][m] = (a[i][m] == 0);
			for(int j = m - 1; j >= 1; j--) rmost[i][j] = (a[i][j] == 0 ? rmost[i][j + 1] + 1 : 0);
		}
		for(int j = 1; j <= m; j++) {
			dmost[n][j] = (a[n][j] == 0);
			for(int i = n - 1; i >= 1; i--) dmost[i][j] = (a[i][j] == 0 ? dmost[i + 1][j] + 1 : 0);
		}
		LL ansc = 0, ansf = 0;
		for(int j = 1; j <= m; j++) {
			LL sum = 0;
			for(int i = 2; i <= n; i++) {
				if(a[i][j] || a[i - 1][j]) { sum = 0; continue; }
				(ansc += sum * (rmost[i][j] - 1) % MOD) %= MOD;
				(ansf += sum * (rmost[i][j] - 1) % MOD * (dmost[i][j] - 1) % MOD) %= MOD;
				(sum += rmost[i - 1][j] - 1) %= MOD;
			}
		}
		printf("%lld %lld\n", ansc * argc, ansf * argf);
	}
	return 0;
}