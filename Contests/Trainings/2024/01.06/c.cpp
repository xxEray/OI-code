#include <bits/stdc++.h>

#ifndef DEBUG
	#undef assert
	#define assert(...) ((void)0)
#endif

const int N = 10 + 3;
const int M = 1e5 + 5;
const int MAXK = 30 + 3;
const int MAXQ = 1e5 + 5;

int n, m, K, Q;

bool sig[M]; // significant
// int prvs[M], nxts[M];
std::vector<int> sigs;
int isig[M];
std::vector<std::pair<int, int>> edges[MAXK];

std::vector<int> rp[N], bl[N];
std::map<int, std::pair<int, int>> id[N];
int cid;

int getid(int i, int j) { // 第 i 辆车第 j 站所属区域的下标
	assert(1 <= j && j <= rp[i].back());
	return std::lower_bound(rp[i].begin(), rp[i].end(), j) - rp[i].begin();
}

struct DSU {
	int fa[(N + MAXK) * N * 2];
	void init(int mx) { for(int i = 1; i <= mx; i++) fa[i] = i; }
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	bool same(int x, int y) { return find(x) == find(y); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : false; }
} dsu[N + MAXK][N + MAXK];

int main() {
#ifndef DEBUG
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		int k, z, r, mn = m;
		scanf("%*d%d", &k);
		while(k--) scanf("%d%*d%d", &z, &r), rp[i].emplace_back(r), bl[i].emplace_back(z), mn = std::min(mn, z);
		sig[mn] = true;
	}
	scanf("%d", &K);
	for(int i = 1; i <= K; i++) {
		int c;
		scanf("%d", &c);
		while(c--) {
			int j, k;
			scanf("%d%d", &j, &k);
			edges[i].emplace_back(j, k);
			int t = getid(j, k);
			sig[bl[j][t]] = true;
		}
	}
	for(int i = 1; i <= m; i++) if(sig[i]) isig[i] = sigs.size(), sigs.emplace_back(i);
	assert((int)sigs.size() <= n + K);
	// printf("sigs: "); for(int i : sigs) printf("%d ", i); puts("");
	// for(int i = 1, j = 0; i <= m; i++) sig[i] ? j = i : 0, prvs[i] = j;
	// for(int i = m, j = m + 1; i >= 1; i--) sig[i] ? j = i : 0, nxts[i] = j;
	for(int i = 1; i <= n; i++) for(int j = 0; j < (int)bl[i].size(); j++) if(sig[bl[i][j]]) id[i][j] = {++cid, isig[bl[i][j]]};
	for(int l = 0; l < (int)sigs.size(); l++) for(int r = 0; r < (int)sigs.size(); r++) dsu[l][r].init(cid);
	for(int l = 0; l < (int)sigs.size(); l++) for(int r = l; r < (int)sigs.size(); r++) {
		for(int i = 1; i <= n; i++) {
			int last = 0;
			for(auto p : id[i]) {
				int t = p.second.second;
				if(t < l || t > r) { last = 0; continue; }
				if(last) dsu[l][r].merge(last, p.second.first);
				last = p.second.first;
			}
		}
		for(int k = 1; k <= K; k++) {
			int last = 0;
			for(auto [i, j] : edges[k]) {
				int t = getid(i, j);
				assert(sig[bl[i][t]]);
				if(bl[i][t] < sigs[l] || bl[i][t] > sigs[r]) continue;
				if(last) dsu[l][r].merge(last, id[i][t].first);
				last = id[i][t].first;
			}
		}
	}
	// for(int i = 1; i <= n; i++) {
	// 	printf("id[%d]: ", i);
	// 	for(auto p : id[i]) printf("(%d: (%d, %d)) ", p.first, p.second.first, p.second.second);
	// 	puts("");
	// }
	scanf("%d", &Q);
	while(Q--) {
		int i1, j1, i2, j2;
		scanf("%d%d%d%d", &i1, &j1, &i2, &j2);
		j1 = getid(i1, j1), j2 = getid(i2, j2);
		int b1 = bl[i1][j1], b2 = bl[i2][j2];
		if(b1 > b2) std::swap(i1, i2), std::swap(j1, j2), std::swap(b1, b2);
		// printf("i1 = %d, j1 = %d, b1 = %d\n", i1, j1, b1);
		// printf("i2 = %d, j2 = %d, b2 = %d\n", i2, j2, b2);
		int ans = m + 1;
		auto calc = [b1, b2, &ans](auto it1, auto it2) {
			auto [x, i] = it1->second;
			auto [y, j] = it2->second;
			// printf("calc i=%d, j=%d, x=%d, y=%d\n", i, j, x, y);
			if(i > j) std::swap(i, j), std::swap(x, y);
			for(int l = 0, r = j; l <= i; l++) {
				while(r < (int)sigs.size())
					if(dsu[l][r].same(x, y)) {
						ans = std::min(ans, std::max(sigs[r], b2) - std::min(sigs[l], b1) + 1);
						break;
					} else r++;
			}
		};
		auto it1 = id[i1].lower_bound(j1), it2 = id[i2].lower_bound(j2);
		if(it1 != id[i1].begin() && it2 != id[i2].begin()) calc(std::prev(it1), std::prev(it2));
		if(it1 != id[i1].end() && it2 != id[i2].begin()) calc(it1, std::prev(it2));
		if(it1 != id[i1].begin() && it2 != id[i2].end()) calc(std::prev(it1), it2);
		if(it1 != id[i1].end() && it2 != id[i2].end()) calc(it1, it2);
		if(i1 == i2) ans = std::min(ans, std::abs(j1 - j2) + 1);
		if(ans == m + 1) puts("-1");
		else printf("%d\n", ans);
	}
	return 0;
}