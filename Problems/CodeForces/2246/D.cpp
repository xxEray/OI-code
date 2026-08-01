#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
int a[N];

int value(int x) { return 32 - __builtin_clz(x) + __builtin_popcount(x) - 1; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		LL ans = LLINF;
		for(int k = 0; k <= 20; k++) {
			int base = (1 << k) - 1;
			LL ret = 0;
			for(int i = 1; i <= n; i++) {
				int x = a[i];
				ret += (-x) & base, x += (-x) & base;
				LL val = LLINF;
				for(int j = 0; j * (1LL << k) <= val; j++)
					val = std::min(val, j * (1LL << k) + value((x >> k) + j));
				// printf("i = %d, val = %d\n", i, val);
				ret += val;
			}
			// printf("k = %d: %d + %d\n", k, ret, k);
			ans = std::min(ans, ret + k);
		}
		printf("%lld\n", ans);
	}
	return 0;
}