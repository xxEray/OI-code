#ifdef ONLINE_JUDGE
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#endif

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
const int INF = 0x3f3f3f3f;

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
int go[19][N];
void binary_lifting() {
	for(int i = 1; i <= n; i++) go[0][i] = dep[dfl[i]];
	for(int j = 1; j <= 18; j++)
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

int fa[N];
std::vector<int> son[N];

bool vis[N];
int allsize, root, rootwt;
int sz[N];
void getroot(int u, int f) {
	int mx = 0;
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to] && edge[i].to != f) {
		int v = edge[i].to;
		getroot(v, u);
		mx = std::max(mx, sz[v]);
		sz[u] += sz[v];
	}
	mx = std::max(mx, allsize - sz[u]);
	if(rootwt > mx) root = u, rootwt = mx;
}
void get_tree(int u) {
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, 0);
		allsize = sz[v], rootwt = INF, getroot(v, 0);
		son[u].emplace_back(root), fa[root] = u;
		get_tree(root);
	}
}

struct Multiset {
	std::priority_queue<int> p, q;
	int size() const { return p.size() - q.size(); }
	void erase(int x) { q.emplace(x); }
	void emplace(int x) { p.emplace(x); }
	int top() {
		while(!q.empty() && q.top() == p.top()) p.pop(), q.pop();
		return p.top();
	}
	int top_plus_second_top() {
		while(!p.empty() && !q.empty() && q.top() == p.top()) p.pop(), q.pop();
		if(p.empty()) return 0;
		int sum = p.top();
		int x = sum;
		p.pop();
		while(!p.empty() && !q.empty() && q.top() == p.top()) p.pop(), q.pop();
		if(p.empty()) return 0;
		sum += p.top();
		p.emplace(x);
		return sum;
	}
};
Multiset st[N], st2[N], allset, nums;

inline int calc(int u) { return st2[u].top_plus_second_top(); }

std::vector<int> dist_fa[N];

int main() {
#ifndef DEBUG
	freopen("award.in", "r", stdin);
	freopen("award.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]), nums.emplace(a[i]);
	for(int i = 1; i < n; i++) { int u, v; read(u), read(v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0), binary_lifting();
	int rt;
	allsize = n, rootwt = INF, getroot(1, 0), rt = root, get_tree(rt);
	for(int u = 1; u <= n; u++) {
		dist_fa[u].reserve(20);
		for(int v = u; v; v = fa[v])
			dist_fa[u].emplace_back(dist(u, v));
	}
	for(int u = 1; u <= n; u++)
		for(int v = u, d = 1; fa[v]; v = fa[v], d++)
			st[v].emplace(a[u] + dist_fa[u][d]);
	// fprintf(stderr, "clock = %d\n", (int)clock());
	for(int u = 1; u <= n; u++) if(fa[u]) st2[fa[u]].emplace(st[u].top());
	for(int i = 1; i <= n; i++) st2[i].emplace(a[i]);
	for(int i = 1; i <= n; i++) allset.emplace(calc(i));
	// for(int i = 1; i <= n; i++) {
	// 	printf("%d: fa = %d, son = ", i, fa[i]);
	// 	for(int v : son[i]) printf("%d ", v);
	// 	printf(", st = ");
	// 	for(int x : st[i]) printf("%d ", x);
	// 	printf(", st2 = ");
	// 	for(int x : st2[i]) printf("%d ", x);
	// 	puts("");
	// }
	read(Q);
	while(Q--) {
		int u, x;
		read(u), read(x);
		nums.erase(a[u]);
		for(int v = u; v; v = fa[v]) allset.erase(calc(v));
		for(int v = u, d = 1; fa[v]; v = fa[v], d++) {
			st2[fa[v]].erase(st[v].top());
			st[v].erase(a[u] + dist_fa[u][d]);
			st[v].emplace(x + dist_fa[u][d]);
			st2[fa[v]].emplace(st[v].top());
		}
		st2[u].erase(a[u]);
		a[u] = x;
		st2[u].emplace(a[u]);
		for(int v = u; v; v = fa[v]) allset.emplace(calc(v));
		nums.emplace(a[u]);
		write(std::max((allset.top() + 1) >> 1, nums.top()), '\n');
	}
	return 0;
}