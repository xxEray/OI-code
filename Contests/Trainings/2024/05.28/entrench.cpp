#include <bits/stdc++.h>

const int N = 4e5 + 5;

int n, Q, Type;
int a[N];

int c[N][2], fa[N];
int root;
bool chtype(int x) { return x == c[fa[x]][1]; }

struct LCT {
	int c[N][2], v[N], sz[N], sum[N], fa[N];
	int stk[N];
	bool r[N];
	int chtype(int x) { return x == c[fa[x]][1]; }
	void pushup(int x) { sz[x] = sz[c[x][0]] + sz[c[x][1]] + 1, sum[x] = sum[c[x][0]] + sum[c[x][1]] + v[x]; }
	void pushr(int x) { if(x) r[x] ^= 1, std::swap(c[x][0], c[x][1]); }
	void pushdown(int x) { if(r[x]) pushr(c[x][0]), pushr(c[x][1]), r[x] = 0; }
	bool nroot(int x) { return c[fa[x]][0] == x || c[fa[x]][1] == x; }
	void rotate(int x) {
		int y = fa[x], z = fa[y], t = chtype(x), ty = chtype(y);
		c[y][t] = c[x][!t]; if(c[x][!t]) fa[c[x][!t]] = y;
		fa[x] = z; if(nroot(y)) c[z][ty] = x;
		c[x][!t] = y, fa[y] = x;
		pushup(y), pushup(x);
	}
	void splay(int x) {
		int y = x, top = 0;
		stk[++top] = y;
		while(nroot(y)) stk[++top] = y = fa[y];
		while(top) pushdown(stk[top--]);
		for(; nroot(x); rotate(x)) if(nroot(fa[x])) rotate(chtype(x) == chtype(fa[x]) ? fa[x] : x);
	}
	void access(int x) { for(int y = 0; x; y = x, x = fa[x]) splay(x), c[x][1] = y, pushup(x); }
	int findroot(int x) {
		access(x), splay(x);
		while(c[x][0]) pushdown(x), x = c[x][0];
		splay(x);
		return x;
	}
	void makeroot(int x) { access(x), splay(x), pushr(x); }
	void split(int x, int y) { makeroot(x), access(y), splay(y); }
	void link(int x, int y) { makeroot(x); if(findroot(y) != x) fa[x] = y; else assert(false); }
	void cut(int x, int y) {
		makeroot(x);
		if(findroot(y) == x && fa[y] == x && !c[y][0]) fa[y] = c[x][1] = 0, pushup(x);
		else assert(false);
	}
	void modify(int x, int val) { access(x), splay(x), v[x] = val, pushup(x); }
} lct;

void rotate(int x) {
	int y = fa[x], z = fa[y], t = chtype(x), ty = chtype(y);
	lct.cut(x, y), lct.cut(x, c[x][!t]);
	if(z) lct.cut(y, z);
	c[y][t] = c[x][!t], fa[c[x][!t]] = y, lct.modify(c[x][!t], t), lct.link(y, c[x][!t]);
	fa[x] = z; if(z) c[z][ty] = x, lct.modify(x, ty), lct.link(x, z);
	c[x][!t] = y, fa[y] = x, lct.modify(y, !t), lct.link(x, y);
}

int main() {
	// freopen("entrench.in", "r", stdin);
	// freopen("entrench.out", "w", stdout);
	scanf("%d%d%d", &n, &Q, &Type);
	for(int i = 1; i <= 2 * n - 1; i++) {
		int l, r, L, R;
		scanf("%d%d%d%d", &l, &r, &L, &R);
		if(l == 1 && r == n) root = i;
		if(l == r) a[l] = i;
		c[i][0] = L, c[i][1] = R, fa[L] = i, fa[R] = i;
		if(L) lct.modify(L, 0), lct.link(i, L);
		if(R) lct.modify(R, 1), lct.link(i, R);
	}
	// for(int i = 1; i <= 2 * n - 1; i++)
	// 	printf("%d: ls = %d, rs = %d, fa = %d, v = %d, sum = %d, sz = %d, r = %d\n", i, lct.c[i][0], lct.c[i][1], lct.fa[i], lct.v[i], lct.sum[i], lct.sz[i], lct.r[i]);
	int lastans = 0;
	while(Q--) {
		int t, x, l, r;
		scanf("%d", &t);
		if(t == 1) {
			scanf("%d", &x);
			x = (x + lastans * Type) % (n - 1) + 1;
			if(x == root) continue;
			if(fa[x] == root) root = x;
			rotate(x);
		} else {
			scanf("%d%d", &l, &r);
			l = (l + lastans * Type) % n + 1, r = (r + lastans * Type) % n + 1;
			if(l > r) std::swap(l, r);
			if(l == 1 && r == n) { lastans = 1; puts("1"); continue; }
			int ret = 0, lca;
			l--, r++;
			l = (l == 0 ? 0 : a[l]), r = (r == n + 1 ? 0 : a[r]);
			if(!l || !r) lca = root;
			else {
				ret -= 2;
				lct.makeroot(root);
				lct.access(l), lct.access(r), lct.splay(l);
				if(lct.fa[l]) lca = lct.fa[l];
				else lca = l;
			}
			// printf("lca = %d, l = %d, r = %d\n", lca, l, r);
			if(l) {
				lct.split(l, lca);
				ret += lct.sz[lca] - lct.sum[lca];
				ret -= (lct.v[lca] == 0);
			}
			if(r) {
				lct.split(r, lca);
				ret += lct.sum[lca];
				ret -= (lct.v[lca] == 1);
			}
			lastans = ret;
			printf("%d\n", ret);
		}
		// for(int i = 1; i <= 2 * n - 1; i++)
		// 	printf("%d: ls = %d, rs = %d, fa = %d, v = %d, sum = %d, sz = %d, r = %d\n", i, lct.c[i][0], lct.c[i][1], lct.fa[i], lct.v[i], lct.sum[i], lct.sz[i], lct.r[i]);
	}
	return 0;
} /*
4 2 0
1 4 4 2
2 4 5 3
3 4 6 7
1 1 0 0
2 2 0 0
3 3 0 0
4 4 0 0
2 1 2
1 2

*/