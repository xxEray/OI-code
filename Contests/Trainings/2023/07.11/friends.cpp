#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n, m;

std::set<int> in[N], oup[N];
std::set<std::pair<int, int>> out[N];
LL ans;


int fa[N], sz[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
std::vector<std::pair<int, int>> stk;
void debug() {
	for(int i = 1; i <= n; i++) {
		printf("%d: fa = %d, sz = %d, in =", i, fa[i], sz[i]);
		for(int x : in[i]) printf(" %d", x);
		printf(", out =");
		for(auto &p : out[i]) printf(" %d->%d", p.first, p.second);
		printf(", oup =");
		for(int x : oup[i]) printf(" %d", x);
		puts("");
	}
}
void merge(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) return;
	if(sz[x] < sz[y]) std::swap(x, y);
	// debug(), printf("merge(%d, %d)\n", x, y);
	ans += (LL)(sz[x] + sz[y]) * (sz[x] + sz[y] - 1) - (LL)sz[x] * (sz[x] - 1) - (LL)sz[y] * (sz[y] - 1);
	ans -= (LL)in[x].size() * sz[x] + (LL)in[y].size() * sz[y];
	oup[x].erase(y), oup[y].erase(x);
	std::vector<int> tmp;
	for(int z : in[y]) if(find(z) == find(x)) tmp.push_back(z);
	for(int z : tmp) in[y].erase(z);
	for(auto &p : out[y]) if(find(p.second) == find(x)) tmp.push_back(p.first);
	for(int z : tmp) in[x].erase(z);
	fa[y] = x, sz[x] += sz[y];
	for(int z : in[y]) in[x].insert(z), oup[find(z)].erase(y), oup[find(z)].insert(x);
	for(auto &p : out[y]) if(find(p.second) != find(x)) out[x].insert(p);
	for(int z : oup[y]) if(oup[z].count(x)) stk.push_back({x, z});
	for(int z : in[y]) if(oup[x].count(find(z))) stk.push_back({x, z});
	for(int z : oup[y]) oup[x].insert(z);
	sz[y] = 0;
	in[y].clear(), out[y].clear(), oup[y].clear();
	ans += (LL)in[x].size() * sz[x];
	// printf("ans = %lld\n", ans);
}

int main() {
#ifndef DEBUG
	freopen("friends.in", "r", stdin);
	freopen("friends.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
	for(int i = m; i >= 1; i--) {
		int u, v;
		scanf("%d%d", &u, &v);
		int ov = v;
		v = find(v);
		if(find(u) != v && !in[v].count(u)) {
			in[v].insert(u), out[find(u)].insert({u, ov}), oup[find(u)].insert(v);
			ans += sz[v];
			if(oup[v].count(find(u))) {
				merge(u, v);
				while(!stk.empty()) {
					int p = stk.back().first, q = stk.back().second;
					stk.pop_back();
					merge(p, q);
				}
			}
		}
		// debug();
		printf("%lld\n", ans);
	}
	return 0;
} /*
5 6
5 2
2 5
1 4
5 1
4 1
4 2
*/