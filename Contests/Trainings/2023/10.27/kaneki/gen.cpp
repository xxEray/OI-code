#include <bits/stdc++.h>

const int N = 10;
const int V = 1e9 + 6;

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	// freopen("../kaneki.in", "w", stdout);
	int n = N, m = N;
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i++) printf("%d ", rand(0, V));
	puts("");
	for(int i = 1; i <= m; i++) {
		int type = rand(1, 4);
		int l = rand(1, n), r = rand(1, n);
		if(l > r) std::swap(l, r);
		if(type == 1 || type == 2) printf("%d %d %d %d\n", type, l, r, rand(0, V));
		else if(type == 3) printf("%d %d %d %d\n", type, l, r, rand(1, 10));
		else printf("%d %d %d\n", type, l, r);
	}
	return 0;
}