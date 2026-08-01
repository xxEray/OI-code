#include <bits/stdc++.h>

const int N = 1e5 + 5;
const int M = 1e6 + 5;

int n;
char tmp[M];

int c[M][2], fa[M], end[M];
int tot = 1;

struct SegNode { SegNode *ls, *rs; int val, d; } nd[2 * M], *nil;
SegNode *nw(int v) { static int k = 0; k++; nd[k].val = v; nd[k].ls = nil, nd[k].rs = nil; return &nd[k]; }
SegNode *merge(SegNode *x, SegNode *y) {
	if(x == nil || y == nil) return x == nil ? y : x;
	if(x->val > y->val) std::swap(x, y);
	x->rs = merge(x->rs, y);
	if(x->rs->d > x->ls->d) std::swap(x->ls, x->rs);
	x->d = x->rs->d + 1;
	return x;
}

long long ans;
SegNode *f[M], *g[M];
void dfs(int u, int dep) {
	if(!u) { f[u] = g[u] = nil; return; }
	dfs(c[u][0], dep + 1), dfs(c[u][1], dep + 1);
	f[u] = merge(f[c[u][0]], f[c[u][1]]), g[u] = merge(g[c[u][0]], g[c[u][1]]);
	int cn = end[u];
	if(!c[u][0] && !c[u][1]) g[u] = merge(g[u], nw(dep));
	else if(!c[u][0]) g[u] = merge(g[u], nw(dep + 1));
	else if(!c[u][1]) g[u] = merge(g[u], nw(dep + 1));
	// printf("dfs(%d, %d) cn=%d", u, dep, cn);
	while(cn--) {
		if(g[u] == nil || (f[u] != nil && f[u]->val + 2 < g[u]->val)) {
			int v = f[u]->val;
			f[u] = merge(f[u]->ls, f[u]->rs), f[u] = merge(f[u], nw(v + 1)), f[u] = merge(f[u], nw(v + 1));
			ans += v + 2 - dep;
		} else {
			int v = g[u]->val;
			g[u] = merge(g[u]->ls, g[u]->rs);
			f[u] = merge(f[u], nw(v));
			ans += v - dep;
		}
	}
	// printf(" (ans=%lld)\n", ans);
}

int main() {
	nil = &nd[0], nil->ls = nil, nil->rs = nil, nil->d = -1;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%s", tmp + 1);
		int m = strlen(tmp + 1);
		int now = 1;
		for(int j = 1; j <= m; j++) {
			if(!c[now][tmp[j] - '0']) c[now][tmp[j] - '0'] = ++tot, fa[tot] = now;
			now = c[now][tmp[j] - '0'];
		}
		end[now]++;
	}
	dfs(1, 0);
	printf("%lld\n", ans);
	return 0;
}