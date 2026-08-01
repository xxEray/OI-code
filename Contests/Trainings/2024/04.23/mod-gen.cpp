#include <bits/stdc++.h>

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main() {
	freopen("mod.in", "w", stdout);
	int n = 1e5, m = 1e5;
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i++) printf("%d ", rand(1, 100000));
	puts("");
	for(int i = 1; i <= m; i++) {
		// int l = rand(1, n), r = rand(1, n);
		// if(l > r) std::swap(l, r);
		printf("%d %d %d\n", 1, n, rand(1, 100000));
	}
	return 0;
}