#include <bits/stdc++.h>

const int N = 5e4 + 5;

int n, D;

int main() {
	scanf("%d%d", &n, &D);
	if((long long)n * (n - 1) / 2 < n * D) { puts("No"); return 0; }
	puts("Yes");
	for(int i = 1; i <= n; i++) for(int j = i + 1, k = 1; k <= D; j++, k++) {
		if(j == n + 1) j = 1;
		printf("%d %d\n", i, j);
	}
	return 0;
}