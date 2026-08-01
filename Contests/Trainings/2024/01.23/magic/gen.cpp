#include <bits/stdc++.h>

int rand(int l, int r) { return ((long long)rand() << 30 | rand() << 15 | rand()) % (r - l + 1) + l; }

const int N = 5000;

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	// freopen("magic.in", "w", stdout);
	int n = rand(1, N), K = rand(1, n);
	printf("%d %d\n", n, K);
	return 0;
}