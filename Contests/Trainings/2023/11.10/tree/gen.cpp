#include <bits/stdc++.h>

const int N = 10;

int rand(int l, int r) { return rand() % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	// freopen("../tree.in", "w", stdout);
	int n = N;
	printf("%d\n", n);
	for(int i = 2; i <= n; i++) printf("%d %d\n", rand(1, i - 1), i);
	return 0;
}
