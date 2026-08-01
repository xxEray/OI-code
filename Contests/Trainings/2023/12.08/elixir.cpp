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
using FIO::rdc;
using FIO::write;
using FIO::read;

typedef long long LL;

const int N = 5e5 + 5;

int n, Q;
char s[N];

namespace SAM {
	int len[N * 2], link[N * 2], c[N * 2][5];
	int last, tot;
	void init() { tot = 1, last = 0, link[0] = -1, len[0] = 0; }
	void insert(int ch) {
		int cur = tot++, p = last;
		len[cur] = len[last] + 1;
		last = cur;
		for(; ~p && !c[p][ch]; p = link[p]) c[p][ch] = cur;
		if(p == -1) link[cur] = 0;
		else {
			int q = c[p][ch];
			if(len[q] == len[p] + 1) link[cur] = q;
			else {
				int clone = tot++;
				len[clone] = len[p] + 1;
				link[clone] = link[q], link[q] = clone;
				for(int i = 0; i < 5; i++) c[clone][i] = c[q][i];
				link[cur] = clone;
				for(; ~p && c[p][ch] == q; p = link[p]) c[p][ch] = clone;
			}
		}
	}
}
int prefix[N * 2];

void readstr(char *const str) {
	int c = 0;
	char ch = rdc();
	while('a' <= ch && ch <= 'd') str[c++] = ch, ch = rdc();
	str[c] = 0;
}

namespace Parent {
	int fa[N * 2];
	std::vector<int> son[N * 2];
	int dep[N * 2], dfn[N * 2], dfl[N * 2];
	int go[21][N * 2];
	int nn, time_stamp;
	void get_tree() {
		using namespace SAM;
		for(int i = 1; i <= tot; i++) fa[i] = link[i], son[link[i]].emplace_back(i); // , printf("%d -> %d\n", link[i], i);
		nn = tot - 1;
	}
	void dfs(int u) {
		dfn[u] = time_stamp++, dfl[dfn[u]] = u;
		dep[u] = dep[fa[u]] + 1;
		for(int v : son[u]) dfs(v);
	}
	int calc(int u, int v) { return dep[u] < dep[v] ? u : v; }
	void binary_lifting() {
		for(int i = 0; i <= nn; i++) go[0][i] = dfl[i];
		for(int j = 1; j <= 20; j++)
			for(int i = 0; i + (1 << j) - 1 <= nn; i++)
				go[j][i] = calc(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
	}
	void init() {
		get_tree();
		dfs(0);
		binary_lifting();
	}
	int lca(int u, int v) {
		if(u == v) return u;
		int l = dfn[u], r = dfn[v];
		if(l > r) std::swap(l, r);
		int k = 31 ^ __builtin_clz(r - l);
		return fa[calc(go[k][l + 1], go[k][r - (1 << k) + 1])];
	}
}

namespace Trie {
	std::vector<int> son[N * 2];
	int a[N * 2];
	int fa[N * 2], ls[N * 2], rs[N * 2];
	int nn, rt;
	void get_tree() {
		using namespace SAM;
		nn = tot - 1;
		for(int i = 0; i <= nn; i++) for(int j = 0; j < 5; j++) if(len[c[i][j]] == len[i] + 1) son[i].emplace_back(c[i][j]); // , printf("%d -> %d\n", i, c[i][j]);
		for(int i = 1; i <= nn; i++) a[i] = 1;
	}
	int sz[N * 2], dfn[N * 2], dfl[N * 2], hson[N * 2], time_stamp;
	LL sa[N * 2];
	void dfs1(int u) {
		sz[u] = 1;
		sa[u] = a[u];
		for(int v : son[u]) {
			dfs1(v);
			sz[u] += sz[v];
		}
	}
	void dfs2(int u) {
		dfn[u] = time_stamp++, dfl[dfn[u]] = u;
		hson[u] = -1;
		for(int v : son[u]) if(hson[u] == -1 || sz[hson[u]] < sz[v]) hson[u] = v;
		if(hson[u] != -1) dfs2(hson[u]);
		for(int v : son[u]) if(v != hson[u]) dfs2(v);
	}
	int pre[N * 2];
	int cbuild(int l, int r) {
		// printf("cbuild %d %d\n", l, r);
		// assert(l <= r);
		for(int i = l; i <= r; i++) pre[i] = (i == l ? 0 : pre[i - 1]) + sz[dfl[i]] - (hson[dfl[i]] == -1 ? 0 : sz[hson[dfl[i]]]);
		int ll = l, rr = r;
		while(ll < rr) {
			int mid = (ll + rr) >> 1;
			if(2 * pre[mid] <= pre[r]) ll = mid + 1;
			else rr = mid;
		}
		// assert(l <= ll && ll <= r);
		int x = dfl[ll];
		if(l <= ll - 1) {
			int y = cbuild(l, ll - 1);
			ls[x] = y, fa[y] = x;
		}
		if(ll + 1 <= r) {
			int y = cbuild(ll + 1, r);
			rs[x] = y, fa[y] = x;
		}
		return x;
	}
	int build(int u, bool top) {
		// printf("build %d %d\n", u, top);
		for(int v : son[u]) if(v != hson[u]) fa[build(v, true)] = u;
		if(hson[u] != -1) build(hson[u], false);
		if(top) {
			int i = dfn[u];
			while(i < nn && dfl[i + 1] == hson[dfl[i]]) i++;
			return cbuild(dfn[u], i);
		}
		return 0;
	}
	void dfs3(int u) {
		sa[u] = a[u];
		if(ls[u] != -1) dfs3(ls[u]), sa[u] += sa[ls[u]];
		if(rs[u] != -1) dfs3(rs[u]), sa[u] += sa[rs[u]];
	}
	void init() {
		get_tree();
		for(int i = 0; i <= nn; i++) fa[i] = ls[i] = rs[i] = -1;
		dfs1(0), dfs2(0);
		rt = build(0, true);
		for(int i = 0; i <= nn; i++) if(fa[i] == -1 || (ls[fa[i]] != i && rs[fa[i]] != i)) dfs3(i);
		// for(int i = 0; i <= nn; i++) printf("%d: a=%d, dfn = %d, hson=%d, fa=%d, ls=%d, rs=%d, sa=%lld\n", i, a[i], dfn[i], hson[i], fa[i], ls[i], rs[i], sa[i]);
		fa[rt] = -1;
	}
	LL sum[N * 2], tag[N * 2];
	void add(int u, LL v) {
		// printf("add(%d, %lld)\n", u, v);
		LL ret2 = 0;
		bool flag = true;
		while(true) {
			if(flag) {
				tag[u] += v, ret2 += v * sa[u];
				if(rs[u] != -1) tag[rs[u]] -= v, sum[rs[u]] -= v * sa[rs[u]], ret2 -= v * sa[rs[u]];
			}
			sum[u] += ret2;
			if(fa[u] == -1) break;
			flag = (ls[fa[u]] != u);
			if(flag && rs[fa[u]] != u) ret2 = 0;
			u = fa[u];
		}
	}
	LL query(int u) {
		// printf("query(%d)\n", u);
		LL ret = 0, ret2 = 0;
		bool flag = true;
		while(true) {
			if(flag) ret2 += sa[u] - (rs[u] == -1 ? 0 : sa[rs[u]]), ret += (ls[u] == -1 ? 0 : sum[ls[u]]);
			ret += tag[u] * ret2;
			if(fa[u] == -1) break;
			flag = (ls[fa[u]] != u);
			if(flag && rs[fa[u]] != u) ret2 = 0;
			u = fa[u];
		}
		return ret;
	}
}

bool exist[N * 2];

int main() {
#ifndef DEBUG
	freopen("elixir.in", "r", stdin);
	freopen("elixir.out", "w", stdout);
#endif
	readstr(s + 1);
	read(Q);
	n = strlen(s + 1);
	SAM::init();
	for(int i = 1; i <= n; i++) SAM::insert(s[i] - 'a'), prefix[i] = SAM::last;
	Parent::init();
	Trie::init();
	fprintf(stderr, "clock = %d\n", (int)clock());
	LL ans = 0;
	while(Q--) {
		int x, y;
		read(x), read(y);
		int z = Parent::lca(prefix[x], prefix[y]);
		// printf("prefix[x] = %d, prefix[y] = %d, z = %d\n", prefix[x], prefix[y], z);
		if(exist[z]) {
			Trie::add(z, -1);
			ans -= Trie::query(z);
			exist[z] = false;
		} else {
			ans += Trie::query(z);
			Trie::add(z, 1);
			exist[z] = true;
		}
		write(ans, '\n');
		// for(int i = 0; i <= Trie::nn; i++) printf("%d: sum=%lld, tag=%lld\n", i, Trie::sum[i], Trie::tag[i]);
	}
	return 0;
}