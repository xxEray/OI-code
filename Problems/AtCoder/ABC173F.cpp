#include <cstdio>
#include <algorithm>

typedef long long LL;

int n;

LL ans = 0;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) ans += (LL)(i - 1 + 1) * (n - i + 1);
	for(int i = 1; i < n; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		if(l > r) std::swap(l, r);
		ans -= (LL)(l - 1 + 1) * (n - r + 1);
	}
	printf("%lld\n", ans);
	return 0;
}