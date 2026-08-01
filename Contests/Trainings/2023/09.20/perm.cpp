#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const int INF = 0x3f3f3f3f;

int n;
LL K;
struct Edge { int to, nxt; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }

int fa[N], sz[N];
void dfs(int u) {
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		dfs(v);
		sz[u] += sz[v];
	}
}

int a[N];
int tin[N], rk[N], order[N];

int nxt[N];
std::vector<int> sub[N];
std::vector<std::pair<int, int>> chain[N];
void solve(int u) {
	LL sum = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		solve(v), sum += a[v];
	}
	sum += 1 - a[u];
	nxt[u] = 0;
	if(u != 1) chain[u].emplace_back(u, u);
	int len = sub[u].size();
	if(len == 1) {
		assert(!sum);
		if(u == 1) chain[u].swap(chain[sub[u][0]]);
		return;
	}
	// printf("%d: sum = %d\n", u, sum);
	// for(int i = 0; i < len; i++) {
	// 	printf("sub[%d][%d] = %d: ", u, i, sub[u][i]);
	// 	for(auto x : chain[sub[u][i]]) printf("(%d, %d) ", x.first, x.second);
	// 	puts("");
	// }
	int j = 0;
	while(j < len - 1 && chain[sub[u][j + 1]].size() == chain[sub[u][j]].size()) j++;
	int nowst = chain[sub[u][j]].back().first, now = chain[sub[u][j]].back().second, nowid = j;
	chain[sub[u][j]].pop_back();
	// printf("%d", now);
	int i = 1;
	while(i < len - 1 && chain[sub[u][i + 1]].size() == chain[sub[u][i]].size()) i++;
	while(sum) {
		while(j < len - 1 && chain[sub[u][j + 1]].size() == chain[sub[u][j]].size()) j++;
		if(j) break;
		if(nowid != 0) {
			nxt[now] = chain[sub[u][0]].back().first, now = chain[sub[u][0]].back().second, nowid = 0;
			chain[sub[u][0]].pop_back();
			sum--;
			// printf(" -> %d", now);
			continue;
		}
		assert(nowid != i);
		nxt[now] = chain[sub[u][i]].back().first, now = chain[sub[u][i]].back().second, nowid = i;
		chain[sub[u][i]].pop_back();
		sum--;
		// printf(" -> %d", now);
		if(i == 1) {
			while(i < len - 1 && chain[sub[u][i + 1]].size() == chain[sub[u][i]].size()) i++;
		} else i--;
	}
	i = 0;
	while(i < len - 1 && chain[sub[u][i + 1]].size() == chain[sub[u][i]].size()) i++;
	while(sum) {
		assert(nowid != i);
		nxt[now] = chain[sub[u][i]].back().first, now = chain[sub[u][i]].back().second, nowid = i;
		chain[sub[u][i]].pop_back();
		sum--;
		// printf(" -> %d", now);
		if(i == 0) {
			while(i < len - 1 && chain[sub[u][i + 1]].size() == chain[sub[u][i]].size()) i++;
		} else i--;
	}
	// puts("");
	assert(!sum);
	chain[u].emplace_back(nowst, now);
	for(int v : sub[u]) if(v != u) {
		if(chain[u].size() < chain[v].size()) chain[u].swap(chain[v]);
		chain[u].insert(chain[u].end(), chain[v].begin(), chain[v].end());
	}
	assert(u == 1 || (int)chain[u].size() == a[u]);
	// printf("chain[%d]: ", u); for(auto &p : chain[u]) printf("(%d, %d) ", p.first, p.second); puts("");
}

int main() {
#ifndef DEBUG
	freopen("perm.in", "r", stdin);
	freopen("perm.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1;
		scanf("%d%lld", &n, &K);
		for(int i = 1; i <= n; i++) head[i] = 0, chain[i].clear(), sub[i].clear(), nxt[i] = 0;
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
		dfs(1);
		for(int i = 1; i <= n; i++) a[i] = std::min(sz[i], n - sz[i]);
		for(int i = 0; i <= n; i++) tin[i] = 0;
		for(int i = 1; i <= n; i++) tin[a[i]]++;
		for(int i = 1; i <= n; i++) tin[i] += tin[i - 1];
		for(int i = n; i >= 1; i--) rk[i] = tin[a[i]]--;
		for(int i = 1; i <= n; i++) order[rk[i]] = i;
		// printf("a: "); for(int i = 1; i <= n; i++) printf("%d ", a[i]); puts("");
		// printf("rk: "); for(int i = 1; i <= n; i++) printf("%d ", rk[i]); puts("");
		// printf("order: "); for(int i = 1; i <= n; i++) printf("%d ", order[i]); puts("");
		LL sum = 0;
		for(int i = 1; i <= n; i++) sum += a[i];
		if(K / 2 < n - 1 || K / 2 > sum || (K & 1)) { puts("-1"); continue; }
		sum -= K / 2;
		// printf("sum = %d\n", sum);
		if(sum)
			for(int i = n; i >= 1; i--) {
				while(i > 1 && a[order[i - 1]] == a[order[i]]) i--;
				int val = (n - i + 1) * (a[order[i]] - a[order[i - 1]]);
				if(sum >= val) {
					sum -= val;
					if(!sum) {
						int y = a[order[i - 1]];
						for(int j = i; j <= n; j++) a[order[j]] = y;
					}
				} else {
					int x = sum / (n - i + 1);
					int y = a[order[i]] - x;
					for(int j = i; j <= n; j++) a[order[j]] = y;
					sum -= x * (n - i + 1);
					for(int j = i; j <= n; j++) if(sum) a[order[j]]--, sum--;
					break;
				}
			}
		assert(!sum);
		// printf("a: "); for(int i = 1; i <= n; i++) printf("%d ", a[i]); puts("");
		for(int i = n; i >= 1; i--) sub[fa[order[i]]].push_back(order[i]);
		for(int i = 2; i <= n; i++) sub[i].push_back(i);
		a[1] = 2;
		solve(1);
		// printf("nxt: "); for(int i = 1; i <= n; i++) printf("%d ", nxt[i]); puts("");
		assert(!chain[1].empty());
		// printf("circle: 1 "); for(int i = chain[1].back().first; i; i = nxt[i]) printf("%d ", i); puts("");
		for(int i = chain[1].back().first; i; i = nxt[i]) printf("%d ", i - 1);
		puts("");
	}
	return 0;
} /*
2
5 10
1 2
2 3
3 4
3 5
5 12
1 2
2 3
3 4
3 5
*/