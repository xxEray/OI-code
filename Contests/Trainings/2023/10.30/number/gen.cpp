#include <bits/stdc++.h>

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

const int lim[] = {0, 0, 20, 190, 1140, 4845, 15503, 38741, 77366, 125250, 165740, 179892, 160042, 116140, 68091, 31754, 11500, 3116, 594, 71, 4};

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int T = 10;
	printf("%d\n", T);
	while(T--) {
		int K = rand(2, 20);
		printf("%d %d\n", rand(1, lim[K] - 1), K);
	}
	return 0;
}