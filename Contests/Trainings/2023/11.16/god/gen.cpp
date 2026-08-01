#include <bits/stdc++.h>

int rand(int l, int r) { return rand() % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = std::min({rand(2, 25), rand(2, 25), rand(2, 25)}), m = rand(0, 25 / n);
	printf("%d %d\n", n, m);
	return 0;
}
