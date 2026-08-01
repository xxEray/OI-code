#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D, out[D], *O = out;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
	void wrtc(char c) { (O == out + D ? fwrite(O = out, 1, D, stdout) : 0), *O++ = c; }
	template<typename T> void write(T x, char ch = 0) {
		static char c[60]; int top = 0;
		if(x < 0) wrtc('-'), x = -x;
		do c[++top] = x % 10, x /= 10; while(x);
		while(top) wrtc(c[top--] + '0');
		if(ch) wrtc(ch);
	}
	void flush() { fwrite(out, 1, O - out, stdout); }
	struct Flusher { ~Flusher() { flush(); } } flusher;
}
using FIO::write;
using FIO::read;

const int N = 1e5 + 5;

int n, m, Q;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
struct Query { int l, r, id; } q[N];
bool operator<(Query x, Query y) { return x.r < y.r; }
int out[N];

int gofa[21][N], dep[N];
void dfs(int u) {
	dep[u] = dep[gofa[0][u]] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != gofa[0][u]) {
		int v = edge[i].to;
		gofa[0][v] = u;
		dfs(v);
	}
}
void get_gofa() {
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++)
			gofa[j][i] = gofa[j - 1][gofa[j - 1][i]];
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int i = 0; i <= 20; i++) if((dep[u] - dep[v]) >> i & 1) u = gofa[i][u];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--) if(gofa[i][u] != gofa[i][v]) u = gofa[i][u], v = gofa[i][v];
	return gofa[0][u];
}

struct BIT {
	int t[N];
	void add(int x, int v) { /* printf("add %d %d\n", x, v); */ if(!x) return; while(x <= m) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	int query(int l, int r) { /* printf("query %d %d\n", l, r); */ return query(r) - query(l - 1); }
} bit;

struct ST_Table {
	int lg[N], go[21][N];
	void preprocess() {
		lg[0] = -1;
		for(int i = 1; i <= m; i++) lg[i] = lg[i >> 1] + 1, go[0][i] = a[i];
		for(int j = 1; j <= 20; j++)
			for(int i = 1; i + (1 << j) - 1 <= m; i++)
				go[j][i] = lca(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
	}
	int getlca(int l, int r) {
		int k = lg[r - l + 1];
		return lca(go[k][l], go[k][r - (1 << k) + 1]);
	}
} ST;

struct LCT {
	int c[N][2], fa[N], mx[N], lzmx[N];
	int stk[N];
	int chtype(int x) { return c[fa[x]][1] == x; }
	int isroot(int x) { return c[fa[x]][0] != x && c[fa[x]][1] != x; }
	void setlazy(int x, int v) { if(x) mx[x] = lzmx[x] = v; }
	void pushdown(int x) {
		if(lzmx[x]) setlazy(c[x][0], lzmx[x]), setlazy(c[x][1], lzmx[x]), lzmx[x] = 0;
	}
	void rotate(int x) {
		int y = fa[x], z = fa[y], t = chtype(x), ty = chtype(y);
		fa[x] = z; if(!isroot(y)) c[z][ty] = x;
		c[y][t] = c[x][!t]; if(c[x][!t]) fa[c[x][!t]] = y;
		c[x][!t] = y, fa[y] = x;
	}
	void splay(int x) {
		int y = x, top = 0;
		while(!isroot(y)) y = fa[y], stk[top++] = y;
		while(top) top--, pushdown(stk[top]);
		pushdown(x);
		for(; !isroot(x); rotate(x)) if(!isroot(fa[x])) rotate(chtype(x) == chtype(fa[x]) ? fa[x] : x);
	}
	void access(int x, int v) {
		bit.add(v, dep[x]);
		int y;
		for(y = 0; x; y = x, x = fa[x]) {
			splay(x);
			c[x][1] = y;
			if(y) bit.add(mx[y], -(dep[y] - dep[x]));
		}
		bit.add(mx[y], -dep[y]);
		setlazy(y, v);
	}
} lct;

int main() {
#ifndef DEBUG
	freopen("stellaris.in", "r", stdin);
	freopen("stellaris.out", "w", stdout);
#endif
	read(n), read(m), read(Q);
	for(int i = 1; i < n; i++) { int u, v; read(u), read(v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= m; i++) read(a[i]);
	for(int i = 1; i <= Q; i++) read(q[i].l), read(q[i].r), q[i].id = i;
	std::sort(q + 1, q + Q + 1);
	dfs(1);
	get_gofa();
	ST.preprocess();
	for(int i = 1; i <= n; i++) if(gofa[0][i]) lct.fa[i] = gofa[0][i];
	for(int i = 1, j = 1; i <= m; i++) {
		lct.access(a[i], i);
		while(j <= Q && q[j].r == i) {
			out[q[j].id] = bit.query(q[j].l, i) - dep[ST.getlca(q[j].l, i)] + 1;
			j++;
		}
	}
	for(int i = 1; i <= Q; i++) write(out[i], '\n');
	return 0;
}
