#include <bits/stdc++.h>

const int N = 10;
const int M = 8;
const int PROD = 1e8;
static_assert(N * M <= PROD);

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = rand(1, N);
	int m = rand(1, M);
	printf("%d %d\n", n, m);
	return 0;
}