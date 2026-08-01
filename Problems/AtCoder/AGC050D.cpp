#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 40 + 5;
const int MOD = 998244353;

int n, m;

LL qpow(LL a, LL b) { LL ret = 1; for(; b; b >>= 1) { if(b & 1) { ret = ret * a % MOD; } a = a * a % MOD; } return ret; }
LL inv(LL x) { return qpow(x, MOD - 2); }

bool vis[N][N][N];
std::vector<LL> dp[N][N][N];
// i rounds, j people left, now kth person (not), the possibilities of n people
std::vector<LL> dfs(LL i, LL j, LL k) {
	if(vis[i][j][k]) return dp[i][j][k];
	if(k == j + 1) return dfs(i + 1, j, 1);
	vis[i][j][k] = true;
	std::vector<LL> &ret = dp[i][j][k];
	
}

int main() {
	scanf("%d%d", &n, &m);
	std::vector<LL> ans = dfs(1, n, 1);
	for(LL &x : ans) printf("%lld\n", x);
	return 0;
}