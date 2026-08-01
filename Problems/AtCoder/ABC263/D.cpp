#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
LL p, q;
LL a[N];

LL presum[N], l[N], r[N];

int main() {
	scanf("%d%lld%lld", &n, &p, &q);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) presum[i] = presum[i - 1] + a[i];
	l[0] = r[n + 1] = 0;
	for(int i = 1; i <= n; i++) l[i] = std::min(l[i - 1], i * p - presum[i]);
	for(int i = n; i >= 1; i--) r[i] = std::min(r[i + 1], (n - i + 1) * q - (presum[n] - presum[i - 1]));
	LL ans = LLINF;
	for(int i = 0; i <= n; i++) ans = std::min(ans, l[i] + r[i + 1]);
	printf("%lld\n", ans + presum[n]);
	return 0;
}