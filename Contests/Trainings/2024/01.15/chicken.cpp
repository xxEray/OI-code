#include <bits/stdc++.h>

const int N = 5 + 4;

int n, m, mod;
int a[N];

std::set<std::vector<int>> st;
void calc() {
	std::vector<int> ret(n);
	for(int i = 1; i <= n; i++) {
		int copy = a[i];
		a[i] = 0;
		int mx = 0, f = 0, g = 0;
		for(int j = 1; j <= n; j++) mx = std::max(mx, g), g = f, f = std::max(g, a[j] + mx);
		ret[i - 1] = f;
		a[i] = copy;
	}
	st.emplace(ret);
}

void dfs(int id) {
	if(id == n + 1) { calc(); return; }
	for(int i = 0; i <= m; i++) a[id] = i, dfs(id + 1);
}

int main() {
#ifndef DEBUG
	freopen("chicken.in", "r", stdin);
	freopen("chicken.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &mod);
	dfs(1);
	printf("%d\n", (int)st.size() % mod);
	return 0;
}