#include <bits/stdc++.h>

typedef long long LL;

const int N = 20 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
int a[N], b[N];
std::vector<std::pair<int, LL>> to[N];

LL avg;
int avgcnt;

LL ret;
LL sum[N];
void dfs(int u, int fa) {
	sum[u] = a[u];
	for(auto [v, w] : to[u]) if(v != fa) {
		dfs(v, u);
		ret += std::abs(sum[v] - b[v]) * w;
		sum[u] += sum[v];
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) to[i].clear();
		avg = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), avg += a[i];
		for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); to[u].push_back({v, w}), to[v].push_back({u, w}); }
		avgcnt = avg % n, avg /= n;
		int U = (1 << n) - 1;
		LL ans = LLINF;
		for(int s = 0; s <= U; s++) if(__builtin_popcount(s) == avgcnt) {
			for(int i = 1; i <= n; i++)
				if(s >> (i - 1) & 1) b[i] = avg + 1;
				else b[i] = avg;
			for(int i = 1; i <= n; i++) sum[i] = 0;
			ret = 0;
			dfs(1, 0);
			ans = std::min(ans, ret);
		}
		printf("%lld\n", ans);
	}
	return 0;
}