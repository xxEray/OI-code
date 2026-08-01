#include <bits/stdc++.h>

const int N = 30;

int rand(int l, int r) { return rand() % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	// freopen("../tree.in", "w", stdout);
	int n = N, m = N, Q = N;
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) putchar(rand((i == 1), 3) ? '.' : 'X');
		putchar('\n');
	}
	printf("%d\n", Q);
	for(int i = 1; i <= Q; i++) printf("%d\n", rand(1, m));
	return 0;
}
