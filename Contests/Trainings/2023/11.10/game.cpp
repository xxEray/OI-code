#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n;
int a[N], b[N];

int main() {
#ifndef DEBUG
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
		long long ans = 0;
		for(int i = 1; i <= n; i++) ans += std::abs(a[i] - b[i]);
		printf("%lld\n", ans);
	}
	return 0;
}
