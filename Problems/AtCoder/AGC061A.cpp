#include <cstdio>
#include <algorithm>

typedef long long LL;

LL calc(LL x, LL y) {
	if(y == x + 1) return x + 1;
	LL a = x / 2, b = (y + 1) / 2 - 1;
	a = (1LL << 63) - a;
	return ((a & b) == 0) ? ((y - 1) ^ 1) + 1 : y;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		LL x, y;
		scanf("%lld%lld", &x, &y);
		if(x & 1) printf("%lld\n", y == 1 ? 2 : calc(x - 1, calc(x - 1, y - 1) + 1));
		else printf("%lld\n", calc(x, y));
	}
	return 0;
}