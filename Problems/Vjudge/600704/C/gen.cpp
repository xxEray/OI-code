#include <bits/stdc++.h>

const int N = 1e5;
const int M = 2e5;
const int MAXQ = 1e5;
const int V = 1e5;

int rand(int l, int r) { return rand() % (r - l + 1) + l; }

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int T = 5;
	printf("%d\n", T);
	while(T--) {
		int n = N, m = M, Q = MAXQ;
		printf("%d %d %d\n", n, m, Q);
		for(int i = 1; i <= n; i++) printf("%d ", rand(1, (n + 9) / 10));
		puts("");
		for(int i = 1; i <= n; i++) printf("%d ", rand(1, V));
		puts("");
		std::vector<std::pair<int, int>> edges;
		std::set<std::pair<int, int>> st;
		for(int i = 2; i <= n; i++) {
			int u = rand(1, i - 1);
			st.emplace(u, i);
			edges.emplace_back(u, i);
		}
		for(int i = n; i <= m; i++) {
			int u, v;
			do {
				u = rand(1, n), v = rand(1, n);
				if(u > v) std::swap(u, v);
			} while(st.count({u, v}));
			st.emplace(u, v);
			edges.emplace_back(u, v);
		}
		std::random_shuffle(edges.begin(), edges.end());
		for(auto [u, v] : edges) {
			if(rand(0, 1)) std::swap(u, v);
			printf("%d %d %d\n", u, v, rand(1, V));
		}
		while(Q--) {
			int t = rand(0, 1), x = rand(1, n), y = rand(1, V);
			printf("%d %d %d\n", t, x, y);
		}
	}
	return 0;
}
