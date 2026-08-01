#include <bits/stdc++.h>

const int N = 5000;

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	freopen("../ex_transport4.in", "w", stdout);
	int T = 5;
	printf("%d\n", T);
	while(T--) {
		int n = rand(N / 2, N);
		printf("%d\n", n);
		for(int i = 1; i <= n; i++) printf("%d ", rand(1, 5000));
		puts("");
		for(int i = 2; i <= n; i++) printf("%d %d %d\n", rand(1, i - 1), i, rand(1, 10000));
	}
	return 0;
}