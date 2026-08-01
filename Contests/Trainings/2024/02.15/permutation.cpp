#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

int p[20];

int main() {
#ifndef DEBUG
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		std::vector<std::pair<int, int>> vct;
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); vct.emplace_back(u, v); }
		for(int i = 1; i <= n; i++) p[i] = i;
		int ans = INF;
		do {
			int sum = 0;
			for(auto [i, j] : vct) sum += std::abs(p[i] - p[j]);
			ans = std::min(ans, sum);
		} while(std::next_permutation(p + 1, p + n + 1));
		printf("%d\n", ans);
	}
	return 0;
} /*
1
5
1 2
1 3
2 4
2 5
*/