#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
int a[N], b[N];

int c[N];

LL calc(int K) {
	int U = (1 << n) - 1;
	LL ans = LLINF;
	for(int s = 0; s <= U; s++) if(__builtin_popcount(s) == K) {
		for(int i = 1; i <= n; i++)
			if(s >> (i - 1) & 1) c[i] = a[i];
			else c[i] = b[i];
		LL sum = 0, mn = LLINF, ret = 0;
		for(int i = 0; i <= n; i++) {
			sum += c[i];
			mn = std::min(mn, sum);
			ret = std::max(ret, sum - mn);
		}
		ans = std::min(ans, ret);
	}
	return ans;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i])/* a[i] = rand() - (1 << 14) */;
	for(int i = 1; i <= n; i++) scanf("%d", &b[i])/* b[i] = rand() - (1 << 14) */;
	printf("a: "); for(int i = 1; i <= n; i++) printf("%d ", a[i]); puts("");
	printf("b: "); for(int i = 1; i <= n; i++) printf("%d ", b[i]); puts("");
	for(int K = 0; K <= n; K++) printf("%d: %lld\n", K, calc(K));
	return 0;
}