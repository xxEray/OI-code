#include <bits/stdc++.h>

const int N = 2e5 + 5;
const int MOD = 998244353;

int n, K;
int a[N];

int main() {
#ifndef DEBUG
	freopen("source.in", "r", stdin);
	freopen("source.out", "w", stdout);
#endif
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	long long ans = 1;
	for(int i = 1; i <= n; i++) {
		int cnt = 0;
		for(int j = 1; j < i; j++) cnt += (a[j] > a[i]);
		if(cnt == K) (ans *= n - i + 1) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
}
