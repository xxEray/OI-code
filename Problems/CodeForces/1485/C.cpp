#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long long LL;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		LL x, y;
		scanf("%lld%lld", &x, &y);
		LL sqx = sqrt(x) + 1;
		LL ans = 0;
		for(int i = 1; i <= sqx; i++)
			ans += std::max(std::min(x / i - 1, y) - (i + 1) + 1, 0LL);
		printf("%lld\n", ans);
	}
	return 0;
} /*

*/