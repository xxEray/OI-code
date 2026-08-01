#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n;
LL a[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	LL sum = 0, mx = 0;
	for(int i = 1; i <= n; i++) mx = std::max(mx, a[i]), a[i] += a[i - 1], sum += a[i], printf("%lld\n", sum + mx * i);
	return 0;
}