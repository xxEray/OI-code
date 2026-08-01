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

int n, Q;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int eul[2 * N], eui[N], ceul;
int dfn[N], sz[N], dep[N];
int eu, ev, time_stamp;
void dfs(int u, int fa) {
	// printf("dfs(%d, %d)\n", u, fa);
	dfn[u] = ++time_stamp;
	sz[u] = 1, dep[u] = dep[fa] + 1;
	eul[++ceul] = u, eui[u] = ceul;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		if(dfn[v]) {
			if(dfn[v] > dfn[u]) continue;
			assert(!eu && !ev);
			eu = u, ev = v;
			// printf("eu = %d, ev = %d\n", u, v);
			continue;
		}
		dfs(v, u);
		sz[u] += sz[v];
		eul[++ceul] = u;
	}
}
int go[22][2 * N], lg[2 * N];
int calc(int u, int v) { return dep[u] < dep[v] ? u : v; };
void binary_lifting() {
	assert(ceul == 2 * n - 1);
	for(int i = 1; i <= ceul; i++) go[0][i] = eul[i];
	for(int i = 2; i <= ceul; i++) lg[i] = lg[i >> 1] + 1;
	for(int j = 1; j <= 21; j++)
		for(int i = 1; i + (1 << j) - 1 <= ceul; i++)
			go[j][i] = calc(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
}
int lca(int u, int v) {
	int l = eui[u], r = eui[v];
	if(l > r) std::swap(l, r);
	int k = lg[r - l + 1];
	return calc(go[k][l], go[k][r - (1 << k) + 1]);
}
bool ancestor(int u, int v) { return dfn[u] <= dfn[v] && dfn[v] <= dfn[u] + sz[u] - 1; }
int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
int distance(int u, int v) { return std::min({dist(u, v), dist(u, eu) + dist(ev, v) + 1, dist(u, ev) + dist(eu, v) + 1}); }

int main() {
#ifndef DEBUG
	freopen("catch.in", "r", stdin);
	freopen("catch.out", "w", stdout);
#endif
	read(n), read(Q);
	for(int i = 1; i <= n; i++) { int u, v; read(u), read(v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0);
	binary_lifting();
	while(Q--) {
		int u, v;
		read(u), read(v);
		int t, l = lca(u, eu);
		if(l == eu) t = eu;
		else if(ancestor(l, ev)) t = ev;
		else t = l;
		if(distance(u, t) >= distance(v, t) || dep[eu] - dep[ev] < 3) wrtc('Y'), wrtc('e'), wrtc('s'), wrtc('\n');
		else wrtc('N'), wrtc('o'), wrtc('\n');
	}
	return 0;
}