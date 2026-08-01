#include <bits/stdc++.h>

const int N = 1e3;
const int M = 1e3;
const int V = 1e9;

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = rand(1, N), m = rand(1, M);
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) printf("%d ", rand(1, V));
		puts("");
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) printf("%d ", rand(1, V));
		puts("");
	}
	return 0;
}