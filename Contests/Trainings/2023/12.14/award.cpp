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

const int N = 2e5 + 5;

int n, Q;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dfn[N], dfl[N], dep[N], time_stamp;
void dfs(int u, int f) {
	dfn[u] = ++time_stamp, dfl[dfn[u]] = u;
	dep[u] = dep[f] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != f) {
		int v = edge[i].to;
		dfs(v, u);
	}
}
int go[21][N];
void binary_lifting() {
	for(int i = 1; i <= n; i++) go[0][i] = dep[dfl[i]];
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i + (1 << j) - 1 <= n; i++)
			go[j][i] = std::min(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
}
int dist(int u, int v) {
	if(u == v) return 0;
	int l = dfn[u], r = dfn[v];
	if(l > r) std::swap(l, r);
	int k = 31 ^ __builtin_clz(r - l);
	return dep[u] + dep[v] - 2 * (std::min(go[k][l + 1], go[k][r - (1 << k) + 1]) - 1);
}

struct Path {
	int u, v;
	int dist() const { return ::dist(u, v) + a[u] + a[v]; }
	Path() {}
	Path(int u_, int v_) : u(u_), v(v_) {}
};
bool operator<(const Path &x, const Path &y) { return x.dist() < y.dist(); }
Path merge(const Path &x, const Path &y) { return std::max({x, y, Path(x.u, y.u), Path(x.u, y.v), Path(x.v, y.u), Path(x.v, y.v)}); }
struct SegmentTree {
	Path t[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = Path(l, l); return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = merge(t[x << 1], t[x << 1 | 1]);
	}
	void modify(int qind, int x = 1, int l = 1, int r = n) {
		if(l == r) return;
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, x << 1, l, mid);
		else modify(qind, x << 1 | 1, mid + 1, r);
		t[x] = merge(t[x << 1], t[x << 1 | 1]);
	}
} seg;

std::multiset<int> st;

int main() {
#ifndef DEBUG
	freopen("award.in", "r", stdin);
	freopen("award.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 1; i < n; i++) { int u, v; read(u), read(v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0), binary_lifting();
	seg.build();
	for(int i = 1; i <= n; i++) st.emplace(a[i]);
	read(Q);
	while(Q--) {
		int x, y;
		read(x), read(y);
		st.erase(st.find(a[x]));
		a[x] = y;
		st.emplace(a[x]);
		seg.modify(x);
		write(std::max(*st.rbegin(), (seg.t[1].dist() + 1) >> 1), '\n');
	}
	return 0;
}