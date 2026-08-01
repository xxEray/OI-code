#include <bits/stdc++.h>

const int N = 600 + 5;

int n;

int main() {
#ifndef DEBUG
	freopen("home.in", "r", stdin);
	freopen("home.out", "w", stdout);
#endif
	scanf("%d", &n);
	int sum = ((n & 1) ? (n - 1) / 2 * 3 + 1 : n / 2 * 3);
	std::vector<std::array<int, 3>> ans;
	for(int i = 0; i <= std::min(n, sum); i++)
		for(int j = 0; j <= std::min(n, sum - i); j++)
			if(sum - i - j <= n) ans.push_back({i, j, sum - i - j});
	printf("%d\n", (int)ans.size());
	for(auto &p : ans) printf("%d %d %d\n", p[0], p[1], p[2]);
	return 0;
}