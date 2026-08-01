#include <bits/stdc++.h>

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

struct FHQ {
	int v[N], w[N], sz[N], mn[N], ls[N], rs[N];
	int root, tot;
	FHQ() { mn[0] = INF; }
	int nw(int val) { tot++; ls[tot] = rs[tot] = 0, sz[tot] = 1, v[tot] = val, w[tot] = rand() << 15 | rand(), mn[tot] = v[tot]; return tot; }
	void pushup(int x) {
		sz[x] = sz[ls[x]] + sz[rs[x]] + 1;
		mn[x] = std::min({mn[ls[x]] + sz[rs[x]] + 1, v[x] + sz[rs[x]], mn[rs[x]]});
	}
	int merge(int x, int y) {
		if(!x || !y) return x ^ y;
		if(w[x] > w[y]) { rs[x] = merge(rs[x], y), pushup(x); return x; }
		else { ls[y] = merge(x, ls[y]), pushup(y); return y; }
	}
	void splitv(int rt, int val, int &x, int &y) {
		if(!rt) { x = y = 0; return; }
		if(v[rt] <= val) x = rt, splitv(rs[rt], val, rs[x], y), pushup(x);
		else y = rt, splitv(ls[rt], val, x, ls[y]), pushup(y);
	}
	void splits(int rt, int s, int &x, int &y) {
		if(!rt) { x = y = 0; return; }
		if(sz[ls[rt]] + 1 <= s) x = rt, splits(rs[rt], s - sz[ls[rt]] - 1, rs[x], y), pushup(x);
		else y = rt, splits(ls[rt], s, x, ls[y]), pushup(y);
	}
	void insert(int val) {
		if(!root) { root = nw(val); return; }
		int x, y;
		splitv(root, val - 1, x, y);
		root = merge(x, merge(nw(val), y));
	}
	int getmin(int l) { // suffix(l)
		int x, y;
		splits(root, l - 1, x, y);
		int ret = mn[y];
		root = merge(x, y);
		return ret;
	}
	int get(int p) {
		int x, y, z;
		splits(root, p - 1, x, y), splits(y, 1, y, z);
		int ret = v[y];
		root = merge(x, merge(y, z));
		return ret;
	}
} treap;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int id = 0;
	for(int i = 1; i <= n; i++) {
		treap.insert(a[i]);
		while(id > 0 && treap.get(id) + id > 0) id--;
		while(id < i && treap.get(id + 1) + id + 1 <= 0) id++;
		// printf("id = %d\n", id);
		printf("%d\n", std::min(i - 2 * id, id == i ? INF : treap.getmin(id + 1)));
	}
	return 0;
}