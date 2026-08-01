// Wrong

#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e4 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
struct Node { int a, b; } a[N];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d %d", &a[i].a, &a[i].b);
		std::sort(a + 1, a + n + 1, [](const Node &x, const Node &y) { return x.b > y.b; });
		LL sumb = 0;
		for (int i = 1; i <= n; i++) sumb += a[i].b;
		LL ans = -LLINF, nowa = 0, nowb = 0;
		for(int i = 1; i <= n; i++) {
			nowa += a[i].a, nowb += a[i].b;
			ans = std::max(ans, nowa + sumb - nowb + a[i].b);
		}
		printf("%lld\n", ans);
	}
	return 0;
}