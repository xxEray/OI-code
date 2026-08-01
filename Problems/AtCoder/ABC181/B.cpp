#include <cstdio>

typedef long long LL;

int main() {
	int n;
	LL ans = 0;
	std::scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int l, r;
		std::scanf("%d%d", &l, &r);
		ans += (LL)(l + r) * (r - l + 1) / 2;
	}
	std::printf("%lld\n", ans);
	return 0;
}