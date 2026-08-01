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

int ans;
int sum[N];
void dfs(int u, int fa) {
	sum[u] += a[u];
	bool flag = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		sum[u] += sum[v];
		if(flag && a[u] && (sum[v] & 1) && a[v]) ans--, flag = false;
	}
}

int main() {
#ifndef DEBUG
	freopen("join.in", "r", stdin);
	freopen("join.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 1; i < n; i++) { int u, v; read(u), read(v); add_edge(u, v), add_edge(v, u); }
	ans = 0;
	for(int i = 1; i <= n; i++) ans += a[i];
	if(ans & 1) { puts("UNO"); return 0; }
	dfs(1, 0);
	printf("%d\n", ans);
	return 0;
}
