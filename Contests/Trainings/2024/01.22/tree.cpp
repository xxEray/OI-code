#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D, *Iend = in + D, out[D], *O = out;
	char rdc() { return (I == Iend ? Iend = in + fread(I = in, 1, D, stdin) : 0), (I == Iend ? EOF : *I++); }
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

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;
const LL MOD = 1e9 + 7;

int n, m, L, R;
LL a[N];
int fa[N];
std::vector<int> to[N];

inline void mod(LL &x) { if(x >= MOD) x -= MOD; }

struct LCA {
	int dfn[N], dep[N];
	int go[21][N];
	int time_stamp;
	void init() {
		time_stamp = 0;
		for(int i = 2; i <= n; i++) dep[i] = dep[fa[i]] + 1;
		dfs(1);
		binary_lifting();
	}
	void dfs(int u) {
		dfn[u] = ++time_stamp, go[0][dfn[u]] = u;
		for(int v : to[u]) if(v != fa[u]) dfs(v);
	}
	int lower_dep(int u, int v) const { return dep[u] < dep[v] ? u : v; }
	void binary_lifting() {
		for(int j = 1; j <= 20; j++) for(int i = 1; i + (1 << j) - 1 <= n; i++) go[j][i] = lower_dep(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
	}
	int operator()(int u, int v) const {
		if(u == v) return u;
		int l = dfn[u], r = dfn[v];
		if(l > r) std::swap(l, r);
		int k = 31 ^ __builtin_clz(r - l);
		return fa[lower_dep(go[k][l + 1], go[k][r - (1 << k) + 1])];
	}
} lca;

LL cnt[N];

bool vis[N];
int sz[N], allsize;
int root, rootwt;
void getroot(int u, int ff) {
	int mx = 0;
	sz[u] = 1;
	for(int v : to[u]) if(v != ff && !vis[v]) {
		getroot(v, u);
		mx = std::max(mx, sz[v]);
		sz[u] += sz[v];
	}
	mx = std::max(mx, allsize - sz[u]);
	if(mx < rootwt) root = u, rootwt = mx;
}
struct BIT {
	LL t[N];
	void add(int x, LL v) { x++; while(x <= n + 1) mod(t[x] += v), x += x & -x; }
	LL query_(int r) { LL ret = 0; while(r) mod(ret += t[r]), r -= r & -r; return ret; }
	LL query(int l, int r) {
		l = std::max(l, 0), r = std::min(r, n);
		return l > r ? 0 : (query_(r + 1) - query_(l) + MOD) % MOD;
	}
} tin;
void calc(int rt) {
	// for(int i = 0; i <= n; i++) assert(tin.query(i, i) == 0);
	// printf("calc(%d)\n", rt);
	bool ignorert = false;
	auto dfsquery = [&](auto &&self, int u, int ff, int dep) -> void {
		LL val = tin.query(L - dep, R - dep);
		// if(val) printf("%d <-> %d (%d): %lld\n", u, rt, ignorert, val);
		int lc = lca(u, rt);
		mod(cnt[u] += val), mod(cnt[rt] += val), mod(cnt[lc] += MOD - val), mod(cnt[fa[lc]] += MOD - val);
		if(ignorert) mod(cnt[rt] += MOD - val), mod(cnt[fa[rt]] += val);
		for(int v : to[u]) if(v != ff && !vis[v]) self(self, v, u, dep + 1);
	};
	int addval = 0;
	auto dfsadd = [&](auto &&self, int u, int ff, int dep) -> void {
		tin.add(dep, addval);
		for(int v : to[u]) if(v != ff && !vis[v]) self(self, v, u, dep + 1);
	};
	tin.add(0, 1);
	addval = 1;
	for(int v : to[rt]) if(!vis[v]) {
		// printf("traverse v=%d\n", v);
		dfsquery(dfsquery, v, rt, 1);
		dfsadd(dfsadd, v, rt, 1);
	}
	tin.add(0, MOD - 1);
	addval = MOD - 1;
	for(int v : to[rt]) if(!vis[v]) dfsadd(dfsadd, v, rt, 1);
	ignorert = true;
	addval = 1;
	for(auto it = to[rt].rbegin(); it != to[rt].rend(); it++) if(!vis[*it]) {
		int v = *it;
		// printf("traverse v=%d\n", v);
		dfsquery(dfsquery, v, rt, 1);
		dfsadd(dfsadd, v, rt, 1);
	}
	addval = MOD - 1;
	for(int v : to[rt]) if(!vis[v]) dfsadd(dfsadd, v, rt, 1);
	// if(L == 0) mod(cnt[rt] += 1), mod(cnt[fa[rt]] -= 1);
}
void solve(int u) {
	calc(u);
	vis[u] = true;
	for(int v : to[u]) if(!vis[v]) {
		getroot(v, 0);
		allsize = sz[v], rootwt = INF, getroot(v, 0), solve(root);
	}
}

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	read(n), read(m), read(L), read(R);
	L--, R--;
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 2; i <= n; i++) read(fa[i]), to[i].emplace_back(fa[i]), to[fa[i]].emplace_back(i);
	lca.init();
	allsize = n, rootwt = INF, getroot(1, 0), solve(root);
	for(int u = n; u >= 1; u--) for(int v : to[u]) if(v != fa[u]) mod(cnt[u] += cnt[v]);
	// printf("cnt: "); for(int i = 1; i <= n; i++) printf("%lld ", cnt[i]); puts("");
	LL ans = 0;
	for(int i = 1; i <= n; i++) mod(ans += a[i] * cnt[i] % MOD);
	// printf("ans = %lld\n", ans);
	cnt[0] = 0;
	for(int i = 1; i <= n; i++) mod(cnt[i] += cnt[fa[i]]);
	// printf("cnt: "); for(int i = 1; i <= n; i++) printf("%lld ", cnt[i]); puts("");
	while(m--) {
		int u, v; LL w;
		read(u), read(v), read(w);
		int l = lca(u, v);
		mod(ans += (cnt[u] + cnt[v] - cnt[l] - cnt[fa[l]] + 2 * MOD) % MOD * w % MOD);
		write(ans % MOD, '\n');
	}
	return 0;
} /*
10 10 3 6
36 11 76 24 71 89 24 63 75 40
1 1 2 2 3 3 4 4 5
2 5 18
5 7 95
7 10 82
8 2 99
8 1 85
7 7 60
1 5 85
4 3 38
9 4 17
1 1 99
*/