#include <bits/stdc++.h>

const int N = 2e5;
const int V = 1e6;

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main() {
	freopen("award.in", "w", stdout);
	int n = N, Q = N;
	printf("%d\n", n);
	for(int i = 1; i <= n - 5; i++) printf("%d ", rand(0, 100));
	for(int i = n - 4; i <= n; i++) printf("%d ", rand(V - 10000, V));
	puts("");
	for(int i = 2; i <= n; i++) printf("%d %d\n", i - 1, i);
	printf("%d\n", Q);
	while(Q--) {
		int x = rand(n - 4, n);
		int v = rand(V - 10000, V);
		printf("%d %d\n", x, v);
	}
	return 0;
}