#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n;
int a[N], b[N];

struct BIT {
	int t[N * 2];
	void init() { for(int i = 1; i <= 2 * n; i++) t[i] = 0; }
	void add(int x, int v) { while(x <= 2 * n) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	// int query(int l, int r) { return query(r) - query(l - 1); }
} bit;

int out[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) b[a[i]] = i;
		bit.init();
		std::vector<std::pair<int, int>> vct;
		for(int i = 1; i <= n; i++) {
			if(i < b[i]) vct.emplace_back(b[i], i + n);
			else vct.emplace_back(b[i], i), vct.emplace_back(b[i] + n, i + n);
		}
		std::sort(vct.begin(), vct.end(), [&](std::pair<int, int> x, std::pair<int, int> y) {
			if(x.first == y.first) return x.second < y.second;
			else return x.first > y.first;
		});
		for(auto [l, r] : vct) {
			// printf("[%d, %d]\n", l, r);
			out[r > n ? r - n : r] = r - l - bit.query(r);
			bit.add(r, 1);
		}
		for(int i = 1; i <= n; i++) printf("%d ", out[i]);
		puts("");
	}
	return 0;
}