#include <bits/stdc++.h>

const int N = 20000;
const int M = 5000;
const int V = 1e9;

int rand(int l, int r) { return ((long long)rand() << 30 | rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	freopen("../fireworks.in", "w", stdout);
	int n = N, m = N / n;
	printf("%d %d\n", n, m);
	int K = rand(1, std::min(n * m, M));
	printf("%d\n", K);
	while(K--) {
		int x = rand(1, n), y = rand(1, m);
		int a = rand(1, V), b = rand(1, 10);
		printf("%d %d %d %d\n", x, y, a, b);
	}
	int Q = rand(1, M);
	printf("%d\n", Q);
	while(Q--) {
		int lx = rand(1, n), rx = rand(1, n);
		if(lx > rx) std::swap(lx, rx);
		int ly = rand(1, m), ry = rand(1, m);
		if(ly > ry) std::swap(ly, ry);
		printf("%d %d %d %d\n", lx, ly, rx, ry);
	}
	return 0;
}
