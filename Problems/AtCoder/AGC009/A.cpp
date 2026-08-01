#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n;
LL a[N], b[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &a[i], &b[i]);
	LL ans = 0;
	for(int i = n; i >= 1; i--) {
		if((a[i] + ans) % b[i] == 0) continue;
		ans += ((a[i] + ans) / b[i] + 1) * b[i] - (a[i] + ans);
	}
	printf("%lld\n", ans);
	return 0;
}