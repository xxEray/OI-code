#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 1e5 + 5;

std::pair<int, int> a[N];
int n, m;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d%d", &a[i].second, &a[i].first);
	std::sort(a + 1, a + m + 1);
	long long ans = 0;
	int now = n;
	for(int i = 1; i <= m; i++) {
		ans += (long long)a[i].first * (now - gcd(a[i].second, now));
		now = gcd(a[i].second, now);
	}
	if(now > 1) puts("-1");
	else printf("%lld\n", ans);
	return 0;
}