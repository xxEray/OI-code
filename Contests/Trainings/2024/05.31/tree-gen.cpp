#include <bits/stdc++.h>

int rand(int l, int r) { return rand() % (r - l + 1) + l; }

const int V = 20;

int main(int argc, char *argv[]) {
	int sd; sscanf(argc == 1 ? "123" : argv[1], "%d", &sd); srand(sd);
	freopen("tree.in", "w", stdout);
	int n = 7, Q = 20;
	printf("%d %d\n", n, Q);
	for(int i = 1; i <= n; i++) printf("%d ", rand(1, V));
	puts("");
	for(int i = 2; i <= n; i++) printf("%d ", rand(1, i - 1));
	puts("");
	while(Q--) {
		int t = rand(1, 2), u = rand(1, n);
		printf("%d %d\n", t, u);
	}
	return 0;
}