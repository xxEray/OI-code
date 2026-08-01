#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n, Q;

struct LCT {
	int c[N][2], fa[N], v[N], s[N];
	int stk[N];
	bool r[N];
	int chtype(int x) { return x == c[fa[x]][1]; }
	void pushup(int x) { s[x] = v[x] ^ s[c[x][0]] ^ s[c[x][1]]; }
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
	void makeroot(int x) { access(x), splay(x), pushr(x); }
	int findroot(int x) {
		access(x), splay(x);
		while(c[x][0]) pushdown(x), x = c[x][0];
		splay(x);
		return x;
	}
	void split(int x, int y) { makeroot(x), access(y), splay(y); }
	void link(int x, int y) { makeroot(x); if(findroot(y) != x) fa[x] = y; }
	void cut(int x, int y) {
		makeroot(x);
		if(findroot(y) == x && fa[y] == x && !c[y][0]) fa[y] = c[x][1] = 0, pushup(x);
	}
} lct;

int main() {
	// freopen("P3690_8.in", "r", stdin);
	// freopen("P3690_8.out", "w", stdout);
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &lct.v[i]);
	while(Q--) {
		int t, x, y;
		scanf("%d%d%d", &t, &x, &y);
		if(t == 0) lct.split(x, y), printf("%d\n", lct.s[y]);
		else if(t == 1) lct.link(x, y);
		else if(t == 2) lct.cut(x, y);
		else if(t == 3) lct.splay(x), lct.v[x] = y;
	}
	return 0;
} /*
3 8
1 2 4
1 1 2
1 2 3
2 1 2
2 2 3
1 1 3
1 3 2
0 1 2 :ans=7
*/