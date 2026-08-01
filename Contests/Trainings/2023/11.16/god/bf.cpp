#include <bits/stdc++.h>

typedef long long LL;

const int N = 100 + 5;
const LL MOD = 998244353;

int n, K;
int a[N];

int ans = 0;
//std::vector<std::vector<int>> vct[N];
void dfs(int id) {
	if(id == n + 1) {
		int pre[n + 3], suf[n + 3];
		pre[0] = suf[n + 1] = 0;
		for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] | a[i];
		for(int i = n; i >= 1; i--) suf[i] = suf[i + 1] | a[i];
		for(int i = 0; i <= n; i++) if(pre[i] == suf[i + 1]) {
			ans++;
//			vct[i].emplace_back(a + 1, a + n + 1);
			break;
		}
		return;
	}
	for(int i = 0; i < (1 << K); i++) a[id] = i, dfs(id + 1);
}

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

int main() {
	scanf("%d%d", &n, &K);
	dfs(1);
//	printf("count = %lld\n", ans);
	printf("%lld\n", ans * inv(qpow(2, (LL)n * K)) % MOD);
//	for(int i = 0; i <= n; i++) {
//		printf("vct[%d]:\n", i);
//		for(const auto &vc : vct[i]) {
//			printf("  ");
//			for(auto x : vc) printf("%d ", x);
//			puts("");
//		}
//	}
	return 0;
}
