#include <bits/stdc++.h>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m, Q;
int a[N], b[N];

int main() {
#ifndef DEBUG
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
	int mna = *std::min_element(a + 1, a + n + 1), mnb = *std::min_element(b + 1, b + m + 1);
	while(Q--) {
		int sx, sy, tx, ty;
		scanf("%d%d%d%d", &sx, &sy, &tx, &ty);
		int ans = INF;
		if(sx == tx) ans = std::min(ans, a[sx]);
		if(sy == ty) ans = std::min(ans, b[sy]);
		ans = std::min(ans, std::max(a[sx], b[ty]));
		ans = std::min(ans, std::max(a[tx], b[sy]));
		ans = std::min(ans, std::max({a[sx], a[tx], mnb}));
		ans = std::min(ans, std::max({b[sy], b[ty], mna}));
		printf("%d\n", ans);
	}
	return 0;
}