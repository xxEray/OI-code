#include <bits/stdc++.h>

const int N = 1e5 + 5;

struct Treap {
	int v[N], w[N], sz[N], ls[N], rs[N];
	int root;
	int nw(int val) { static int cnt = 0; cnt++; v[cnt] = val, w[cnt] = rand() << 15 | rand(), sz[cnt] = 1, ls[cnt] = 0, rs[cnt] = 0; return cnt; }
	void pushup(int x) { sz[x] = sz[ls[x]] + sz[rs[x]] + 1; }
	int merge(int x, int y) {
		if(!x || !y) return x ^ y;
		if(w[x] > w[y]) { rs[x] = merge(rs[x], y), pushup(x); return x; }
		else { ls[y] = merge(x, ls[y]), pushup(y); return y; }
	}
	void splitv(int rt, int val, int &x, int &y) {
		if(!rt) { x = y = 0; return; }
		if(v[rt] > val) y = rt, splitv(ls[rt], val, x, ls[y]), pushup(y);
		else x = rt, splitv(rs[rt], val, rs[x], y), pushup(x);
	}
	void splits(int rt, int size, int &x, int &y) {
		if(!rt) { x = y = 0; return; }
		if(size <= sz[ls[rt]]) y = rt, splits(ls[rt], size, x, ls[y]), pushup(y);
		else x = rt, splits(rs[rt], size - sz[ls[rt]] - 1, rs[x], y), pushup(x);
	}
	void insert(int val) {
		int x, y;
		splitv(root, val, x, y);
		root = merge(x, merge(nw(val), y));
	}
	void erase(int val) {
		int x, y, z;
		splitv(root, val - 1, x, y);
		splitv(y, val, y, z);
		if(y) y = merge(ls[y], rs[y]);
		root = merge(x, merge(y, z));
	}
	int rank(int val) {
		int x, y;
		splitv(root, val - 1, x, y);
		int ret = sz[x] + 1;
		root = merge(x, y);
		return ret;
	}
	int at(int k) {
		int x, y, z;
		splits(root, k - 1, x, y);
		splits(y, 1, y, z);
		int ret = v[y];
		root = merge(x, merge(y, z));
		return ret;
	}
	int pre(int val) {
		int x, y, z;
		splitv(root, val - 1, y, z);
		splits(y, sz[y] - 1, x, y);
		int ret = v[y];
		root = merge(x, merge(y, z));
		return ret;
	}
	int nxt(int val) {
		int x, y, z;
		splitv(root, val, x, y);
		splits(y, 1, y, z);
		int ret = v[y];
		root = merge(x, merge(y, z));
		return ret;
	}
} treap;

int main() {
	int n;
	scanf("%d", &n);
	while(n--) {
		int t, x;
		scanf("%d%d", &t, &x);
		if(t == 1) treap.insert(x);
		else if(t == 2) treap.erase(x);
		else if(t == 3) printf("%d\n", treap.rank(x));
		else if(t == 4) printf("%d\n", treap.at(x));
		else if(t == 5) printf("%d\n", treap.pre(x));
		else if(t == 6) printf("%d\n", treap.nxt(x));
	}
	return 0;
} /*
4
1 1
1 2
5 2
*/