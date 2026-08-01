#include <bits/stdc++.h>

int rand(int l, int r) { return rand() % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	freopen("bridge.in", "w", stdout);
	int n = 5, c = rand(2, n);
	printf("%d %d\n", n, c);
	for(int i = 1; i <= n; i++) printf("%d ", rand(1, 20));
	puts("");
	return 0;
}