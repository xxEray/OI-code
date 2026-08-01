#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m, K;
std::vector<std::array<int, 3>> e[2], edges[N];

struct DSU {
	int ld[N];
	void init() { for(int i = 1; i <= n; i++) ld[i] = i; }
	int find(int x) { return x == ld[x] ? x : ld[x] = find(ld[x]); }
	void merge(int u, int v) { ld[find(u)] = find(v); }
} dsu, dsu2;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		e[0].clear(), e[1].clear();
		scanf("%d%d%d", &n, &m, &K);
		dsu.init();
		for(int i = 1; i <= n; i++) edges[i].clear();
		for(int i = 1; i <= m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			e[w].push_back({u, v, i});
		}
		for(auto [u, v, _] : e[0]) dsu.merge(u, v);
		// for(int i = 1; i <= n; i++) printf("find(%d) = %d\n", i, dsu.find(i));
		for(auto [u, v, id] : e[1])
			if(dsu.find(u) == dsu.find(v))
				edges[dsu.find(u)].push_back({u, v, id});
		dsu2 = dsu;
		int base = 0;
		std::vector<int> ans;
		std::vector<std::array<int, 3>> tmp;
		for(auto [u, v, id] : e[1])
			if(dsu.find(u) != dsu.find(v)) {
				dsu.merge(u, v), base++;
				tmp.push_back({u, v, id});
			}
		if(K < base) { puts("-1"); continue; }
		int mx = 0;
		dsu.init();
		for(auto [u, v, id] : tmp) {
			dsu.merge(u, v), mx++;
			ans.emplace_back(id);
		}
		if(mx < K)
			for(auto [u, v, id] : e[1])
				if(dsu2.find(u) != dsu2.find(v) && dsu.find(u) != dsu.find(v)) {
					dsu.merge(u, v), mx++;
					ans.emplace_back(id);
					if(mx == K) break;
				}
		for(int i = 1; i <= n; i++) {
			// if(!edges[i].empty()) printf("block %d:\n", i);
			if(mx == K) break;
			for(auto [u, v, id] : edges[i]) {
				// printf("%d %d %d\n", u, v, id);
				if(dsu.find(u) != dsu.find(v)) {
					dsu.merge(u, v), mx++;
					ans.emplace_back(id);
					if(mx == K) break;
				}
			}
		}
		// printf("mx = %d\n", mx);
		if(mx < K) { puts("-1"); continue; }
		for(auto [u, v, id] : e[0])
			if(dsu.find(u) != dsu.find(v))
				dsu.merge(u, v), ans.emplace_back(id);
		std::sort(ans.begin(), ans.end());
		for(int x : ans) printf("%d ", x);
		puts("");
	}
	return 0;
}