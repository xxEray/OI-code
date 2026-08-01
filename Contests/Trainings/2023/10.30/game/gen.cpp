#include <bits/stdc++.h>

const int N = 1000;

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	printf("%d\n", rand(1, N));
	return 0;
}