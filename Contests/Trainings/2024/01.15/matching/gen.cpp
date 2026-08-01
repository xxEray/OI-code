#include <bits/stdc++.h>

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

const int N = 8;

int e[N + 5][N + 5];

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int T = 3;
	printf("%d\n", T);
	while(T--) {
		int n = N, m = 0;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) e[i][j] = rand(-1, 1), m += (e[i][j] != -1);
		printf("%d %d\n", n, m);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(e[i][j] != -1) printf("%d %d %d\n", i, j + n, e[i][j]);
	}
	return 0;
}