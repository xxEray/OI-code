#include <cstdio>
#include <algorithm>

typedef long long LL;

const int MOD = 998244353;

struct Query { int l, r; } q[12];
int n, k;

LL pre[200005];

int main() {
	std::scanf("%d%d", &n, &k);
	for(int i = 1; i <= k; i++) std::scanf("%d%d", &q[i].l, &q[i].r);
	pre[1] = 1;
	for(int i = 2; i <= n; i++) {
		LL f = 0;
		for(int j = 1; j <= k; j++)
			if(i - q[j].l >= 0)
				f = ((LL)f + pre[i - q[j].l] - pre[std::max(i - q[j].r - 1, 0)] + MOD) % MOD;
		// std::printf("f[%d] = %lld\n", i, f);
		pre[i] = ((LL)pre[i - 1] + f) % MOD;
	}
	std::printf("%d\n", (pre[n] - pre[n - 1] + MOD) % MOD);
	return 0;
}