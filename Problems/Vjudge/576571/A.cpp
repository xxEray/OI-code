#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, K;
int a[N];

LL pre[N], ppre[N];
LL sum(int l, int r) { return pre[r] - pre[l - 1]; }
LL psum(int l, int r) { return ppre[r] - ppre[l - 1]; }

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i], ppre[i] = ppre[i - 1] + std::max(a[i], 0);
	LL ans = -LLINF;
	for(int i = 1; i <= n - K + 1; i++) ans = std::max(ans, psum(1, i - 1) + psum(i + K, n) + std::max(sum(i, i + K - 1), 0LL));
	printf("%lld\n", ans);
	return 0;
}