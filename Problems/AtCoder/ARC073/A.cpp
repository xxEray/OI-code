#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, T;
int a[N];

int main() {
	scanf("%d%d", &n, &T);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = n; i >= 2; i--) a[i] -= a[i - 1];
	long long ans = 0;
	for(int i = 2; i <= n; i++) ans += std::min(T, a[i]);
	ans += T;
	printf("%lld\n", ans);
	return 0;
}