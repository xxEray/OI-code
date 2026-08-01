#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

struct Splay {
	int val[N];
	int cnt[N], sz[N], fa[N], c[N][2];
	int rev[N];
	int tot, rt;
	int create(int v) { int id = ++tot; sz[id] = cnt[id] = 1, val[id] = v; return id; }
	void pushup(int x) { sz[x] = sz[c[x][0]] + sz[c[x][1]] + cnt[x]; }
	void set_tag(int x, int r) { if(r) rev[x] ^= 1, std::swap(c[x][0], c[x][1]); }
	void pushdown(int x) { if(rev[x]) set_tag(c[x][0], 1), set_tag(c[x][1], 1), rev[x] = 0; }
	int chtype(int x) { return c[fa[x]][1] == x; }
	void rotate(int x) {
		int y = fa[x], z = fa[y];
		pushdown(z), pushdown(y);
		int t = chtype(x), ty = chtype(y);
		c[y][t] = c[x][t ^ 1]; if(c[x][t ^ 1]) fa[c[x][t ^ 1]] = y;
		c[x][t ^ 1] = y, fa[y] = x;
		fa[x] = z; if(z) c[z][ty] = x;
		pushup(y), pushup(x);
	}
	void splay(int x, int to = 0) { for(rt = x; fa[x] != to; rotate(x)) if(fa[fa[x]] != to) rotate(chtype(x) == chtype(fa[x]) ? fa[x] : x); }
	void insert(int v) {
		if(!rt) { rt = create(v); return; }
		int now = rt;
		while(true) {
			if(val[now] == v) { cnt[now]++; pushup(now), splay(now); break; }
			pushdown(now);
			int o = now;
			now = c[now][val[now] < v];
			if(!now) { now = create(v); fa[now] = o, c[o][val[o] < v] = now; pushup(now), splay(now); break; }
		}
	}
	int find(int k) {
		int now = rt;
		while(now) {
			pushdown(now);
			if(k <= sz[c[now][0]]) { now = c[now][0]; continue; }
			k -= sz[c[now][0]];
			if(k <= cnt[now]) { splay(now); return now; }
			k -= cnt[now];
			now = c[now][1];
		}
		return -1;
	}
	void reverse(int l, int r) {
		l = find(l), r = find(r + 2);
		splay(l), splay(r, l);
		pushdown(r);
		int now = c[r][0];
		set_tag(now, 1);
	}
} splay;

int n, m;

int main() {
	scanf("%d%d", &n, &m);
	splay.insert(0);
	for(int i = 1; i <= n; i++) splay.insert(i);
	splay.insert(n + 1);
	for(int i = 1; i <= m; i++) { int l, r; scanf("%d%d", &l, &r); splay.reverse(l, r); }
	for(int i = 1; i <= n; i++) printf("%d ", splay.val[splay.find(i + 1)]);
	return 0;
}