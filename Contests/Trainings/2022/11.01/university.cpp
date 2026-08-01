#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>

typedef long long LL;

const int N = 3e5 + 5;
const LL MOD = 998244353;

int n, m;
std::vector<int> to[N], from[N];

std::set<int> st[N];

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[std::min(x, y)] = std::max(x, y) : 0; }

int main() {
#ifndef DEBUG
	freopen("university.in", "r", stdin);
	freopen("university.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		if(u > v) std::swap(u, v);
		to[u].push_back(v), from[v].push_back(u);
	}
	LL ans = 1;
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1; i <= n; i++) {
		for(int j : from[i]) {
			j = find(j);
			if(i == j) continue;
			if(st[j].size() > st[i].size()) std::swap(st[i], st[j]);
			for(int x : st[j]) st[i].insert(x);
			// st[j].clear();
			merge(i, j);
		}
		for(int x : to[i]) st[i].insert(x);
		if(st[i].find(i) != st[i].end()) st[i].erase(i);
		// printf("%d: sz = %d\n", i, (int)st[i].size());
		(ans *= n - (int)st[i].size()) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
}