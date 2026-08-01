#include <bits/stdc++.h>

typedef long long LL;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		LL n;
		scanf("%lld", &n);
		LL l = 1, r = 1e9 + 1;
		while(l < r) {
			LL mid = (l + r) / 2;
			if(mid * mid <= n) l = mid + 1;
			else r = mid;
		}
		LL x = l - 1;
		// printf("x = %lld\n", x);
		if(x * x == n) printf("%lld\n", 2 * n - (x + x));
		else if(x * (x + 1) >= n) printf("%lld\n", 2 * n - (x + x + 1));
		else printf("%lld\n", 2 * n - (x + 1 + x + 1));
	}
	return 0;
}