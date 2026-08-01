#include <bits/stdc++.h>

const int N = 5000;

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int T = 10;
	printf("%d\n", T);
	while(T--) {
		int n = rand(1, N);
		printf("%d\n", n);
	}
	return 0;
}