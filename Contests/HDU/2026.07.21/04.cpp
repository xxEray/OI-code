#include <bits/stdc++.h>
#include <cassert>

typedef long long LL;

const int N = 2e5 + 5;

int n;
LL a[N], b[N];
int fa[N];

struct Node { int id; LL A, B; };
struct cmp {
	bool operator()(const Node &i, const Node &j) const { return i.B * j.A > j.B * i.A; }
};
std::priority_queue<Node, std::vector<Node>, cmp> q;

struct DSU {
	int ld[N];
	void init() { for(int i = 1; i <= n; i++) ld[i] = i; }
	int find(int x) { return x == ld[x] ? x : ld[x] = find(ld[x]); }
} dsu;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		dsu.init();
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
		for(int i = 1; i <= n; i++) scanf("%d", &fa[i]);
		for(int i = 2; i <= n; i++) q.push({i, a[i], b[i]});
		LL ans = 0;
		while(!q.empty()) {
			auto [u, ua, ub] = q.top();
			q.pop();
			if(dsu.find(u) != u || ua != a[u] || ub != b[u]) continue;
			// printf("u = %d\n", u);
			int v = dsu.find(fa[u]);
			ans += b[v] * a[u];
			a[v] += a[u], b[v] += b[u];
			dsu.ld[u] = v;
			// printf("merge %d %d\n", u, v);
			if(v > 1) q.push({v, a[v], b[v]});
		}
		printf("%lld\n", ans);
	}
	return 0;
}