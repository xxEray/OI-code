#include <bits/stdc++.h>

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n, k, x;
		scanf("%d%d%d", &n, &k, &x);
		if(n < k || x < k - 1) { puts("-1"); continue; }
		printf("%d\n", (k - 1) * k / 2 + (n - k) * (x == k ? k - 1 : x));
	}
	return 0;
}