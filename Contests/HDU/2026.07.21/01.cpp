#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
LL a[N], b[N];

LL x, y;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld%d%d", &x, &y, &n, &m);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for(int i = 1; i <= m; i++) scanf("%lld", &b[i]);
		LL mna = *std::min_element(a + 1, a + n + 1);
		LL mxa = *std::max_element(a + 1, a + n + 1);
		LL mnb = *std::min_element(b + 1, b + m + 1);
		LL mxb = *std::max_element(b + 1, b + m + 1);
		if(n == 0) mna = mxa = 0;
		if(m == 0) mnb = mxb = 0;
		LL xs[] = {x + mna, x, x + mxa}, ys[] = {y + mnb, y, y + mxb};
		LL ans = -LLINF;
		for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) ans = std::max(ans, xs[i] * ys[j]);
		printf("%lld\n", ans);
	}
	return 0;
}