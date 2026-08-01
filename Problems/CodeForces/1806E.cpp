#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

typedef long long LL;

const int N = 1e5 + 5;
const int D = 500;

int n, Q;
int fa[N], dep[N], s[N];
LL a[N];

int pos[N];
std::vector<std::vector<LL>> g[N];
#define f(u, v) g[dep[u]][pos[u]][pos[v]]

std::vector<std::pair<int, int>> stk;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 2; i <= n; i++) scanf("%d", &fa[i]);
	for(int i = 1; i <= n; i++) dep[i] = dep[fa[i]] + 1, pos[i] = s[dep[i]], s[dep[i]]++;
	for(int i = 1; i <= n; i++) if(s[i] <= D) g[i].resize(s[i], std::vector<LL>(s[i]));
	g[0].push_back({0});
	while(Q--) {
		int u, v;
		scanf("%d%d", &u, &v);
		while(u && v && (s[dep[u]] > D || !f(u, v))) {
			stk.push_back({u, v});
			u = fa[u], v = fa[v];
		}
		LL ans = f(u, v);
		while(!stk.empty()) {
			u = stk.back().first, v = stk.back().second;
			stk.pop_back();
			ans += a[u] * a[v];
			if(s[dep[u]] <= D) f(u, v) = f(v, u) = ans;
		}
		printf("%lld\n", ans);
	}
	return 0;
}