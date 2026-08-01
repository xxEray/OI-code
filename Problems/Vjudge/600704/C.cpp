#pragma GCC optimize("Ofast")

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
const int M = 2e5 + 5;

int n, m, Q;
struct Edge { int u, v, w; } e[M];

LL a[2 * N], b[2 * N];
int up[2 * N], c[2 * N];
std::vector<int> tin[N];
struct Node { int id, ls, rs; LL mx, last; };
std::vector<Node> vct[N];
int son[N * 2][2], fa[N * 2];

int ld[N * 2];
int find(int x) { return ld[x] == x ? x : ld[x] = find(ld[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? ld[x] = y : 0; }

int dep[N * 2], dfn[N * 2], dfl[N * 2], sz[N * 2], time_stamp;
int go[20][N * 2];
void dfs(int u) {
	if(!u) return;
	dep[u] = dep[fa[u]] + 1, dfn[u] = ++time_stamp, dfl[dfn[u]] = u, sz[u] = 1;
	for(int v : {son[u][0], son[u][1]}) {
		dfs(v);
		sz[u] += sz[v];
	}
}
int go2[20][N * 2];
int lower_dep(int u, int v) { return dep[u] < dep[v] ? u : v; }
void binary_lifting() {
	for(int j = 0; j < 20; j++) for(int i = 0; i <= 2 * n + 1; i++) go2[j][i] = go[j][i] = 0;
	for(int i = 1; i <= 2 * n - 1; i++) go2[0][i] = dfl[i], go[0][i] = fa[i];
	for(int j = 1; j < 20; j++)
		for(int i = 1; i + (1 << j) - 1 <= 2 * n - 1; i++)
			go2[j][i] = lower_dep(go2[j - 1][i], go2[j - 1][i + (1 << (j - 1))]);
	for(int j = 1; j < 20; j++)
		for(int i = 1; i <= 2 * n - 1; i++)
			go[j][i] = go[j - 1][go[j - 1][i]];
}
int lca(int u, int v) {
	if(u == v) return u;
	int l = dfn[u], r = dfn[v];
	if(l > r) std::swap(l, r);
	int k = (31 ^ __builtin_clz(r - l));
	return fa[lower_dep(go2[k][l + 1], go2[k][r - (1 << k) + 1])];
}
bool ancestor(int u, int v) { return dfn[u] <= dfn[v] && dfn[v] <= dfn[u] + sz[u] - 1; }

struct BIT {
	LL t[N * 2];
	void add(int x, LL v) { assert(1 <= x && x <= 2 * n - 1); while(x <= 2 * n - 1) t[x] += v, x += x & -x; }
	LL query(int r) { LL ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	LL query(int l, int r) { assert(1 <= l && l <= r && r <= 2 * n - 1); return query(r) - query(l - 1); }
} bit;

int main() {
	// freopen("C.in", "r", stdin);
	// freopen("out.txt", "w", stdout);
	int T; read(T);
	while(T--) {
		read(n), read(m), read(Q);
		for(int i = 0; i <= 2 * n + 1; i++) a[i] = b[i] = c[i] = fa[i] = son[i][0] = son[i][1] = up[i] = 0;
		for(int i = 1; i <= n; i++) tin[i].clear(), vct[i].clear();
		for(int i = 1; i <= n; i++) read(c[i]), tin[c[i]].emplace_back(i);
		for(int i = 1; i <= n; i++) read(a[i]);
		for(int i = 1; i <= m; i++) read(e[i].u), read(e[i].v), read(e[i].w);
		std::sort(e + 1, e + m + 1, [&](const Edge &x, const Edge &y) { return x.w < y.w; });
		for(int i = 1; i <= 2 * n; i++) ld[i] = i;
		for(int i = 1, cn = n; i <= m; i++) {
			int u = find(e[i].u), v = find(e[i].v);
			if(u == v) continue;
			cn++, son[cn][0] = u, son[cn][1] = v, fa[u] = cn, fa[v] = cn;
			up[cn] = e[i].w;
			merge(u, cn), merge(v, cn);
		}
		time_stamp = 0;
		dfs(2 * n - 1);
		binary_lifting();
		// for(int i = 1; i <= 2 * n - 1; i++) printf("%d: son=%d %d, fa=%d, up=%d, dfn=%d, sz=%d, dep=%d\n", i, son[i][0], son[i][1], fa[i], up[i], dfn[i], sz[i], dep[i]);
		for(int i = 1; i <= n; i++) if(!tin[i].empty()) {
			std::sort(tin[i].begin(), tin[i].end(), [&](const int &x, const int &y) { return dfn[x] < dfn[y]; });
			int len = tin[i].size();
			for(int j = 0; j < len - 1; j++) tin[i].emplace_back(lca(tin[i][j], tin[i][j + 1]));
			std::sort(tin[i].begin(), tin[i].end(), [&](const int &x, const int &y) { return dfn[x] < dfn[y]; });
			tin[i].erase(std::unique(tin[i].begin(), tin[i].end()), tin[i].end());
			// printf("tin[%d]: ", i); for(int x : tin[i]) printf("%d ", x); puts("");
			vct[i].resize(tin[i].size());
			len = vct[i].size();
			for(int j = 0; j < len; j++) vct[i][j].id = tin[i][j];
			std::vector<int> stk{0};
			for(int j = 1; j < len; j++) {
				while(!stk.empty() && !ancestor(tin[i][stk.back()], tin[i][j])) stk.pop_back();
				assert(!stk.empty());
				auto &now = vct[i][stk.back()];
				(now.ls ? now.rs : now.ls) = tin[i][j];
				stk.emplace_back(j);
			}
			std::reverse(vct[i].begin(), vct[i].end());
			// printf("vct[%d]: ", i); for(const auto &[u, ls, rs, _, __] : vct[i]) printf("(%d,%d,%d) ", u, ls, rs); puts("");
		}
		for(int i = 1; i <= 2 * n - 1; i++) bit.t[i] = 0;
		for(int i = 1; i <= n; i++)
			for(auto &[u, ls, rs, mx, last] : vct[i]) {
				b[u] = mx = std::max({a[u], b[ls], b[rs]});
				last = mx - b[ls] - b[rs];
				bit.add(dfn[u], last);
			}
		// printf("bit: "); for(int i = 1; i <= 2 * n - 1; i++) printf("%lld ", bit.query(i, i)); puts("");
		while(Q--) {
			int type, x, y;
			read(type), read(x), read(y);
			if(type == 0) {
				a[x] += y;
				for(auto &[u, ls, rs, mx, last] : vct[c[x]]) {
					bit.add(dfn[u], -last);
					b[u] = mx = std::max({a[u], b[ls], b[rs]});
					last = mx - b[ls] - b[rs];
					bit.add(dfn[u], last);
				}
			} else {
				for(int i = 19; i >= 0; i--) if(go[i][x] && up[go[i][x]] <= y) x = go[i][x];
				// printf("x = %d (dfn=%d)\n", x, dfn[x]);
				write(bit.query(dfn[x], dfn[x] + sz[x] - 1), '\n');
			}
			// printf("bit: "); for(int i = 1; i <= 2 * n - 1; i++) printf("%lld ", bit.query(i, i)); puts("");
		}
	}
	return 0;
} /*
1
3 2 2
1 1 2 
3 5 5 
2 1 2
2 3 1
0 3 4
1 1 4
*/