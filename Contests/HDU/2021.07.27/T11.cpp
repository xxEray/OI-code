#include <cstdio>
#include <algorithm>
#include <map>

typedef long long LL;

std::map<LL, LL> dp;

LL n, m;
LL dfs(LL x) {
	if(x <= m) return 1;
	if(dp.find(x) != dp.end()) return dp[x];
	return dp[x] = dfs(x / 2) + dfs(x - x / 2) + 1;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		dp.clear();
		scanf("%lld%lld", &n, &m);
		printf("%lld\n", dfs(n));
	}
	return 0;
}