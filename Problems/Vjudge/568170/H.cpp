#include <bits/stdc++.h>

int n, K;

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

int main() {
	scanf("%d%d", &n, &K);
	int g = 0;
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); g = gcd(g, x % K); }
	g = gcd(g, K);
	printf("%d\n", K / g);
	for(int i = 0; i < K / g; i++) printf("%d ", i * g);
	puts("");
	return 0;
}