#include <bits/stdc++.h>

int rand(int l, int r) { return ((long long)rand() << 30 | rand() << 15 | rand()) % (r - l + 1) + l; }

const int N = 500;

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	// freopen("immutable.in", "w", stdout);
	int type = rand(1, 2), n, K;
	if(type == 1) n = rand(1, N), K = rand(0, n / 2), printf("1\n%d %d\n", n, K);
	else n = rand(1, N), printf("2\n%d\n", n);
	return 0;
}