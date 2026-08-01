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

typedef __int128_t LL;

const int N = 1e5 + 5;

int n;
LL a[N];
struct Edge { int to, nxt; LL w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

LL base;
LL sum[N];
int fa[N];
void predfs(int u) {
	sum[u] = a[u];
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		predfs(v);
		sum[u] += sum[v];
	}
}

LL f[N];
int rt;
void dfs(int u) {
	f[u] = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		dfs(v);
		f[u] = std::max(f[u], f[v] + (sum[rt] - 2 * sum[v]) * edge[i].w);
	}
}
LL solve(int rt_) {
	rt = rt_;
	dfs(rt);
	return base + f[rt] * (sum[1] - sum[rt]);
}

int main() {
#ifndef DEBUG
	freopen("brain.in", "r", stdin);
	freopen("brain.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 2; i <= n; i++) { LL w; read(fa[i]), read(w); add_edge(i, fa[i], w), add_edge(fa[i], i, w); }
	predfs(1);
	for(int u = 1; u <= n; u++)
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
			int v = edge[i].to;
			base += sum[v] * (sum[1] - sum[v]) * edge[i].w;
		}
	for(int i = 2; i <= n; i++) write(solve(i), '\n');
	return 0;
}