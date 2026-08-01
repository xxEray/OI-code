#include <bits/stdc++.h>

const int N = 7000 + 5;

int n, K;
int a[N];

int f[N];

void print() {
	for(int i = 1; i <= n; i++) printf("%d ", a[i]);
	puts("");
}

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) {
		std::vector<int> v0, v1;
		for(int j = i + 1; j <= n; j++)
			if(a[j] < a[i]) v0.push_back(j);
			else if(a[j] > a[i]) v1.push_back(j);
		std::sort(v0.begin(), v0.end(), [&](int x, int y) { return a[x] < a[y]; });
		std::sort(v1.begin(), v1.end(), [&](int x, int y) { return a[x] < a[y]; });
		if(K <= (int)v0.size()) { std::reverse(a + i, a + v0[K - 1] + 1), print(); return 0; }
		K -= (int)v0.size();
		if(K <= (n - i) * (n - i - 1) / 2 + n) continue;
		K -= (n - i) * (n - i - 1) / 2 + n;
		if(K <= (int)v1.size()) { std::reverse(a + i, a + v1[K - 1] + 1), print(); return 0; }
		// printf("%d: K = %d\n", i, K);
		assert(false);
	}
	print();
	return 0;
}