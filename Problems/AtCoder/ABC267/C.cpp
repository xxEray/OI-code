#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL a[N];
int n, m;

LL s1[N], s2[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), s1[i] = s1[i - 1] + a[i], s2[i] = s2[i - 1] + i * a[i];
	LL ans = -LLINF;
	for(int i = 1; i <= n - m + 1; i++) ans = std::max(ans, (s2[i + m - 1] - s2[i - 1]) - (i - 1) * (s1[i + m - 1] - s1[i - 1]));
	printf("%lld\n", ans);
	return 0;
}