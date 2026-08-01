#include <bits/stdc++.h>

const int N = 5;
const int V = 5;

int rand(int l, int r) { return rand() % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = rand(1, N), m = rand(1, N);
	printf("1 %d %d 0\n", n, m);
	while(n--) printf("%d ", rand(0, V));
	puts("");
	while(m--) printf("%d ", rand(0, V));
	puts("");
	return 0;
}