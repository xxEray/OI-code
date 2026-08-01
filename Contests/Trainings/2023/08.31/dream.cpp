#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n;

struct Splay {
	int fa[N], c[N][2];
	int rt;
	int chtype(int x) { return x == c[fa[x]][1]; }
	void rotate(int x) {
		int y = fa[x], z = fa[y];
		int t = chtype(x), ty = chtype(y);
		c[y][t] = c[x][t ^ 1]; if(c[x][t ^ 1]) fa[c[x][t ^ 1]] = y;
		c[x][t ^ 1] = y, fa[y] = x;
		fa[x] = z; if(z) c[z][ty] = x;
	}
	void splay(int x, int to = 0) { for(rt = x; fa[x] != to; rotate(x)) if(fa[fa[x]] != to) rotate(chtype(x) == chtype(fa[x]) ? fa[x] : x); }
} origin, splay;
int dep[N];
int depth(int x) { return splay.fa[x] == 0 ? 0 : depth(splay.fa[x]) + 1; }

int ans[N];

int main() {
#ifndef DEBUG
	freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int ls, rs;
		scanf("%d%d", &ls, &rs);
		if(ls) origin.c[i][0] = ls, origin.fa[ls] = i;
		if(rs) origin.c[i][1] = rs, origin.fa[rs] = i;
	}
	for(int i = 1; i <= n; i++) {
		splay = origin;
		splay.splay(i);
		for(int j = 1; j <= n; j++) dep[j] = 0;
		for(int j = 1; j <= n; j++) ans[j] += depth(j);
	}
	for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}