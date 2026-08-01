#include <bits/stdc++.h>

const int N = 5000 + 5;

int n, m;

std::vector<int> to[N];

double f[N], g[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) to[i].clear();
		for(int i = 1; i <= n; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v); }
		f[n] = 1;
		for(int i = n - 1; i >= 1; i--) {
			std::sort(to[i].begin(), to[i].end(), [&](int x, int y) { return f[x] > f[y]; });
			int sz = to[i].size();
			g[sz] = 0;
			for(int j = sz - 1; j >= 0; j--) g[j] = g[]
		}
	}
	return 0;
}