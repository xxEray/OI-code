#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, Q;

struct Splay {
	int c[N][2], fa[N], v[N], sz[N], lazy[N];
	int tot, root;
	int chtype(int x) { return x == c[fa[x]][1]; }
	void setlazy(int x) { lazy[x] ^= 1, std::swap(c[x][0], c[x][1]); }
	void pushdown(int x) { if(x && lazy[x]) setlazy(c[x][0]), setlazy(c[x][1]), lazy[x] = 0; }
	void pushup(int x) { sz[x] = sz[c[x][0]] + sz[c[x][1]] + 1; }
	int nw(int val) { tot++; c[tot][0] = c[tot][1] = fa[tot] = 0; v[tot] = val; pushup(tot); return tot; }
	void rotate(int x) {
		int y = fa[x], z = fa[y];
		pushdown(x), pushdown(y);
		int t = chtype(x), ty = chtype(y);
		fa[c[x][!t]] = y, c[y][t] = c[x][!t];
		c[x][!t] = y, fa[y] = x;
		fa[x] = z; if(z) c[z][ty] = x;
		pushup(y), pushup(x);
	}
	void splay(int x, int to = 0) { if(to == 0) root = x; for(; fa[x] != to; rotate(x)) if(fa[fa[x]] != to) rotate(chtype(x) == chtype(fa[x]) ? fa[x] : x);  }
	int find(int k) {
		// printf("root = %d, size = %d, at(%d)\n", root, sz[root], k);
		int now = root;
		while(true) {
			pushdown(now);
			if(k <= sz[c[now][0]]) now = c[now][0];
			else if(k == sz[c[now][0]] + 1) break;
			else k -= sz[c[now][0]] + 1, now = c[now][1];
		}
		return now;
	}
	void insert(int pos, int val) {
		if(!root) { root = nw(val); return; }
		if(pos == sz[root] + 1) { splay(find(pos - 1)); c[root][1] = nw(val); fa[c[root][1]] = root; pushup(root); splay(c[root][1]); return; }
		int x = find(pos - 1), y = find(pos);
		splay(x), splay(y, root);
		pushdown(c[root][1]);
		c[c[root][1]][0] = nw(val), fa[c[c[root][1]][0]] = c[root][1];
		pushup(c[root][1]), pushup(root);
		splay(c[c[root][1]][0]);
	}
	void reverse(int l, int r) {
		int x = find(l - 1), y = find(r + 1);
		splay(x), splay(y, root);
		pushdown(c[root][1]);
		assert(sz[c[c[root][1]][0]] == r - l + 1);
		setlazy(c[c[root][1]][0]);
		splay(c[c[root][1]][0]);
	}
	int get(int k) { int x = find(k); splay(x); return v[x]; }
} splay;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 0; i <= n + 1; i++) splay.insert(i + 1, i);
	while(Q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		splay.reverse(l + 1, r + 1);
		// for(int i = 1; i <= n; i++) printf("%d ", splay.get(i + 1));
		// puts("");
	}
	for(int i = 1; i <= n; i++) printf("%d ", splay.get(i + 1));
	puts("");
	return 0;
}