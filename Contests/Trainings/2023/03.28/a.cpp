#include <bits/stdc++.h>

long long a[100];

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), assert(std::abs(a[i]) <= 2000000000);
	return 0;
}