#include <bits/stdc++.h>

const int N = 20;

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = rand(1, N), m = rand(1, n);
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i++) printf("%d ", rand(0, n));
	puts("");
	return 0;
}