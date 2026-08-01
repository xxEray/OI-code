#include <bits/stdc++.h>

int rand(int l, int r) { return rand() % (r - l + 1) + l; }

const int N = 5000;

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	// freopen("lamp.in", "w", stdout);
	int n = N;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) printf("%d ", rand(0, n));
	puts("");
	return 0;
}
