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

typedef long long LL;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, Q;
struct Edge { int to, nxt; LL w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

int dc[N], eul[N * 2], euo[N], euc;
LL dep[N];
void dfs(int u, int fa) {
	eul[++euc] = u, euo[u] = euc;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dep[v] = dep[u] + edge[i].w, dc[v] = dc[u] + 1;
		dfs(v, u);
		eul[++euc] = u;
	}
}
int lg[N * 2];
int go[N * 2][21];
int calc(int u, int v) { return dc[u] < dc[v] ? u : v; }
void preprocess() {
	lg[0] = -1;
	for(int i = 1; i <= euc; i++) lg[i] = lg[i >> 1] + 1, go[i][0] = eul[i];
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i + (1 << j) - 1 <= euc; i++)
			go[i][j] = calc(go[i][j - 1], go[i + (1 << (j - 1))][j - 1]);
}
int lca(int u, int v) {
	int l = euo[u], r = euo[v];
	if(l > r) std::swap(l, r);
	int k = lg[r - l + 1];
	return calc(go[l][k], go[r - (1 << k) + 1][k]);
}
LL distance(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }

bool vis[N];
int sz[N], allsize, root, rootwt;
void findroot(int u, int fa) {
	int mx = 0;
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && !vis[edge[i].to]) {
		int v = edge[i].to;
		findroot(v, u);
		sz[u] += sz[v];
		mx = std::max(mx, sz[v]);
	}
	mx = std::max(mx, allsize - sz[u]);
	if(rootwt > mx) root = u, rootwt = mx;
}
int fa[N];
void solve(int u) {
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		findroot(v, u);
		rootwt = INF, allsize = sz[v], findroot(v, u), fa[root] = u, solve(root);
	}
}

LL out[N];
struct Query { int k, x, y, id; LL dis; };
std::vector<Query> q[N];
std::vector<std::pair<int, LL>> fas[N];
LL f[N];

int main() {
#ifndef DEBUG
	freopen("distance.in", "r", stdin);
	freopen("distance.out", "w", stdout);
#endif
	read(n), read(Q);
	for(int i = 1; i < n; i++) { int u, v, w; read(u), read(v), read(w); add_edge(u, v, w), add_edge(v, u, w); }
	dfs(1, 0), preprocess();
	rootwt = INF, allsize = n, findroot(1, 0), solve(root);
	for(int i = 1; i <= n; i++) f[i] = LLINF;
	for(int i = 1; i <= Q; i++) {
		int k, x, y;
		read(k), read(x), read(y);
		out[i] = (k == 1 ? -1LL : LLINF);
		for(int u = x; u; u = fa[u]) q[u].push_back({k, x, y, i, distance(x, u)});
	}
	// fprintf(stderr, "clock = %d\n", clock());
	for(int i = 1; i <= n; i++) f[i] = LLINF;
	for(int i = 1; i <= n; i++) for(int j = i; j; j = fa[j]) fas[i].push_back({j, distance(i, j)});
	for(int i = 1; i <= n; i++) {
		for(const auto &[k, x, y, id, dis] : q[i])
			if(k == 1) {
				for(const auto &[j, d] : fas[y]) f[j] = std::min(f[j], dis + d);
			} else {
				for(const auto &[j, d] : fas[y]) out[id] = std::min(out[id], dis + d + f[j]);
			}
		for(const auto &[k, x, y, id, dis] : q[i])
			for(int j = y; j; j = fa[j])
				f[j] = LLINF;
	}
	for(int i = 1; i <= Q; i++) if(out[i] != -1) write(out[i] == LLINF ? -1LL : out[i], '\n');
	return 0;
}