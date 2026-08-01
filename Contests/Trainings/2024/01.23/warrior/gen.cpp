#include <bits/stdc++.h>

typedef long long LL;

int rand(int l, int r) { return ((long long)rand() << 30 | rand() << 15 | rand()) % (r - l + 1) + l; }
int rand(LL l, LL r) { return ((LL)rand() << 45 | (LL)rand() << 30 | rand() << 15 | rand()) % (r - l + 1) + l; }

const int N = 5;

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	// freopen("warrior.in", "w", stdout);
	int n = rand(1, N);
	LL K = rand(1LL, (LL)n * (n + 1) / 2);
	printf("%d %lld\n", n, K);
	for(int i = 1; i <= n; i++) printf("%d ", rand(1, n));
	puts("");
	return 0;
}