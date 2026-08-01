#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e7 + 5;
const LL MOD = 998244353;

int my_rand(int *seed) {
	*seed = *seed * 1103515245 + 12345;
	return ((unsigned)*seed) / 34;
}
void gen(int n, int Lim, int seed, int* arr) {
	int cur = 0;
	for(int i = 1; i <= n; i++) {
		int rd = my_rand(&seed);
		if(rd % std::min(10, cur + 1) == 0 && cur < Lim) arr[i] = ++cur;
		else arr[i] = (my_rand(&seed) % cur) + 1;
	}
}

int n, lim, seed;
int a[N];

int cnt[N], ans[N];

int main() {
	scanf("%d%d%d", &n, &lim, &seed);
	gen(n, lim, seed, a);
	// printf("  a: "); for(int i = 1; i <= n; i++) printf("%d ", a[i]); puts("");
	for(int i = n; i >= 1; i--) ans[i] += cnt[a[i] + 1], cnt[a[i] + 1] = 0, cnt[a[i]] += ans[i] + 1;
	// printf("ans: "); for(int i = 1; i <= n; i++) printf("%d ", ans[i]); puts("");
	for(int i = 0; i <= n + 1; i++) cnt[i] = 0;
	for(int i = 1; i <= n; i++) ans[i] += cnt[a[i]], cnt[a[i]] = ans[i] + 1;
	// printf("ans: "); for(int i = 1; i <= n; i++) printf("%d ", ans[i]); puts("");
	for(int i = 1; i <= n; i++) ans[i] = n - ans[i];
	// printf("ans: "); for(int i = 1; i <= n; i++) printf("%d ", ans[i]); puts("");
	LL out = 0, power = 1;
	for(int i = 1; i <= n; i++) (out += power * ans[i]) %= MOD, power = power * 233 % MOD;
	printf("%lld\n", out);
	return 0;
}