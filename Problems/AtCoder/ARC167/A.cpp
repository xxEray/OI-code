#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n, m;
int a[N], b[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= n - m; i++) b[i] += a[i];
	for(int i = n - m + 1; i <= 2 * (n - m); i++) b[(n - m) - (i - (n - m)) + 1] += a[i];
	for(int i = 2 * (n - m) + 1; i <= n; i++) b[i - (n - m)] += a[i];
	// printf("b: "); for(int i = 1; i <= n; i++) printf("%d ", b[i]); puts("");
	LL ans = 0;
	for(int i = 1; i <= m; i++) ans += (LL)b[i] * b[i];
	printf("%lld\n", ans);
	return 0;
}