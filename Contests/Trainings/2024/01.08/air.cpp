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

const int N = 5e5 + 5;

int n;
int w[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int fa[N];
int f[N], g[N];
void dfs1(int u) {
	std::vector<int> vct;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		dfs1(v);
		vct.emplace_back(f[v]);
	}
	std::sort(vct.begin(), vct.end(), std::greater<int>());
	for(int i = 0; i < (int)vct.size(); i++) f[u] = std::max(f[u], vct[i] + i / w[u] + 1);
}
void dfs2(int u) {
	{
		std::vector<std::pair<int, int>> vct;
		if(u != 1) vct.emplace_back(g[u], 0);
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) vct.emplace_back(f[edge[i].to], edge[i].to);
		std::sort(vct.begin(), vct.end(), std::greater<std::pair<int, int>>());
		std::vector<int> tmp(vct.size());
		for(int i = (int)vct.size() - 2; i >= 0; i--) tmp[i] = std::max(tmp[i + 1], vct[i + 1].first + i / w[u] + 1);
		int tmp2 = 0;
		for(int i = 0; i < (int)vct.size(); i++) {
			if(vct[i].second) g[vct[i].second] = std::max(tmp2, tmp[i]);
			tmp2 = std::max(tmp2, vct[i].first + i / w[u] + 1);
		}
	}
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) dfs2(edge[i].to);
}

int main() {
#ifndef DEBUG
	freopen("air.in", "r", stdin);
	freopen("air.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i <= n; i++)	read(w[i]);
	for(int i = 1; i < n; i++) { int u, v; read(u), read(v); add_edge(u, v), add_edge(v, u); }
	dfs1(1), dfs2(1);
	// for(int i = 1; i <= n; i++) printf("%d: fa=%d, f=%d, g=%d\n", i, fa[i], f[i], g[i]);
	for(int u = 1; u <= n; u++) {
		std::vector<int> vct;
		if(u != 1) vct.emplace_back(g[u]);
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) vct.emplace_back(f[edge[i].to]);
		std::sort(vct.begin(), vct.end(), std::greater<int>());
		int mx = 0;
		for(int i = 0; i < (int)vct.size(); i++) mx = std::max(mx, vct[i] + i / w[u] + 1);
		write(mx, '\n');
	}
	return 0;
} /*
4
5 1 5 2 
1 2
2 3
3 4
*/