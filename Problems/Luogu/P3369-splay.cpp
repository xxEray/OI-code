#include <cstdio>
#include <algorithm>

const int N = 1.1e6 + 5;

int n, Q;
int ans, last;

struct Splay {
	int c[N][2], fa[N], val[N], cnt[N], sz[N];
	int tot, rt;
	int chtype(int x) { return x == c[fa[x]][1]; }
	void pushup(int x) { sz[x] = sz[c[x][0]] + sz[c[x][1]] + cnt[x]; }
	void clear(int x) { c[x][0] = c[x][1] = fa[x] = val[x] = cnt[x] = sz[x] = 0; }
	void rotate(int x) {
		int y = fa[x], z = fa[y], t = chtype(x), ty = chtype(y);
		c[y][t] = c[x][t ^ 1], fa[c[x][t ^ 1]] = (c[x][t ^ 1] ? y : 0);
		c[x][t ^ 1] = y, fa[y] = x;
		c[z][ty] = (z ? x : 0), fa[x] = z;
		pushup(y), pushup(x);
	}
	void splay(int x) { for(rt = x; fa[x]; rotate(x)) if(fa[fa[x]]) rotate(chtype(x) == chtype(fa[x]) ? fa[x] : x); }
	void insert(int x) {
		if(!rt) { tot++; val[tot] = x, sz[tot] = cnt[tot] = 1, rt = tot; return; }
		int now = rt;
		while(true) {
			if(val[now] == x) { cnt[now]++, splay(now); return; }
			int f = now;
			now = c[now][x > val[now]];
			if(!now) { tot++; val[tot] = x, cnt[tot] = 1, fa[tot] = f, c[f][x > val[f]] = tot, splay(tot); return; }
		}
	}
	void del(int x) {
		rank(x), x = rt;
		if(cnt[x] > 1) { cnt[x]--, sz[x]--; return; }
		if(!c[x][0] || !c[x][1]) { rt = c[x][c[x][0] ? 0 : 1], fa[rt] = 0, clear(x); return; }
		int now = c[x][0];
		while(c[now][1]) now = c[now][1];
		splay(now);
		c[now][1] = c[x][1], fa[c[x][1]] = now;
		rt = now;
		clear(x);
	}
	int rank(int x) {
		int now = rt, ret = 0;
		while(now) {
			if(val[now] == x) { ret += sz[c[now][0]] + 1, splay(now); return ret; }
			else if(x < val[now]) now = c[now][0];
			else ret += sz[c[now][0]] + cnt[now], now = c[now][1];
		}
		return ret + 1;
	}
	int kth(int x) {
		int now = rt;
		while(true) {
			if(x <= sz[c[now][0]]) now = c[now][0];
			else if(x <= sz[c[now][0]] + cnt[now]) { splay(now); return val[now]; }
			else x -= sz[c[now][0]] + cnt[now], now = c[now][1];
		}
	}
	int pre(int x) {
		insert(x);
		int now = c[rt][0];
		while(c[now][1]) now = c[now][1];
		int ret = val[now];
		del(x);
		return ret;
	}
	int nxt(int x) {
		insert(x);
		int now = c[rt][1];
		while(c[now][0]) now = c[now][0];
		int ret = val[now];
		del(x);
		return ret;
	}
} splay;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1, x; i <= n; i++) scanf("%d", &x), splay.insert(x);
	last = ans = 0;
	while(Q--) {
		int t, x;
		scanf("%d%d", &t, &x);
		x ^= last;
		// printf("opt: %d %d", t, x);
		if(t == 1) splay.insert(x);
		else if(t == 2) splay.del(x);
		else if(t == 3) last = splay.rank(x), ans ^= last;
		else if(t == 4) last = splay.kth(x), ans ^= last;
		else if(t == 5) last = splay.pre(x), ans ^= last;
		else if(t == 6) last = splay.nxt(x), ans ^= last;
		// if(t >= 3) printf(", ans: %d\n", last); else puts("");
	}
	printf("%d\n", ans);
	return 0;
}