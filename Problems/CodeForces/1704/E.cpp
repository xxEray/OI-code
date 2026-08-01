#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 1000 + 5;
const LL MOD = 998244353;

LL a[N], b[N];
int n, m;
std::vector<int> to[N], rev[N];
int rt;

bool vis[N];
void dfs(int u) {
	if(vis[u]) return;
	vis[u] = true;
	for(int v : rev[u]) dfs(v);
	if(a[u]) {
		a[u]--;
		for(int v : to[u]) b[v]++;
	}
}
void dfs2(int u) {
	if(vis[u]) return;
	vis[u] = true;
	for(int v : rev[u]) dfs2(v);
	for(int v : to[u]) (a[v] += a[u]) %= MOD;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) to[i].clear(), rev[i].clear();
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v), rev[v].push_back(u); }
		for(int i = 1; i <= n; i++) if(to[i].empty()) rt = i;
		// printf("rt = %d\n", rt);
		LL ans = -1;
		bool flag = true;
		for(int i = 1; i <= n; i++) flag &= a[i] == 0;
		if(flag) { puts("0"); continue; }
		// printf("%d: ", 0);
		// for(int j = 1; j <= n; j++) printf("%lld ", a[j]);
		// puts("");
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) vis[j] = false;
			dfs(rt);
			for(int j = 1; j <= n; j++) a[j] += b[j], b[j] = 0;
			// printf("%d: ", i);
			// for(int j = 1; j <= n; j++) printf("%lld ", a[j]);
			// puts("");
			flag = true;
			for(int j = 1; j <= n; j++) flag &= a[j] == 0;
			if(flag) { ans = i; break; }
		}
		if(ans != -1) { printf("%lld\n", ans); continue; }
		for(int i = 1; i <= n; i++) vis[i] = false, a[i] %= MOD;
		dfs2(rt);
		printf("%lld\n", (a[rt] + n) % MOD);
	}
	return 0;
} /*
1
7 8
1 0 0 0 0 0 0
1 2
1 3
2 4
3 4
4 5
4 6
5 7
6 7
*/