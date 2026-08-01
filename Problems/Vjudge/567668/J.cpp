#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const int M = 2e5 + 5;

int n, m;
char s[N];

struct Query { int l, r, id; } a[M];

struct SAM {
	struct State { int len, link; std::map<int, int> next; } t[N << 1];
	int tot, last;
	SAM() : tot(1), last(1) { t[1].len = 0, t[1].link = 0, t[1].next.clear(); }
	void init() { tot = 1, last = 1, t[1].len = 0, t[1].link = 0, t[1].next.clear(); }
	void insert(int c) {
		int cur = ++tot, p = last;
		t[cur].len = t[last].len + 1, t[cur].next.clear();
		last = cur;
		for(; p && !t[p].next[c]; p = t[p].link) t[p].next[c] = cur;
		if(!p) t[cur].link = 1;
		else {
			int q = t[p].next[c];
			if(t[p].len + 1 == t[q].len) t[cur].link = q;
			else {
				int clone = ++tot;
				t[clone].len = t[p].len + 1;
				t[clone].link = t[q].link, t[q].link = clone;
				t[clone].next = t[q].next;
				t[cur].link = clone;
				for(; p && t[p].next[c] == q; p = t[p].link) t[p].next[c] = clone;
			}
		}
	}
} sam;

LL out[M];

struct BIT {
	LL t1[N], t2[N];
	void add(int x, LL v) { int o = x; while(x <= n) t1[x] += v, t2[x] += o * v, x += x & -x; }
	void add(int l, int r, LL v) { assert(1 <= l), assert(l <= r), assert(r <= n); /* printf("add [%d, %d] %lld\n", l, r, v);  */add(l, v), add(r + 1, -v); }
	LL query(int r) { int o = r + 1; LL ret = 0; while(r) ret += o * t1[r] - t2[r], r -= r & -r; return ret; }
	LL query(int l, int r) { assert(1 <= l && l <= r && r <= n); /* printf("query [%d, %d] = %lld\n", l, r, query(r) - query(l - 1));  */return query(r) - query(l - 1); }
} bit;

struct LCT {
	int c[N << 1][2], fa[N << 1], last[N << 1], tagl[N << 1];
	int stk[N << 1];
	int chtype(int x) { return x == c[fa[x]][1]; }
	void pushlast(int x, int v) { if(x && v) /* printf("last[%d] = %d\n", x, v),  */last[x] = tagl[x] = v; }
	void pushup(int x) {}
	void pushdown(int x) { if(tagl[x]) pushlast(c[x][0], tagl[x]), pushlast(c[x][1], tagl[x]), tagl[x] = 0; }
	bool nroot(int x) { return c[fa[x]][0] == x || c[fa[x]][1] == x; }
	void rotate(int x) {
		int y = fa[x], z = fa[y], t = chtype(x), ty = chtype(y);
		c[y][t] = c[x][!t]; if(c[x][!t]) fa[c[x][!t]] = y;
		fa[x] = z; if(nroot(y)) c[z][ty] = x;
		c[x][!t] = y, fa[y] = x;
		pushup(y), pushup(x);
	}
	void splay(int x) {
		int y = x, top = 0;
		stk[++top] = y;
		while(nroot(y)) stk[++top] = y = fa[y];
		while(top) pushdown(stk[top--]);
		for(; nroot(x); rotate(x)) if(nroot(fa[x])) rotate(chtype(x) == chtype(fa[x]) ? fa[x] : x);
	}
	void access(int x, int v) {
		// printf("access %d %d\n", x, v);
		int y = 0;
		for(; x; y = x, x = fa[x]) {
			splay(x), c[x][1] = y, pushup(x);
			// printf("link %d %d\n", x, y);
			if(x > 1 && last[x]) /* printf("%d:(last=%d, fa=%d) ", x, last[x], fa[x]),  */bit.add(last[x] - sam.t[x].len + 1, last[x] - sam.t[fa[x]].len, -1);
		}
		// printf("y = %d\n", y);
		pushlast(y, v);
		bit.add(1, v, 1);
	}
	void init() {
		for(int i = 2; i <= sam.tot; i++) fa[i] = sam.t[i].link;
	}
} lct;

int main() {
	scanf("%s%d", s + 1, &m), n = strlen(s + 1);
	for(int i = 1; i <= m; i++) scanf("%d%d", &a[i].l, &a[i].r), a[i].id = i;
	std::sort(a + 1, a + m + 1, [&](Query x, Query y) { return x.r < y.r; });
	for(int i = 1; i <= n; i++) sam.insert(s[i]);
	// for(int i = 1; i <= sam.tot; i++) printf("sam.t[%d]: len = %d, link = %d\n", i, sam.t[i].len, sam.t[i].link);
	int now = 1;
	lct.init();
	for(int i = 1, j = 1; i <= n; i++) {
		now = sam.t[now].next[s[i]];
		lct.access(now, i);
		while(j <= m && a[j].r == i) out[a[j].id] = bit.query(a[j].l, i), j++;
	}
	for(int i = 1; i <= m; i++) printf("%lld\n", out[i]);
	return 0;
}