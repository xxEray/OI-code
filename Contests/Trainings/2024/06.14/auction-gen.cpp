#include <bits/stdc++.h>

int rand(int l, int r) { return rand() % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	freopen("auction.in", "w", stdout);
	int n = 10, Q = 10;
	printf("%d %d\n", n, Q);
	for(int i = 1; i <= n; i++) printf("%d", rand(0, 1));
	puts("");
	for(int i = 1; i <= Q; i++) printf("%d\n", i);
	return 0;
}