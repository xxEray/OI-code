#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;

int n, m, K, Q;
LL a[N][N];

int main() {
	scanf("%d%d", &n, &m);
	scanf("%d", &K);
	while(K--) {
		int x, y; LL a_, b;
		scanf("%d%d%lld%lld", &x, &y, &a_, &b);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
			a[i][j] += std::max(0LL, a_ - b * std::max(std::abs(i - x), std::abs(j - y)));
	}
	LL ans = 0;
	scanf("%d", &Q);
	while(Q--) {
		int xl, yl, xr, yr;
		scanf("%d%d%d%d", &xl, &yl, &xr, &yr);
		LL sum = 0;
		for(int i = xl; i <= xr; i++) for(int j = yl; j <= yr; j++) sum += a[i][j];
		// LL cnt = (xr - xl + 1) * (yr - yl + 1);
		// printf("sum = %lld\n", sum);
		ans ^= sum;
	}
	printf("%lld\n", ans);
	return 0;
}
