#include <bits/stdc++.h>

typedef long long LL;

const int N = 500 + 5;

int n;
LL K;
int a[N];

std::vector<std::vector<int>> vct;

int main() {
	scanf("%d%lld", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) for(int j = i; j <= n; j++) {
		std::vector<int> tmp(a + i, a + j + 1);
		std::sort(tmp.begin(), tmp.end());
		vct.emplace_back(std::move(tmp));
	}
	std::nth_element(vct.begin(), vct.begin() + K - 1, vct.end(), [&](const std::vector<int> &x, const std::vector<int> &y) {
		for(int i = 0; i < (int)std::min(x.size(), y.size()); i++) if(x[i] != y[i]) return x[i] < y[i];
		if(x.size() == y.size()) return false;
		else return x.size() > y.size();
	});
	// for(auto &vec : vct) {
	// 	for(auto x : vec) printf("%d ", x);
	// 	puts("");
	// }
	for(auto x : vct[K - 1]) printf("%d ", x);
	puts("");
	return 0;
}