#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n1, n2, n3;
int a[N], b[N], c[N];

std::set<std::pair<int, int>> ac, ab, bc;

int main() {
	scanf("%d%d%d", &n1, &n2, &n3);
	for(int i = 1; i <= n1 + n2 + n3; i++) scanf("%d%d%d", &a[i], &b[i], &c[i]);
	auto solve = [&]() {
		ab.clear(), bc.clear(), ac.clear();
		LL ans = 0;
		for(int i = 1; i <= n1 + n2 + n3; i++) ans += a[i], ab.emplace(b[i] - a[i], i);
		for(int _ = 1; _ <= n2; _++) {
			int i = ab.rbegin()->second;
			ab.erase(--ab.end());
			ans += b[i] - a[i];
			bc.emplace(c[i] - b[i], i);
			// printf("%d: a -> b\n", i);
		}
		for(auto [_, i] : ab) ac.emplace(c[i] - a[i], i);
		for(int _ = 1; _ <= n3; _++) {
			if(!bc.empty() && ab.rbegin()->first + bc.rbegin()->first >= ac.rbegin()->first) {
				int i = ab.rbegin()->second;
				ab.erase(--ab.end()), ac.erase({c[i] - a[i], i});
				ans += b[i] - a[i];
				bc.emplace(c[i] - b[i], i);
				// printf("%d: a -> b\n", i);
				i = bc.rbegin()->second;
				bc.erase(--bc.end());
				ans += c[i] - b[i];
				// printf("%d: b -> c\n", i);
			} else {
				int i = ac.rbegin()->second;
				ac.erase(--ac.end()), ab.erase({b[i] - a[i], i});
				ans += c[i] - a[i];
				// printf("%d: a -> c\n", i);
			}
		}
		// printf("ans = %lld\n", ans);
		return ans;
	};
	LL out = solve();
	std::swap(n2, n3);
	for(int i = 1; i <= n1 + n2 + n3; i++) std::swap(b[i], c[i]);
	out = std::max(out, solve());
	printf("%lld\n", out);
	return 0;
}