#include <bits/stdc++.h>

namespace FIO {
	const int D = (1 << 23) + 1;
	char in[D], *I = in + D, *Iend = in + D;
	char gc() { return (I == in + D ? Iend = in + fread(I = in, 1, D, stdin) : 0), I == Iend ? EOF : *I++; }
	template<typename T>
	void read(T &x) {
		char ch = gc();
		while(ch < '0' || ch > '9') ch = gc();
		for(x = 0; '0' <= ch && ch <= '9'; ch = gc()) x = x * 10 + (ch - '0');
	}
}
using FIO::read;

const int N = 1e6 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int f[N][2];

void dfs(int u, int fa) {
	int mx = -INF;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		f[u][0] += std::max(f[v][0], f[v][1]);
		if(a[v]) mx = std::max(mx, f[v][0] - std::max(f[v][0], f[v][1]) + 1);
	}
	if(a[u]) f[u][1] = f[u][0] + mx;
	else f[u][1] = -INF;
}

int main() {
#ifndef DEBUG
	freopen("join.in", "r", stdin);
	freopen("join.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 1; i < n; i++) { int u, v; read(u), read(v); add_edge(u, v), add_edge(v, u); }
	int cnt = 0;
	for(int i = 1; i <= n; i++) cnt += a[i];
	dfs(1, 0);
//	for(int i = 1; i <= n; i++) printf("f[%d]: %d, %d\n", i, f[i][0], f[i][1]);
	if(cnt & 1) puts("UNO");
	else printf("%d\n", cnt - std::max(f[1][0], f[1][1]));
	return 0;
}
