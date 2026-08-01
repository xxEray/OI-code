#include <bits/stdc++.h>

int rand(int l, int r) { return rand() % (r - l + 1) + l; }

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = 2e5, m = 2e5, Q = 2e5;
	printf("%d %d %d\n", n, m, Q);
	while(Q--) {
		int lx = rand(1, n), rx = rand(1, n), ly = rand(1, m), ry = rand(1, m);
		if(lx > rx) std::swap(lx, rx);
		if(ly > ry) std::swap(ly, ry);
		printf("%d %d %d %d\n", lx, rx, ly, ry);
	}
	return 0;
}