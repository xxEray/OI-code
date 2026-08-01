#include <bits/stdc++.h>

int rand(int l, int r) { return ((long long)rand() << 30 | rand() << 15 | rand()) % (r - l + 1) + l; }

const int N = 5000;
const int V = 1e9;

int a[N + 5];

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	// freopen("triangle.in", "w", stdout);
	int n = rand(1, N), Q = N;
	printf("%d %d\n", n, Q);
	for(int i = 1; i <= n; i++) printf("%d ", a[i] = rand(0, V));
	puts("");
	while(Q--) {
		int i = rand(1, n);
		int v = rand(-a[i], V);
		a[i] += v;
		printf("%d %d\n", i, v);
	}
	return 0;
}