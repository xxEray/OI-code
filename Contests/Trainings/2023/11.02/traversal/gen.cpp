#include <bits/stdc++.h>

const int N = 1000;

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	freopen("../traversal.in", "w", stdout);
	int n = 6;
	int T = 3 * n - 1;
	printf("%d\n", T);
	for(int i = 1; i <= 3; i++) for(int j = 1; j <= n; j++) if(i != 1 || j != 1) printf("%d %d %d\n", n, i, j);
	return 0;
}