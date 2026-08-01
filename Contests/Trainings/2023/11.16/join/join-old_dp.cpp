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
	int ret[2][2] = {{0, INF}, {INF, INF}};
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		int old[2][2] = {{ret[0][0], ret[0][1]}, {ret[1][0], ret[1][1]}};
		ret[0][0] = ret[0][1] = ret[1][0] = ret[1][1] = INF;
		if(a[v]) {
			for(int j : {0, 1}) for(int k : {0, 1}) ret[j][k] = std::min(ret[j][k], old[j][k] + f[v][0]);
			for(int j : {0, 1}) for(int k : {0, 1}) ret[1][k ^ 1] = std::min(ret[1][k ^ 1], old[j][k] + f[v][1] + 1);
		} else {
			for(int j : {0, 1}) for(int k : {0, 1}) ret[j][k] = std::min(ret[j][k], old[j][k] + f[v][0]);
			for(int j : {0, 1}) for(int k : {0, 1}) ret[j][k ^ 1] = std::min(ret[j][k ^ 1], old[j][k] + f[v][1] + 1);
		}
	}
	if(a[u]) {
		f[u][0] = std::min(ret[0][1] + 1, ret[1][1]);
		f[u][1] = std::min(ret[0][0], ret[1][0]);
	} else {
		f[u][0] = std::min(ret[0][0], ret[1][0]);
		f[u][1] = std::min(ret[0][1], ret[1][1]) - 1;
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
	dfs(1, 0);
	 for(int i = 1; i <= n; i++) printf("f[%d]: %d, %d\n", i, f[i][0], f[i][1]);
	if(f[1][0] >= INF / 2) puts("UNO");
	else printf("%d\n", f[1][0]);
	return 0;
}
