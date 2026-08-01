#include <cstdio>
#include <algorithm>
#include <cassert>

typedef long long LL;

const int N = 5000 + 5;
const LL MOD = 998244353;

int n;
int a[N];
LL f[N][N], fl[N][N], fr[N][N], fs[N][N];

struct ST_Table {
	int go[N][21];
	int ind[N][21];
	int lg[N];
	void init() {
		lg[0] = -1;
		for(int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1;
		for(int i = 1; i <= n; i++) go[i][0] = a[i], ind[i][0] = i;
		for(int j = 1; j <= 20; j++)
			for(int i = 1; i + (1 << j) - 1 <= n; i++)
				if(go[i][j - 1] > go[i + (1 << (j - 1))][j - 1]) ind[i][j] = ind[i][j - 1], go[i][j] = go[i][j - 1];
				else ind[i][j] = ind[i + (1 << (j - 1))][j - 1], go[i][j] = go[i + (1 << (j - 1))][j - 1];
	}
	int prod(int lb, int rb) {
		assert(lb <= rb);
		int k = lg[rb - lb + 1];
		return go[lb][k] > go[rb - (1 << k) + 1][k] ? go[lb][k] : go[rb - (1 << k) + 1][k];
	}
	int index(int lb, int rb) {
		assert(lb <= rb);
		int k = lg[rb - lb + 1];
		return go[lb][k] > go[rb - (1 << k) + 1][k] ? ind[lb][k] : ind[rb - (1 << k) + 1][k];
	}
} ST;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	ST.init();
	for(int i = 1; i <= n; i++) f[i][i] = 1, fl[i][i] = fr[i][i] = 1;
	for(int len = 2; len <= n; len++)
		for(int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			int k = ST.index(i, j);
			f[i][j] = ((fl[i][k - 1] + 1 - fs[i][k - 1]) * (fr[k + 1][j] + 1 - fs[k + 1][j])) % MOD;
			fl[i][j] = (fl[i][j - 1] + f[i][j]) % MOD;
			fr[i][j] = (fr[i + 1][j] + fr[i][j]) % MOD;
			fs[i][j] = (fs[i][j - 1] + fr[i][j]) % MOD;
			printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
		}
	printf("%lld\n", f[1][n]);
	return 0;
}