#include <cstdio>
#include <algorithm>
#include <set>

typedef long long LL;

const int N = 2e5 + 5;

LL a[N], b[N];
int n, m;
std::set<std::pair<LL, int>> nodes;
std::set<int> to[N];


int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[u].insert(v), to[v].insert(u); b[u] += a[v], b[v] += a[u]; }
	for(int i = 1; i <= n; i++) nodes.insert({b[i], i});
	LL ans = 0;
	while(!nodes.empty()) {
		int u = nodes.begin()->second;
		nodes.erase(nodes.begin());
		LL sum = 0;
		for(int v : to[u]) to[v].erase(u), nodes.erase({b[v], v}), b[v] -= a[u], nodes.insert({b[v], v}), sum += a[v];
		to[u].clear();
		ans = std::max(ans, sum);
	}
	printf("%lld\n", ans);
	return 0;
}