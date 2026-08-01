#include <bits/stdc++.h>

const int MOD = 998244353;

int n;

int main() {
#ifndef DEBUG
	freopen("cycle.in", "r", stdin);
	freopen("cycle.out", "w", stdout);
#endif
	scanf("%d", &n);
	int prod = 1;
	for(int i = 1; i <= n; i++) {
		prod += prod;
		if(prod >= MOD) prod -= MOD;
	}
	printf("%d\n", prod);
	return 0;
}
