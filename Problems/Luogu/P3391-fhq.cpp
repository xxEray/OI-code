#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, Q;

struct FHQ {
	int ls[N], rs[N], t[N], w[N], lazy[N], v[N], sz[N];
	int tot, root;
	int nw(int val) { tot++; ls[tot] = rs[tot] = t[tot] = lazy[tot] = 0, v[tot] = val, w[tot] = rand() << 15 | rand(); pushup(tot); return tot; }
	void pushup(int x) { sz[x] = sz[ls[x]] + sz[rs[x]] + 1; }
	void setlazy(int x) { std::swap(ls[x], rs[x]); lazy[x] ^= 1; }
	void pushdown(int x) { if(x && lazy[x]) setlazy(ls[x]), setlazy(rs[x]), lazy[x] = 0; }
	int merge(int x, int y) {
		// printf("merge %d %d\n", x, y);
		if(!x || !y) return x ^ y;
		if(w[x] > w[y]) { pushdown(x), rs[x] = merge(rs[x], y), pushup(x); return x; }
		else { pushdown(y), ls[y] = merge(x, ls[y]), pushup(y); return y; }
	}
	void split(int rt, int vc, int &x, int &y) {
		// printf("split(%d, %d)\n", rt, vc);
		if(!rt) { x = y = 0; return; }
		if(vc <= sz[ls[rt]]) y = rt, pushdown(y), split(ls[rt], vc, x, ls[y]), pushup(y);
		else x = rt, pushdown(x), split(rs[rt], vc - sz[ls[rt]] - 1, rs[x], y), pushup(x);
	}
	void insert(int pos, int val) {
		int x, y;
		split(root, pos - 1, x, y);
		root = merge(x, merge(nw(val), y));
	}
	void reverse(int l, int r) {
		int x, y, z;
		split(root, l - 1, x, y), split(y, r - l + 1, y, z);
		setlazy(y);
		root = merge(x, merge(y, z));
	}
	int get(int pos) {
		int x, y, z;
		split(root, pos - 1, x, y), split(y, 1, y, z);
		int ret = v[y];
		root = merge(x, merge(y, z));
		return ret;
	}
} treap;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) treap.insert(i, i);
	while(Q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		treap.reverse(l, r);
	}
	for(int i = 1; i <= n; i++) printf("%d ", treap.get(i));
	puts("");
	return 0;
}