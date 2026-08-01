#include <cstdio>
#include <algorithm>

typedef long long LL;

const long long LLINF = 0x3f3f3f3f3f3f3f3f;

void chkmin(LL &x, LL y) { x > y && (x = y); }
void chkmax(LL &x, LL y) { x < y && (x = y); }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		LL n, H, W;
		scanf("%lld%lld", &W, &H);
		LL mn1 = LLINF, mx1 = -LLINF, mn2 = LLINF, mx2 = -LLINF, mn3 = LLINF, mx3 = -LLINF, mn4 = LLINF, mx4 = -LLINF;
		scanf("%lld", &n); for(int i = 1; i <= n; i++) { LL x; scanf("%lld", &x); chkmin(mn1, x), chkmax(mx1, x); }
		scanf("%lld", &n); for(int i = 1; i <= n; i++) { LL x; scanf("%lld", &x); chkmin(mn2, x), chkmax(mx2, x); }
		scanf("%lld", &n); for(int i = 1; i <= n; i++) { LL x; scanf("%lld", &x); chkmin(mn3, x), chkmax(mx3, x); }
		scanf("%lld", &n); for(int i = 1; i <= n; i++) { LL x; scanf("%lld", &x); chkmin(mn4, x), chkmax(mx4, x); }
		LL v1 = (mx1 - mn1) * H, v2 = (mx2 - mn2) * H, v3 = (mx3 - mn3) * W, v4 = (mx4 - mn4) * W;
		LL maxv = std::max({v1, v2, v3, v4});
		printf("%lld\n", maxv);
	}
	return 0;
}