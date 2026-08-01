#include <bits/stdc++.h>

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

const int N = 20;

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	// freopen("air.in", "w", stdout);
	int n = N, K = rand(2, 4);
	printf("%d %d\n", n, K);
	for(int i = 1; i <= n; i++) putchar(rand(0, 1) ? '(' : ')');
	puts("");
	return 0;
}