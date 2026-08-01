#include <bits/stdc++.h>

const int N = 1e3;

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = rand(1, N);
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) putchar(rand(0, 1) ? 'L' : 'R');
	puts("");
	return 0;
}
