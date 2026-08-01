#include <bits/stdc++.h>

const int N = 6000;

int rand(int l, int r) { return ((long long)rand() << 30 | rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	// freopen("exchange.in", "w", stdout);
	int n = N, K = rand(0, std::min(n, 100));
	printf("%d %d\n", n, K);
	for(int i = 1; i <= n; i++) printf("%d ", rand(-1e9, 1e9));
	return 0;
}