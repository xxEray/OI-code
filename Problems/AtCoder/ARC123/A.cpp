#include <cstdio>
#include <algorithm>

int main() {
	long long a, b, c, ans = 0;
	scanf("%lld%lld%lld", &a, &b, &c);
	if(a > c) std::swap(a, c);
	if(b < a) ans += a - b, b = a;
	if(b - a < c - b) printf("%lld\n", ans + (c - 2 * b + a + 1) / 2 + (c - 2 * b + a) % 2);
	else printf("%lld\n", ans + 2 * b - a - c);
	return 0;
}