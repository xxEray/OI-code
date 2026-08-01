#include <cstdio>
#include <algorithm>
#include <cstring>

// #define int long long

typedef long long LL;

const int N = 300 + 5;
const int MOD = 1e9 + 7;
const int inv2 = (MOD + 1) / 2;

int n, m, k;

int C[N][N], fac[N];

int f[N][N][2];

int dfs(int vcnt, int ecnt, bool fulled) {
	if(ecnt < 0) return 0;
	if(f[vcnt][ecnt][fulled] != -1) return f[vcnt][ecnt][fulled];
	if(!vcnt) return fulled && !ecnt;
	int ret = 0;
	for(int i = 1; i <= std::min(vcnt, k); i++) {
		ret = ((LL)ret + (LL)dfs(vcnt - i, ecnt - (i - 1), fulled || (i == k)) * (LL)C[vcnt - 1][i - 1] % MOD * (i == 1 ? 1LL : (LL)fac[i] * inv2 % MOD) % MOD) % MOD;
		if(i != 1) ret = ((LL)ret + (LL)dfs(vcnt - i, ecnt - i, fulled || (i == k)) * (LL)C[vcnt - 1][i - 1] % MOD * (i == 2 ? 1LL : (LL)fac[i - 1] * inv2 % MOD) % MOD) % MOD;
	}
	return f[vcnt][ecnt][fulled] = ret;
}

signed main() {
	std::memset(f, -1, sizeof(f));
	std::scanf("%d%d%d", &n, &m, &k);
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = (LL)fac[i - 1] * i % MOD;
	for(int i = 0; i <= n; i++) C[i][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= i; j++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
	int ans = dfs(n, m, 0);
	std::printf("%d\n", ans);
	return 0;
}