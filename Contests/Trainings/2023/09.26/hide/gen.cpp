#include <bits/stdc++.h>

const int N = 2000;
const int M = 2000;
const int MAXQ = 2000;

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = rand(1, N), m = rand(1, M), Q = rand(1, MAXQ);
	printf("%d %d %d\n", n, m, Q);
	for(int i = 1; i <= m; i++) {
		int l = rand(1, n), r = rand(1, n);
		if(l > r) std::swap(l, r);
		printf("%d %d\n", l, r);
	}
	for(int i = 1; i <= Q; i++) {
		int l = rand(1, n), r = rand(1, n);
		if(l > r) std::swap(l, r);
		printf("%d %d\n", l, r);
	}
	return 0;
}