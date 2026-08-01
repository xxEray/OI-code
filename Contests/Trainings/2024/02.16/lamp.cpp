#include <bits/stdc++.h>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

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
using FIO::wrtc;
using FIO::write;
using FIO::read;

int n, m;
int a[N], b[N];
int pos[N][2];

struct FHQ {
	int fa[N << 1], c[N << 1][2], v[N << 1], w[N << 1], sz[N << 1], sum[N << 1][2], xs[N << 1], first[N << 1];
	int tot, root;
	int random() { return rand() << 15 | rand(); }
	void init() { tot = 0, root = 0; }
	int nw(int val, int fst) { tot++; w[tot] = random(), v[tot] = val, first[tot] = fst, c[tot][0] = c[tot][1] = 0, fa[tot] = 0; pushup(tot); return tot; }
	void pushdown(int x) {}
	void pushup(int x) {
		sz[x] = sz[c[x][0]] + sz[c[x][1]] + 1;
		xs[x] = xs[c[x][0]] ^ xs[c[x][1]] ^ v[x];
		sum[x][0] = sum[c[x][0]][0] + sum[c[x][1]][xs[c[x][0]] ^ v[x] ^ 0] + (first[x] && (xs[c[x][0]] ^ v[x]) == 0);
		sum[x][1] = sum[c[x][0]][1] + sum[c[x][1]][xs[c[x][0]] ^ v[x] ^ 1] + (first[x] && (xs[c[x][0]] ^ v[x]) == 1);
		fa[c[x][0]] = fa[c[x][1]] = x;
	}
	void split(int rt, int size, int &x, int &y) {
		pushdown(rt);
		if(!rt) x = y = 0;
		else if(sz[c[rt][0]] >= size) y = rt, split(c[y][0], size, x, c[y][0]), pushup(y);
		else x = rt, split(c[x][1], size - sz[c[x][0]] - 1, c[x][1], y), pushup(x);
	}
	int merge(int x, int y) {
		if(!x || !y) return x ^ y;
		else if(w[x] > w[y]) { pushdown(x), c[x][1] = merge(c[x][1], y), pushup(x); return x; }
		else { pushdown(y), c[y][0] = merge(x, c[y][0]), pushup(y); return y; }
	}
	void move(int l, int r, int p) {
		// printf("move [%d, %d] to %d\n", l, r, p);
		// assert(p < l || p > r);
		if(p > r) p -= r - l + 1;
		int x, y, z;
		split(root, l - 1, x, y), split(y, r - l + 1, y, z);
		x = merge(x, z);
		split(x, p, x, z);
		root = merge(x, merge(y, z));
	}
	void append(int val, int fst) { root = merge(root, nw(val, fst)); }
	void seti(int x, int val) {
		v[x] = val;
		for(; fa[x]; x = fa[x]) pushup(x);
	}
	int get(int p) {
		int x, y, z;
		split(root, p - 1, x, y);
		split(y, 1, y, z);
		int ret = v[y];
		root = merge(x, merge(y, z));
		return ret;
	}
	int getxor(int p) {
		int x, y;
		split(root, p, x, y);
		int ret = xs[x];
		root = merge(x, y);
		return ret;
	}
	int ranki(int x) {
		int ret = sz[c[x][0]] + 1;
		for(; fa[x]; x = fa[x]) if(x == c[fa[x]][1]) ret += sz[c[fa[x]][0]] + 1;
		return ret;
	}
	int getxori(int x) { return getxor(ranki(x)); }
	int count() { return sum[root][1]; }
} treap;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
void dfs(int u) {
	treap.append(a[u], 1), pos[u][0] = treap.tot;
	for(int i = head[u]; i; i = edge[i].nxt) dfs(edge[i].to);
	treap.append(a[u], 0), pos[u][1] = treap.tot;
}

int main() {
#ifndef DEBUG
	freopen("lamp.in", "r", stdin);
	freopen("lamp.out", "w", stdout);
#endif
	srand(12983754);
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]), read(b[i]), add_edge(i == 1 ? 0 : b[i], i);
	dfs(0);
	read(m);
	// for(int i = 1; i <= 2 * n + 2; i++) `printf("%d ", treap.get(i));
	// puts("");
	while(m--) {
		int x, y, z;
		read(x), read(y), read(z);
		a[x] = y, b[x] = z;
		if(x != 1) treap.move(treap.ranki(pos[x][0]), treap.ranki(pos[x][1]), treap.ranki(pos[b[x]][0]));
		// treap.set(treap.ranki(pos[x][0]), a[x]), treap.set(treap.ranki(pos[x][1]), a[x]);
		treap.seti(pos[x][0], a[x]), treap.seti(pos[x][1], a[x]);
		// for(int i = 1; i <= 2 * n + 2; i++) printf("%d ", treap.get(i));
		// puts("");
		int ans = INF;
		if(b[1]) {
			// treap.set(treap.ranki(pos[1][0]), a[1] ^ 1), treap.set(treap.ranki(pos[1][1]), a[1] ^ 1);
			treap.seti(pos[1][0], a[1] ^ 1), treap.seti(pos[1][1], a[1] ^ 1);
			if(treap.getxori(pos[b[1]][0]) == 1) ans = std::min(ans, treap.count());
		}
		// treap.set(treap.ranki(pos[1][0]), a[1]), treap.set(treap.ranki(pos[1][1]), a[1]);
		treap.seti(pos[1][0], a[1]), treap.seti(pos[1][1], a[1]);
		if(treap.getxori(pos[b[1]][0]) == 0) ans = std::min(ans, treap.count());
		if(ans == INF) wrtc('-'), wrtc('1'), wrtc('\n');
		else write(ans, '\n');
	}
	return 0;
} /*
4
1 3
1 0
0 1
1 2
3
1 0 3
4 1 3
3 0 2
*/