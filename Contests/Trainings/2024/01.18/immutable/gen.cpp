#include <bits/stdc++.h>

int rand(int l, int r) { return ((long long)rand() << 30 | rand() << 15 | rand()) % (r - l + 1) + l; }

const int N = 5;
const int V = 10;

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	// freopen("immutable.in", "w", stdout);
	int n = N;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) printf("%d ", rand(1, V));
	return 0;
}