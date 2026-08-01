#include <bits/stdc++.h>

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

const int N = 5000;

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	// freopen("air.in", "w", stdout);
	int n = N;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) printf("%d ", rand(1, 5));
	puts("");
	for(int i = 2; i <= n; i++) printf("%d %d\n", rand(1, i - 1), i);
	return 0;
}