#include <bits/stdc++.h>

const int N = 2;
const int V = 3;

int rand(int l, int r) { return ((long long)rand() << 30 | rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = N, K = rand(0, n);
	printf("%d %d\n", n, K);
	for(int i = 1; i <= n; i++) printf("%d ", rand(-V, V));
	puts("");
	for(int i = 1; i <= n; i++) printf("%d ", rand(-V, V));
	puts("");
	return 0;
}
