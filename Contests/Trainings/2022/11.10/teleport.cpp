#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D, out[D], *O = out;
	char gc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char ch = gc();
		while(ch < '0' || ch > '9') ch = gc();
		for(x = 0; '0' <= ch && ch <= '9'; ch = gc()) x = x * 10 + ch - '0';
	}
	void pc(char c) { (O == out + D ? fwrite(O = out, 1, D, stdout) : 0), *O++ = c; }
	void flush() { fwrite(out, 1, O - out, stdout); }
}
using FIO::pc;
using FIO::flush;
using FIO::read;

const int N = 1e6 + 5;

int n, m, Q;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int fa[N], dep[N], vis[N], block[N];
int blk_cnt;
void dfs(int u) {
	block[u] = blk_cnt;
	dep[u] = dep[fa[u]] + 1, vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		fa[v] = u;
		dfs(v);
	}
}

bool flag[N];

int main() {
#ifndef DEBUG
	freopen("teleport.in", "r", stdin);
	freopen("teleport.out", "w", stdout);
#endif
	int T; read(T), read(n), read(m);
	for(int i = 1; i <= m; i++) { int u, v; read(u), read(v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) if(!vis[i]) blk_cnt++, dfs(i);
	for(int u = 1; u <= n; u++) for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(!((dep[u] + dep[v]) & 1)) flag[block[u]] = true;
	}
	read(Q);
	while(Q--) {
		int u, v;
		read(u), read(v);
		if(block[u] != block[v]) pc('-'), pc('1'), pc('\n');
		else if(flag[block[u]]) pc(u == v ? '0' : '1'), pc('\n');
		else pc(u == v ? '0' : '1' + !((dep[u] + dep[v]) & 1)), pc('\n');
	}
	flush();
	return 0;
}
