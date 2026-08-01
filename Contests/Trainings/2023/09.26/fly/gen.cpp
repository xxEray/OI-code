#include <bits/stdc++.h>

const int N = 10;
const int M = 45;
const int V = 1e8;

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

std::vector<std::pair<int, int>> edges;

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = rand(2, N), m = std::min(rand(n - 1, n * (n - 1) / 2)/* n - 1 */, M);
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i++) printf("%d ", i == 1 || i == n ? 0 : rand(1, V));
	for(int i = 2; i <= n; i++) edges.push_back({rand(1, i - 1), i});
	for(int i = n; i <= m; i++) {
		int u = rand(1, n), v = rand(1, n);
		edges.push_back({u, v});
	}
	std::random_shuffle(edges.begin(), edges.end());
	for(int i = 0; i < m; i++) printf("%d %d\n", edges[i].first, edges[i].second);
	// for(int i = 2; i <= n; i++) printf("%d %d\n", i - 1, i);
	return 0;
}