#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>

const int N = 3e5 + 5;

int Q;

struct FHQ {
	int c[N][2], sz[N], v[N], w[N];
	int root, tot;
	int nw(int val) { tot++, c[tot][0] = c[tot][1] = 0, w[tot] = rand() * rand(), v[tot] = val, sz[tot] = 1; return tot; }
	void pushup(int x) { sz[x] = sz[c[x][0]] + sz[c[x][1]] + 1; }
	int merge(int x, int y) {
		if(!x || !y) return x ^ y;
		if(w[x] < w[y]) { c[x][1] = merge(c[x][1], y), pushup(x); return x; }
		else { c[y][0] = merge(x, c[y][0]), pushup(y); return y; }
	}
	void splitv(int rt, int val, int &x, int &y) {
		if(!rt) { x = y = 0; return; }
		if(v[rt] <= val) x = rt, splitv(c[x][1], val, c[x][1], y), pushup(x);
		else y = rt, splitv(c[y][0], val, x, c[y][0]), pushup(y);
	}
	void splits(int rt, int s, int &x, int &y) {
		if(!rt) { x = y = 0; return; }
		if(s <= sz[c[rt][0]]) y = rt, splits(c[y][0], s, x, c[y][0]), pushup(y);
		else x = rt, splits(c[x][1], s - sz[c[rt][0]] - 1, c[x][1], y), pushup(x);
	}
	void insert(int val) {
		int x, y;
		splitv(root, val - 1, x, y);
		root = merge(x, merge(nw(val), y));
	}
	void erase_once(int val) {
		int x, y, z;
		splitv(root, val - 1, x, y), splitv(y, val, y, z);
		if(y) y = merge(c[y][0], c[y][1]);
		root = merge(x, merge(y, z));
	}
	int smaller_count(int val) {
		int x, y;
		splitv(root, val - 1, x, y);
		int ret = sz[x];
		root = merge(x, y);
		return ret;
	}
	int at(int k) {
		int x, y, z;
		splits(root, k - 1, x, y), splits(y, 1, y, z);
		int ret = v[y];
		root = merge(x, merge(y, z));
		return ret;
	}
	int prev(int val) {
		int x, y, z;
		splitv(root, val - 1, x, z), splits(x, sz[x] - 1, x, y);
		int ret = y ? v[y] : -1;
		root = merge(x, merge(y, z));
		return ret;
	}
	int next(int val) {
		int x, y, z;
		splitv(root, val, x, y), splits(y, 1, y, z);
		int ret = y ? v[y] : -1;
		root = merge(x, merge(y, z));
		return ret;
	}
} treap;

int main() {
#ifndef DEBUG
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
#endif
	srand(time(0));
	scanf("%d", &Q);
	while(Q--) {
		int t, x;
		scanf("%d%d", &t, &x);
		if(t == 0) treap.insert(x);
		else if(t == 1) treap.erase_once(x);
		else if(t == 2) printf("%d\n", treap.at(x));
		else if(t == 3) printf("%d\n", treap.smaller_count(x));
		else if(t == 4) printf("%d\n", treap.prev(x));
		else if(t == 5) printf("%d\n", treap.next(x));
	}
	return 0;
}