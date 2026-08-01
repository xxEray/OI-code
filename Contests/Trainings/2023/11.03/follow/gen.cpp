#include <bits/stdc++.h>

const int N = 100000;

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = N;
	printf("%d %d\n", n, n);
	for(int i = 1; i <= n; i++) printf("%d ", rand(1, n));
	puts("");
	for(int i = 1; i <= n; i++) printf("%d ", i);
	puts("");
	return 0;
}