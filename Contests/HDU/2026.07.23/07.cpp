#include <bits/stdc++.h>
#ifdef DEBUG
#include "stl_printer.h"
#endif

typedef long long LL;

const int N = 2e5 + 5;

int n;
std::vector<int> to[N];

LL ans;

int sz[N], cnt[N];

std::vector<int> prime, factor[N];
int mu[N];
bool isprm[N];
void get_mu(int mx) {
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	mu[1] = 1;
	for(int i = 2; i <= mx; i++) {
		if(isprm[i]) prime.emplace_back(i), mu[i] = -1;
		for(int p : prime) {
			if(p * i > mx) break;
			isprm[p * i] = false;
			if(i % p == 0) {
				mu[i * p] = 0;
				break;
			} else mu[i * p] = mu[i] * mu[p];
		}
	}
	for(int i = 1; i <= mx; i++)
		for(int j = i; j <= mx; j += i)
			factor[j].emplace_back(i);
}

void dfs0(int u, int fa) { // get sz[]
	sz[u] = factor[u].size();
	for(int v : to[u]) if(v != fa) dfs0(v, u), sz[u] += sz[v];
}

void dfs_del(int u, int fa) {
	for(int i : factor[u]) cnt[i]--;
	for(int v : to[u]) if(v != fa) dfs_del(v, u);
}

void dfs_add(int u, int fa) {
	for(int i : factor[u]) cnt[i]++;
	for(int v : to[u]) if(v != fa) dfs_add(v, u);
}

int u0;
void dfs_calc(int u, int fa) {
	for(int i : factor[u]) if(i % u0 == 0) ans += mu[i / u0] * cnt[i];
	for(int v : to[u]) if(v != fa) dfs_calc(v, u);
}

void dfs1(int u, int fa, bool keep) {
	int hson = 0;
	for(int v : to[u]) if(v != fa && sz[v] > sz[hson]) hson = v;
	for(int v : to[u]) if(v != fa && v != hson) dfs1(v, u, false);
	if(hson) dfs1(hson, u, true);
	ans += cnt[u]; // mu[u / u] * cnt[u]
	for(int i : factor[u]) cnt[i]++;
	// printf("u=%d, cnt: %s\n", u, tostring(cnt + 1, cnt + n + 1).c_str());
	u0 = u;
	for(int v : to[u]) if(v != fa && v != hson) dfs_calc(v, u), dfs_add(v, u);
	if(!keep) dfs_del(u, fa);
}

int main() {
	get_mu(2e5);
	int T; scanf("%d", &T);
	while(T--) {
		ans = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) to[i].clear();
		for(int i = 1; i < n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			to[x].emplace_back(y), to[y].emplace_back(x);
		}
		// for(int i = 1; i <= n; i++) cnt[i] = 0;
		dfs0(1, 0), dfs1(1, 0, false);
		printf("%lld\n", ans);
	}
	return 0;
}