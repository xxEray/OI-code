#include <bits/stdc++.h>

typedef long long LL;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		LL n;
		scanf("%lld", &n);
		int mx = 0;
		for(int i = 2; i <= 1000000; i++) if(n % i == 0) {
			int cnt = 0;
			while(n % i == 0) n /= i, cnt++;
			mx = std::max(mx, cnt);
		}
		if(n > 1) {
			mx = std::max(mx, 1);
			LL sq = roundl(sqrtl(n));
			bool flag = false;
			for(LL i = std::max(sq - 1000, 1LL); i <= std::min(sq + 1000, 1000000000LL); i++)
				flag |= (i * i == n);
			if(flag) mx = std::max(mx, 2);
		}
		int ans = 0;
		while(mx) ans++, mx /= 2;
		printf("%d\n", ans);
	}
	return 0;
}