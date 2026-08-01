#include <cstdio>
#include <algorithm>

typedef long long LL;

const LL MOD = 1e9 + 7;

int K, x;

LL f(int x) {
	LL ret = 1;
	while(x) {
		if(x % 10) (ret *= x % 10) %= MOD;
		x /= 10;
	}
	return ret;
}

LL ans = 0;
void dfs(int id, int sum) {
	if(id == K + 1) {
		(ans += f(sum)) %= MOD;
		return;
	}
	for(int i = 0; i <= x; i++) dfs(id + 1, sum + i);
}

int main() {
#ifndef DEBUG
	freopen("ke.in", "r", stdin);
	freopen("ke.out", "w", stdout);
#endif
	scanf("%d%d", &K, &x);
	dfs(1, 0);
	printf("%lld\n", ans);
	return 0;
}
