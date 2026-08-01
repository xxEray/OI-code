#include <bits/stdc++.h>

const int N = 7;

int rand(int l, int r) { return rand() % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int T = 5;
	printf("%d\n", T);
	while(T--) {
		int n = rand(2, N), m = rand(0, n * (n - 1) / 2);
		printf("%d %d\n", n, m);
		std::set<std::pair<int, int>> st;
		for(int i = 1; i <= m; i++) {
			int u, v;
			do {
				u = rand(1, n), v = rand(1, n);
			} while(u == v || st.count({u, v}));
			st.insert({u, v}), st.insert({v, u});
			printf("%d %d\n", u, v);
		}
	}
	return 0;
}
