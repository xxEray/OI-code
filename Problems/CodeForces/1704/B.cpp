#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL a[N];
int n; LL m;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%lld", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		LL mn = LLINF, mx = -LLINF;
		LL ans = 0;
		for(int i = 1; i <= n; i++) {
			mn = std::min(mn, a[i]), mx = std::max(mx, a[i]);
			if(mx - mn > 2 * m) mn = mx = a[i], ans++;
		}
		printf("%lld\n", ans);
	}
	return 0;
}