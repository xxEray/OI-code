#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

int n;
LL m;
LL a[N];

int main() {
#ifndef DEBUG
	freopen("router.in", "r", stdin);
	freopen("router.out", "w", stdout);
#endif
	scanf("%d%lld", &n, &m);
	LL sum = 0, mx = 0;
	for(int i = 1; i < n; i++) scanf("%lld", &a[i]), sum += a[i], mx = std::max(mx, a[i]);
	printf("%lld\n", sum + mx * (m - 1));
	return 0;
}