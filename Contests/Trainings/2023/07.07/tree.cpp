#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

int n;
LL m;
int a[N];

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	scanf("%d%lld", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	LL ans = 1, sum = 0;
	for(int i = 1; i <= n; i++) (ans *= a[i]) %= m, (sum += a[i] - 1) %= m;
	for(int i = 0; i < n - 2; i++) (ans *= (sum - i + m) % m) %= m;
	printf("%lld\n", ans);
	return 0;
}
