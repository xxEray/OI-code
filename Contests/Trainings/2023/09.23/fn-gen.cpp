#include <bits/stdc++.h>

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main() {
	freopen("fn.in", "w", stdout);
	srand(time(0));
	int n = 2000, m = 1000000;
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i++) printf("%d ", rand(1, m));
	puts("");
	for(int i = 2; i <= n; i++) printf("%d %d\n", rand(1, i - 1), i);
	return 0;
}