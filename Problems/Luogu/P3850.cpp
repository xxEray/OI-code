#include <cstdio>
#include <algorithm>
#include <string>

const int N = 1.2e5 + 5;

int n, m, Q;

char tmp[20];
std::string str;

struct FHQ {
	int c[N][2], w[N], sz[N];
	int tot, rt;
	std::string v[N];
	int random() { static int seed = 1353124125; return seed *= 31413521521; }
	int nw(const std::string &key) { tot++, c[tot][0] = c[tot][1] = 0, w[tot] = random(), sz[tot] = 1, v[tot] = key; return tot; }
	void pushup(int x) { sz[x] = sz[c[x][0]] + sz[c[x][1]] + 1; }
	void split(int root, int size, int &x, int &y) {
		if(!root) x = y = 0;
		else if(size <= sz[c[root][0]]) y = root, split(c[root][0], size, x, c[y][0]), pushup(y);
		else x = root, split(c[root][1], size - (sz[c[root][0]] + 1), c[x][1], y), pushup(x);
	}
	int merge(int x, int y) {
		if(!x || !y) return x ^ y;
		else if(w[y] > w[x]) { c[y][0] = merge(x, c[y][0]), pushup(y); return y; }
		else { c[x][1] = merge(c[x][1], y), pushup(x); return x; }
	}
	void insert(const std::string &key, int ind) {
		int x, y;
		split(rt, ind - 1, x, y);
		rt = merge(merge(x, nw(key)), y);
	}
	const std::string &query(int ind) {
		int x, y, z;
		split(rt, ind - 1, x, y);
		split(y, 1, y, z);
		const std::string &ans = v[y];
		rt = merge(x, merge(y, z));
		return ans;
	}
} treap;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%s", tmp), str = tmp, treap.insert(str, i);
	scanf("%d", &m);
	for(int i = 1, d; i <= m; i++) scanf("%s%d", tmp, &d), str = tmp, treap.insert(str, d + 1);
	scanf("%d", &Q);
	for(int d; Q--;) scanf("%d", &d), puts(treap.query(d + 1).c_str());
	return 0;
}