#include <bits/stdc++.h>

int rand(int l, int r) { return ((long long)rand() << 30 | rand() << 15 | rand()) % (r - l + 1) + l; }

const int N = 1e5;
const int V = 1e9;

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	freopen("top.in", "w", stdout);
	int n = N, E = rand(0, V);
	printf("%d %d\n", n, E);
	for(int i = 1; i <= n; i++) printf("%d ", rand(0, V));
	puts("");
	for(int i = 1; i <= n; i++) printf("%d ", rand(0, V));
	puts("");
	return 0;
}