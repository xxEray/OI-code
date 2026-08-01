#include <bits/stdc++.h>

typedef long long LL;

int n;
LL K;

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }
LL lcm(LL x, LL y) { return x / gcd(x, y) * y; }

int main() {
	scanf("%d%lld", &n, &K);
	LL l = 1;
	for(int i = 1; i <= n; i++) {
		LL x;
		scanf("%lld", &x);
		l = gcd(lcm(l, x), K);
	}
	puts(l == K ? "Yes" : "No");
	return 0;
}