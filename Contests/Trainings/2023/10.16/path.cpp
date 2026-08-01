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
using FIO::wrtc;
using FIO::read;

const int N = 1e6 + 5;

int n, m, K;
int a[N];
struct Edge { int to, nxt; } edge[N];
int head[N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }

bool vis[N];
int f[N];

void dfs(int u) {
	vis[u] = true;
	f[u] = a[u];
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(!vis[v]) dfs(v);
		f[u] = std::max(f[u], a[u] + f[v]);
	}
}

int main() {
#ifndef DEBUG
	freopen("path.in", "r", stdin);
	freopen("path.out", "w", stdout);
#endif
	int T; read(T);
	while(T--) {
		ek = 1;
		read(n), read(m);
		for(int i = 1; i <= n; i++) head[i] = 0, a[i] = 0;
		for(int i = 1; i <= m; i++) { int u, v; read(u), read(v); add_edge(u, v); }
		read(K);
		for(int i = 1; i <= K; i++) { int u; read(u); a[u] = 1; }
		for(int i = 1; i <= n; i++) f[i] = 0, vis[i] = 0;
		for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i);
		int mx = 0;
		for(int i = 1; i <= n; i++) mx = std::max(mx, f[i]);
		if(mx == K) wrtc('Y'), wrtc('e'), wrtc('s'), wrtc('\n');
		else wrtc('N'), wrtc('o'), wrtc('\n');
	}
	return 0;
}
