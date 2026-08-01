#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;

int n;
int a[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	LL ans = 0;
	for(int i = 1; i <= n; i++) ans += std::abs(a[i] - i);
	printf("%lld\n", ans / 2);
	return 0;
}