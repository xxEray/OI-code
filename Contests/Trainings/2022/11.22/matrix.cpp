#include <cstdio>
#include <algorithm>

typedef long long LL;

LL n, K;

// int ans[8][8] = {
// 	{0},
// 	{0, 0},
// 	{0, 0, 1},
// 	{0, 0, 2, 3},
// 	{0, 0, 4, 5, 6},
// 	{0, 0, 6, 8, 9, 10},
// 	{0, 0, 9, 12, 13, 14, 15},
// 	{0, 0, 12, 16, 18, 19, 20, 21}
// };

LL sum(LL a1, LL an, LL d) {
	LL n_ = (an - a1) / d + 1;
	return (a1 + an) * n_ / 2;
}

int main() {
	scanf("%lld%lld", &n, &K);
	if(K > n) K = n;
	LL ans = 0;
	LL x = n / K, y = (n + K - 1) / K, c = n - K * x;
	ans = sum(n - y * c, n - y, y) * y + sum(0, n - y * c - x, x) * x;
	printf("%lld\n", ans);
	return 0;
}
