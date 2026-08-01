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

const int N = 1e5 + 5;
const int D = 19;
const int INF = 0x3f3f3f3f;

int n;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

LL ans[N];

bool vis[N];
int sz[N], root, rootwt, allsize;
void getroot(int u, int fa) {
	int mx = 0;
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to] && edge[i].to != fa) {
		int v = edge[i].to;
		getroot(v, u);
		sz[u] += sz[v];
		mx = std::max(mx, sz[v]);
	}
	mx = std::max(mx, allsize - sz[u]);
	if(mx < rootwt) rootwt = mx, root = u;
}
int cntall[(1 << D) + 5];
LL sumall[(1 << D) + 5];
std::vector<int> cnt[D + 3];
std::vector<LL> sum[D + 3];
void dfs(int u, int fa, int dep, std::vector<std::pair<int, int>> &vec) {
	vec.emplace_back(u, dep);
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to] && edge[i].to != fa) dfs(edge[i].to, u, dep + 1, vec);
}
void calc(int rt) {
	auto add = [&](int u, int dep) {
		cntall[dep + a[u]]++, sumall[dep + a[u]] += dep + a[u];
		for(int i = 0; i < D; i++) cnt[i][(dep + a[u]) & ((1 << i) - 1)]++, sum[i][(dep + a[u]) & ((1 << i) - 1)] += dep + a[u];
	};
	auto del = [&](int u, int dep) {
		cntall[dep + a[u]]--, sumall[dep + a[u]] -= dep + a[u];
		for(int i = 0; i < D; i++) cnt[i][(dep + a[u]) & ((1 << i) - 1)]--, sum[i][(dep + a[u]) & ((1 << i) - 1)] -= dep + a[u];
	};
	auto contribute = [&](int u, int dep) {
		for(int i = 0; i + 1 < D; i++) {
			int val = ((1 << 20) - dep + 1) & ((1 << (i + 1)) - 1);
			ans[u] += (cnt[i + 1][val] * (LL)(dep - 1) + sum[i + 1][val]) >> i;
			val = (1 << (i + 1)) - dep + 1;
			if(val >= 0) ans[u] -= (cntall[val] * (LL)(dep - 1) + sumall[val]) >> i;
			val = ((1 << 20) - dep + 2) & ((1 << (i + 1)) - 1);
			ans[u] += (cnt[i + 1][val] * (LL)(dep - 2) + sum[i + 1][val]) >> i;
			val = (1 << (i + 1)) - dep + 2;
			if(val >= 0) ans[u] -= (cntall[val] * (LL)(dep - 2) + sumall[val]) >> i;
			if(i + 2 < D) {
				val = ((1 << 20) - dep + 1) & ((1 << (i + 2)) - 1);
				ans[u] -= (cnt[i + 2][val] * (LL)(dep - 1) + sum[i + 2][val]) >> i;
				val = ((1 << 20) - dep + 2) & ((1 << (i + 2)) - 1);
				ans[u] -= (cnt[i + 2][val] * (LL)(dep - 2) + sum[i + 2][val]) >> i;
			}
		}
	};
	std::vector<std::pair<int, int>> vall;
	dfs(rt, 0, 0, vall);
	for(auto [u, dep] : vall) add(u, dep);
	contribute(rt, 0);
	for(int j = head[rt]; j; j = edge[j].nxt) if(!vis[edge[j].to]) {
		int v = edge[j].to;
		std::vector<std::pair<int, int>> vec;
		dfs(v, rt, 1, vec);
		for(auto [u, dep] : vec) del(u, dep);
		for(auto [u, dep] : vec) contribute(u, dep);
		for(auto [u, dep] : vec) add(u, dep);
	}
	for(auto [u, dep] : vall) del(u, dep);
}
void solve(int u) {
	calc(u);
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, u), rootwt = INF, allsize = sz[v], getroot(v, u), solve(root);
	}
}

int main() {
#ifndef DEBUG
	freopen("team.in", "r", stdin);
	freopen("team.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 1; i < n; i++) { int u, v; read(u), read(v); add_edge(u, v), add_edge(v, u); }
	for(int i = 0; i < D; i++) cnt[i].resize(1 << i), sum[i].resize(1 << i);
	allsize = n, rootwt = INF, getroot(1, 0), solve(root);
	for(int i = 1; i <= n; i++) write(ans[i], ' ');
	return 0;
} /*
5
1 2 3 4 5
1 2
3 2
3 5
5 4
*/