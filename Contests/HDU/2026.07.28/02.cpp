#include <bits/stdc++.h>

const int N = 66 + 5;

int n, m;
int a[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		std::vector<std::pair<double, int>> vct;
		for(int i = 1; i <= n; i++) vct.emplace_back(a[i], a[i]), vct.emplace_back(a[i] / (a[i] - 1.) * (n - 1), -a[i]);
		std::sort(vct.begin(), vct.end(), std::greater<std::pair<double, int>>());
		
	}
	return 0;
}