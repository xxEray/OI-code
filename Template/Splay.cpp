const int N = 1e6 + 5; // dot count
typedef long long LL;
struct Splay {
	LL val[N];
	int cnt[N], sz[N], fa[N], c[N][2];
	// LL lazy[N];
	int stk[N], top;
	int tot, rt;
	int create(LL v) { int id = top ? stk[--top] : ++tot; sz[id] = cnt[id] = 1, val[id] = v; return id; }
	void pushup(int x) { sz[x] = sz[c[x][0]] + sz[c[x][1]] + cnt[x]; }
	void pushdown(int x) {}
	int chtype(int x) { return c[fa[x]][1] == x; }
	void destroy(int x) { stk[top++] = x; val[x] = LL(); cnt[x] = sz[x] = fa[x] = c[x][0] = c[x][1] = 0; }
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
	void insert(LL v) {
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
	int rank(LL v) {
		int now = rt, ret = 0;
		while(now) {
			pushdown(now);
			if(v < val[now]) { now = c[now][0]; continue; }
			ret += sz[c[now][0]];
			if(v == val[now]) { splay(now); return ret + 1; }
			ret += cnt[now];
			now = c[now][1];
		}
		return -1;
	}
	int find(LL v) { return rank(v) == -1 ? -1 : rt; }
	LL at(int k, LL illegal = -1) {
		int now = rt;
		while(now) {
			pushdown(now);
			if(k <= sz[c[now][0]]) { now = c[now][0]; continue; }
			k -= sz[c[now][0]];
			if(k <= cnt[now]) { splay(now); return val[now]; }
			k -= cnt[now];
			now = c[now][1];
		}
		return illegal;
	}
	LL prev(LL v) {
		insert(v);
		int now = c[rt][0];
		while(c[now][1]) pushdown(now), now = c[now][1];
		remove(v, 1);
		return val[now];
	}
	LL next(LL v) {
		insert(v);
		int now = c[rt][1];
		while(c[now][0]) pushdown(now), now = c[now][0];
		remove(v, 1);
		return val[now];
	}
	// opition: 0 -> all, other -> at most x times
	// return: the number of LLs removed
	int remove(LL v, int opition = 0) {
		if(find(v) == -1) return 0;
		if(opition && cnt[rt] > opition) { cnt[rt] -= opition; pushup(rt); return opition; }
		int res = cnt[rt], ls = c[rt][0], rs = c[rt][1]; destroy(rt);
		if(!ls || !rs) { rt = ls ^ rs, fa[rt] = 0; return res; }
		int now = ls;
		while(c[now][1]) pushdown(now), now = c[now][1];
		splay(now);
		c[now][1] = rs, fa[rs] = now;
		rt = now;
		pushup(rt);
		return res;
	}
};