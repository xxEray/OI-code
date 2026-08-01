#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int D = 50;
const int MAXD = D + 5;

int n;
int fa[N];
std::vector<int> son[N];

LL ans[N];

int dep[N], d[N], hson[N], top[N];
void dfs(int u) {
	dep[u] = dep[fa[u]] + 1;
	for(int v : son[u]) {
		dfs(v);
		if(!hson[u] || d[v] > d[hson[u]]) hson[u] = v, d[u] = d[v] + 1;
	}
}

std::vector<int> f[N];
void dfs1(int u) {
	for(int v : son[u]) dfs1(v);
	for(int v : son[u]) if(v != hson[u]) {
		for(int i = D + 1; i <= (int)f[v].size(); i++) {
			LL sum = 0;
			for(int j = i - 1; j < (int)f[v].size(); j += i) sum += f[v][j];
			LL sum2 = 0;
			for(int j = dep[u] - dep[top[u]]; j < (int)f[top[u]].size(); j += i) sum2 += f[top[u]][j];
			ans[i] += sum * sum2;
			// printf("u = %d, v = %d, ans[%d] += %lld * %lld\n", u, v, i, sum, sum2);
		}
		for(int j = 0; j < (int)f[v].size(); j++) f[top[u]][dep[v] - dep[top[u]] + j] += f[v][j];
	}
	f[top[u]][dep[u] - dep[top[u]]]++;
}

LL g[MAXD][MAXD];
int rt;
void dfs2_calc(int u) {
	for(int i = 1; i <= D; i++) if(dep[u] % i == dep[rt] % i) ans[i] += g[i][dep[rt] % i];
	for(int v : son[u]) dfs2_calc(v);
}
void dfs2_add(int u) {
	for(int i = 1; i <= D; i++) g[i][dep[u] % i]++;
	for(int v : son[u]) dfs2_add(v);
}
void dfs2(int u) {
	for(int v : son[u]) if(v != hson[u]) {
		dfs2(v);
		for(int i = 1; i <= D; i++) for(int j = dep[v]; j <= dep[v] + d[v]; j++) g[i][j % i] = 0;
	}
	if(hson[u]) dfs2(hson[u]);
	for(int i = 1; i <= D; i++) ans[i] += g[i][dep[u] % i];
	for(int i = 1; i <= D; i++) g[i][dep[u] % i]++;
	rt = u;
	for(int v : son[u]) if(v != hson[u]) dfs2_calc(v), dfs2_add(v);
}

LL h[N];

int main() {
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) scanf("%d", &fa[i]), son[fa[i]].emplace_back(i);
	top[1] = 1, dfs(1);
	for(int u = 1; u <= n; u++) for(int v : son[u]) top[v] = (v == hson[u] ? top[u] : v);
	// for(int i = 1; i <= n; i++) printf("%d: top=%d, dep=%d, hson=%d, d=%d\n", i, top[i], dep[i], hson[i], d[i]);
	for(int i = 1; i <= n; i++) if(top[i] == i) f[i].resize(d[i] + 1);
	dfs1(1);
	fprintf(stderr, "time = %.3f\n", (double)clock() / 1024. / 1024);
	// printf("original ans (1): "); for(int i = 1; i <= n; i++) printf("%lld ", ans[i]); puts("");
	dfs2(1);
	fprintf(stderr, "time = %.3f\n", (double)clock() / 1024. / 1024);
	// printf("original ans (2): "); for(int i = 1; i <= n; i++) printf("%lld ", ans[i]); puts("");
	for(int i = 1; i <= n; i++) h[dep[i] - 1]++;
	for(int i = n; i >= 1; i--) h[i] += h[i + 1];
	// printf("h: "); for(int i = 1; i <= n; i++) printf("%lld ", h[i]); puts("");
	for(int i = 1; i <= n; i++) for(int j = i + i; j <= n; j += i) h[i] += h[j];
	for(int i = D + 1; i <= n; i++) ans[i] += h[i];
	// printf("original ans (3): "); for(int i = 1; i <= n; i++) printf("%lld ", ans[i]); puts("");
	for(int i = n; i >= 1; i--) for(int j = i + i; j <= n; j += i) ans[i] -= ans[j];
	for(int i = 1; i <= n - 1; i++) printf("%lld\n", ans[i]);
	return 0;
} /*
5
1
2
2
1
*/