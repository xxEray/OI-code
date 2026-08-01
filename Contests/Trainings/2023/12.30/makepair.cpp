#include <bits/stdc++.h>

const int N = 5000 + 5;
const long long LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
int a[N];
std::vector<int> to[N];

int fbd1, fbd2;
long long sum;
long long ans[N];
int dfs(int u, int fa) {
	if(u <= m) return u == fbd1 || u == fbd2 ? -1 : a[u];
	std::vector<int> vct;
	for(int v : to[u]) if(v != fa) {
		int val = dfs(v, u);
		if(val != -1) vct.emplace_back(val);
	}
	if(vct.size() == 0) return -1;
	else if(vct.size() == 1) return vct[0];
	else if(vct.size() == 2) {
		sum += vct[0] ^ vct[1];
		return -1;
	} else { sum = -LLINF; return -1; }
}

int main() {
#ifndef DEBUG
	freopen("makepair.in", "r", stdin);
	freopen("makepair.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); to[u].emplace_back(v), to[v].emplace_back(u); }
	for(fbd1 = 1; fbd1 <= m; fbd1++) for(fbd2 = 1; fbd2 <= m; fbd2++) if(fbd1 != fbd2) {
		sum = 0;
		dfs(n, 0);
		ans[fbd1] = std::max(ans[fbd1], sum);
	}
	for(int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
	return 0;
}