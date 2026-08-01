#include <cstdio>
#include <algorithm>
#include <vector>

void read(int &x) {
	char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	for(x = 0; '0' <= ch && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}

typedef long long LL;

const int N = 500 + 5;
const int MOD = 998244353;

int n;
int a[N][N];
char b[N][N];

std::vector<int> v[2 * N], w[2 * N];
int f[N][N], g[N][N], fv[2 * N], gv[2 * N];

void mod(int &x) { x >= MOD ? x -= MOD : 0; }

int main() {
#ifndef DEBUG
	freopen("gou.in", "r", stdin);
	freopen("gou.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		char ch = getchar();
		while(ch < 'A' || ch > 'Z') ch = getchar();
		for(int j = 1; j <= n; j++) b[i][j] = ch, ch = getchar();
	}
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) read(a[i][j]);
	for(int i = 1; i <= 2 * n; i++) v[i].push_back(0), w[i].push_back(0);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
		if(b[i][j] == 'L' || b[i][j] == 'R') v[i].push_back(b[i][j] == 'R' ? 1 : -1), w[i].push_back(a[i][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
		if(b[j][i] == 'U' || b[j][i] == 'D') v[i + n].push_back(b[j][i] == 'D' ? 1 : -1), w[i + n].push_back(a[j][i]);
	for(int k = 1; k <= 2 * n; k++) {
		int sz = (int)v[k].size() - 1;
		for(int i = 0; i <= sz; i++) for(int j = 0; j <= sz; j++) f[i][j] = 0, g[i][j] = -1;
		f[0][0] = 1, g[0][0] = 0;
		for(int i = 1; i <= sz; i++) for(int j = 0; j <= i; j++) {
			mod(f[i][j] += f[i - 1][j]);
			if(g[i - 1][j] >= 0) g[i][j] = g[i - 1][j];
			if(0 <= j - v[k][i] && j - v[k][i] <= sz) {
				LL extra = (v[k][i] == -1 ? j - v[k][i] : 1);
				mod(f[i][j] += f[i - 1][j - v[k][i]] * extra % MOD);
				if(g[i - 1][j - v[k][i]] >= 0) {
					if(g[i][j] == -1) g[i][j] = 0;
					mod(g[i][j] += (g[i - 1][j - v[k][i]] + (LL)f[i - 1][j - v[k][i]] * w[k][i] % MOD) * extra % MOD);
				}
			}
		}
		fv[k] = f[sz][0], gv[k] = g[sz][0];
//		for(int i = 1; i <= sz; i++) for(int j = 0; j <= sz; j++) printf("g[%d][%d] = %lld\n", i, j, g[i][j]);
//		printf("%d: (f=%lld, g=%lld) ", k, fv[k], gv[k]);
//		for(int i = 1; i <= sz; i++) printf("%d(%d) ", v[k][i], w[k][i]);
//		puts("");
	}
	int ans = 0;
	for(int i = 1; i <= 2 * n; i++) {
		LL ret = 1;
		for(int j = 1; j <= 2 * n; j++) if(i != j) (ret *= fv[j]) %= MOD;
		(ans += ret * gv[i] % MOD) %= MOD;
	}
	printf("%d\n", ans);
	return 0;
} /*
4
RRLL
RLLL
UUUU
DDDD
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
*/
