#include <bits/stdc++.h>

const int N = 1000;
const int MAXQ = 2e6;
const int P = 223092870;

int main() {
	freopen("tsuki.in", "w", stdout);
	srand(1231);
	int n = N, m = N, Q = MAXQ;
	printf("%d %d %d\n", n, m, P);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) printf("%d ", rand() << 15 | rand());
		puts("");
	}
	printf("%d\n", Q);
	while(Q--) {
		int xl = (rand() << 15 | rand()) % n, yl = (rand() << 15 | rand()) % n, xr = (rand() << 15 | rand()) % n, yr = (rand() << 15 | rand()) % n;
		if(xl > xr) std::swap(xl, xr);
		if(yl > yr) std::swap(yl, yr);
		printf("%d %d %d %d\n", xl, yl, xr, yr);
	}
	return 0;
}