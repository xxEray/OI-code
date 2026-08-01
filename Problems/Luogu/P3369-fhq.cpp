#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

struct FHQ {
	int c[N][2], v[N], w[N], sz[N];
	int tot, rt;
	void init() { tot = 0; }
	int random() { static int seed = 122412352; return seed *= 2150501125; }
	int nw(int key) { tot++, w[tot] = random(), v[tot] = key, sz[tot] = 1; return tot; }
	void pushup(int x) { sz[x] = sz[c[x][0]] + sz[c[x][1]] + 1; }
	void split(int root, int key, int &x, int &y) {
		if(!root) x = y = 0;
		else if(v[root] <= key) x = root, split(c[root][1], key, c[x][1], y), pushup(x);
		else y = root, split(c[root][0], key, x, c[y][0]), pushup(y);
	}
	int merge(int x, int y) {
		if(!x || !y) return x ^ y;
		else if(w[x] > w[y]) { c[x][1] = merge(c[x][1], y), pushup(x); return x;}
		else { c[y][0] = merge(x, c[y][0]), pushup(y); return y; }
	}
	void insert(int key) {
		int x, y;
		split(rt, key - 1, x, y);
		rt = merge(merge(x, nw(key)), y);
	}
	void remove(int key) {
		int x, y, z;
		split(rt, key, x, z);
		split(x, key - 1, x, y);
		if(y) y = merge(c[y][0], c[y][1]);
		rt = merge(merge(x, y), z);
	}
	int rank(int key) {
		int x, y, ans;
		split(rt, key - 1, x, y);
		ans = sz[x] + 1;
		rt = merge(x, y);
		return ans;
	}
	int at(int ind) {
		int now = rt;
		while(now)
			if(ind <= sz[c[now][0]]) now = c[now][0];
			else if(ind == sz[c[now][0]] + 1) return v[now];
			else ind -= sz[c[now][0]] + 1, now = c[now][1];
		return v[now];
	}
	int prev(int key) {
		int x, y, now, ans;
		split(rt, key - 1, x, y);
		now = x;
		while(c[now][1]) now = c[now][1];
		ans = v[now];
		rt = merge(x, y);
		return ans;
	}
	int next(int key) {
		int x, y, now, ans;
		split(rt, key, x, y);
		now = y;
		while(c[now][0]) now = c[now][0];
		ans = v[now];
		rt = merge(x, y);
		return ans;
	}
	int size() { return sz[rt]; }
} treap;

int main() {
	int Q;
	scanf("%d", &Q);
	while(Q--) {
		int t, x;
		scanf("%d%d", &t, &x);
		if(t == 1) treap.insert(x);
		else if(t == 2) treap.remove(x);
		else if(t == 3) printf("%d\n", treap.rank(x));
		else if(t == 4) printf("%d\n", treap.at(x));
		else if(t == 5) printf("%d\n", treap.prev(x));
		else if(t == 6) printf("%d\n", treap.next(x));
	}
	return 0;
}