#pragma GCC optimize(2)
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>

#define SZ(x) ((int)(x).size())

typedef long long LL;

const int N = 1e5 + 5;

int n, m;
std::vector<int> to[N];
std::vector<int> e[N], order;

int a[N], d[N];
bool exist[N];

unsigned long long f[N];
int id[N];
bool vis[N];
void dfs(int u) {
	if(vis[u]) return;
	vis[u] = true;
	for(int v : e[u]) dfs(v);
	order.push_back(u);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) to[i].clear(), exist[i] = true, e[i].clear(), f[i] = 0, d[i] = 0, vis[i] = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v), to[v].push_back(u), d[u]++, d[v]++; }
		std::vector<int> q;
		bool flag = true;
		for(int i = 1; i <= n; i++)
			if(SZ(to[i]) < a[i]) flag = false;
			else if(SZ(to[i]) == a[i]) q.push_back(i);
		while(!q.empty()) {
			int u = q.back();
			// printf("%d(%d) ", u, flag);
			// for(int v : q) printf("%d ", v);
			// puts("");
			assert(d[u] == a[u] || flag == false);
			exist[u] = false;
			q.pop_back();
			for(int v : to[u]) if(exist[v]) {
				d[v]--;
				e[u].push_back(v);
				if(d[v] < a[v]) flag = false;
				else if(d[v] == a[v]) q.push_back(v);
			}
			to[u].clear();
		}
		for(int i = 1; i <= n; i++) flag &= (exist[i] == false);
		if(!flag) puts("Error");
		LL ans = (LL)n * (n - 1) / 2;
		for(int i = 1; i <= n; i++) dfs(i);
		for(int i = 1; i <= n; i++) id[i] = 64;
		for(int i = 1; i <= n; i += 64) {
			for(int j = i; j <= i + 63; j++) id[j] = j - i;
			for(int j = 1; j <= n; j++) f[j] = 0;
			for(int u : order) for(int v : e[u]) {
				f[u] |= f[v];
				if(id[v] <= 63) f[u] |= (1LL << v);
			}
			for(int j = 1; j <= n; j++) ans -= __builtin_popcountll(f[j]);
			for(int j = i; j <= i + 63; j++) id[j] = 64;
		}
		printf("%lld\n", ans);
	}
	return 0;
}