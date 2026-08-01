#include <bits/stdc++.h>

const int N = 1e5 + 5;

char s[N], t[N], p[N];
int n, m, K;

#define print(arr, len) print_(#arr, arr, len)
void print_(const char *arrname, int *arr, int len) { printf("%s: ", arrname); for(int i = 1; i <= len; i++) printf("%d ", arr[i]); puts(""); }

void get_nxt(char *const str, int *nxt) {
	int c = strlen(str + 1);
	for(int i = 1; i <= c; i++) nxt[i] = 0;
	for(int i = 2, j = 0; i <= c; i++) {
		while(j && str[j + 1] != str[i]) j = nxt[j];
		if(str[j + 1] == str[i]) j++;
		nxt[i] = j;
	}
	// printf("s = %s, nxt = ", str + 1); for(int i = 1; i <= c; i++) printf("%d ", nxt[i]); puts("");
}
void match(char *const text, char *const pattern, int *const nxt, int *occ) {
	int lt = strlen(text + 1), lp = strlen(pattern + 1);
	for(int i = 1, j = 0; i <= lt; i++) {
		while(j && text[i] != pattern[j + 1]) j = nxt[j];
		if(text[i] == pattern[j + 1]) j++;
		occ[i] = j;
		if(j == lp) j = nxt[j];
	}
	// printf("s = %s, t = %s, occ = ", text + 1, pattern + 1); for(int i = 1; i <= lt; i++) printf("%d ", occ[i]); puts("");
}
void get_rev_nxt(char *str, int *nxt) {
	int l = strlen(str + 1);
	std::reverse(str + 1, str + l + 1);
	get_nxt(str, nxt);
	std::reverse(str + 1, str + l + 1);
	std::reverse(nxt + 1, nxt + l + 1);
	for(int i = 1; i <= l; i++) nxt[i] = l - nxt[i] + 1;
}
void get_rev_match(char *text, char *pattern, int *const nxt, int *occ) {
	int lt = strlen(text + 1), lp = strlen(pattern + 1);
	std::reverse(text + 1, text + lt + 1), std::reverse(pattern + 1, pattern + lp + 1);
	std::reverse(nxt + 1, nxt + lp + 1);
	for(int i = 1; i <= lp; i++) nxt[i] = lp - nxt[i] + 1;
	match(text, pattern, nxt, occ);
	std::reverse(nxt + 1, nxt + lp + 1);
	for(int i = 1; i <= lp; i++) nxt[i] = lp - nxt[i] + 1;
	std::reverse(text + 1, text + lt + 1), std::reverse(pattern + 1, pattern + lp + 1), std::reverse(occ + 1, occ + lt + 1);
	for(int i = 1; i <= lt; i++) occ[i] = lp - occ[i] + 1;
}

int nxts[N], nxtt[N], nxtp[N], nxtrs[N], nxtrp[N];
int prepins[N];
int pins[N], tinp[N], pint[N], rpins[N], rpint[N];
int sumpint;

struct Tree {
	int fa[N];
	std::vector<int> son[N];
	void add_edge(int u, int v) { fa[v] = u; son[u].push_back(v); }
	int dfn[N], sz[N], time_stamp;
	Tree() : time_stamp(-1) {}
	void init(int u) {
		dfn[u] = ++time_stamp;
		sz[u] = 1;
		for(int v : son[u]) init(v), sz[u] += sz[v];
	}
} Trp, Trrp;

struct BIT {
	int t[N];
	void add_(int x, int v) { while(x <= K) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	void add(int l, int r, int v) { assert(1 <= l && l <= r && r <= K); /* printf("[%d, %d] += %d\n", l, r, v); */ add_(l, v), add_(r + 1, -v); }
} bit;

int ans[N];
std::vector<std::pair<int, int>> query[N];
bool ok[N];
void dfs1(int u) {
	// printf("dfs1 %d\n", u);
	if(1 <= u && u + 1 <= K) bit.add(Trrp.dfn[u + 1], Trrp.dfn[u + 1] + Trrp.sz[u + 1] - 1, 1);
	if(1 <= u && u <= K) {
		for(auto [id, v] : query[u]) ans[id] += bit.query(Trrp.dfn[v]); // , printf("ans[%d] += query(%d)(%d)\n", id, Trrp.dfn[v], bit.query(Trrp.dfn[v]));
		query[u].clear(), query[u].shrink_to_fit();
	}
	for(int v : Trp.son[u]) dfs1(v);
	if(1 <= u && u + 1 <= K) bit.add(Trrp.dfn[u + 1], Trrp.dfn[u + 1] + Trrp.sz[u + 1] - 1, -1);
}
void dfs2(int u) {
	// printf("dfs2 %d\n", u);
	if(1 <= u && u + m + 1 <= K && ok[u]) bit.add(Trrp.dfn[u + m + 1], Trrp.dfn[u + m + 1] + Trrp.sz[u + m + 1] - 1, 1);
	if(1 <= u && u <= K) {
		for(auto [id, v] : query[u]) ans[id] += bit.query(Trrp.dfn[v]); // , printf("ans[%d] += query(%d)(%d)\n", id, Trrp.dfn[v], bit.query(Trrp.dfn[v]));
		query[u].clear(), query[u].shrink_to_fit();
	}
	for(int v : Trp.son[u]) dfs2(v);
	if(1 <= u && u + m + 1 <= K && ok[u]) bit.add(Trrp.dfn[u + m + 1], Trrp.dfn[u + m + 1] + Trrp.sz[u + m + 1] - 1, -1);
}
void dfs3(int u) {
	// printf("dfs3 %d\n", u);
	if(1 <= u - 1 && u <= K) bit.add(Trp.dfn[u - 1], Trp.dfn[u - 1] + Trp.sz[u - 1] - 1, 1);
	if(1 <= u && u <= K) {
		for(auto [id, v] : query[u]) ans[id] += bit.query(Trp.dfn[v]); // , printf("ans[%d] += query(%d)(%d)\n", id, Trp.dfn[v], bit.query(Trp.dfn[v]));
		query[u].clear(), query[u].shrink_to_fit();
	}
	for(int v : Trrp.son[u]) dfs3(v);
	if(1 <= u - 1 && u <= K) bit.add(Trp.dfn[u - 1], Trp.dfn[u - 1] + Trp.sz[u - 1] - 1, -1);
}

int main() {
#ifndef DEBUG
	freopen("lgs.in", "r", stdin);
	freopen("lgs.out", "w", stdout);
#endif
	scanf("%s%s%s", s + 1, t + 1, p + 1);
	n = strlen(s + 1), m = strlen(t + 1), K = strlen(p + 1);
	get_nxt(s, nxts), get_nxt(t, nxtt), get_nxt(p, nxtp);
	get_rev_nxt(s, nxtrs), get_rev_nxt(p, nxtrp);
	match(s, p, nxtp, pins), match(p, t, nxtt, tinp), match(t, p, nxtp, pint);
	get_rev_match(s, p, nxtrp, rpins), get_rev_match(t, p, nxtrp, rpint);
	for(int i = 1; i <= n - K + 1; i++) prepins[i] = prepins[i - 1] + (pins[i + K - 1] == K);
	for(int i = 1; i <= m - K + 1; i++) sumpint += (pint[i + K - 1] == K);
	for(int i = 1; i <= K; i++) Trp.add_edge(nxtp[i], i); // , printf("Trp: %d -> %d\n", nxtp[i], i);
	for(int i = 1; i <= K; i++) Trrp.add_edge(nxtrp[i], i); // , printf("Trrp: %d -> %d\n", nxtrp[i], i);
	// print(nxts, n), print(nxtt, m), print(nxtp, K), print(nxtrs, n), print(nxtrp, K);
	// print(pins, n), print(tinp, K), print(pint, m), print(rpins, n), print(rpint, m);
	Trp.init(0), Trrp.init(K + 1);
	for(int i = 0; i <= n; i++) {
		if(i - K + 1 >= 1) ans[i] += prepins[i - K + 1];
		if(i <= n - K + 1) ans[i] += prepins[n - K + 1] - prepins[i];
		ans[i] += sumpint;
	}
	// for(int i = 0; i <= n; i++) printf("ans[%d] = %d\n", i, ans[i]);
	for(int i = 0; i <= n; i++) if(pins[i] && 1 <= rpint[1] && rpint[1] <= K) query[pins[i]].emplace_back(i, rpint[1]); // , printf("$1(%d): %d -- %d\n", i, pins[i], rpint[1]);
	dfs1(0);
	for(int i = 1; i < K - m; i++) if(tinp[i + m] == m) ok[i] = true;
	// for(int i = 1; i < K - m; i++) printf("ok[%d] = %d\n", i, ok[i]);
	for(int i = 0; i <= n; i++) if(m <= K - 2 && pins[i] && rpins[i + 1]) query[pins[i]].emplace_back(i, rpins[i + 1]); // , printf("$2(%d): %d -- %d\n", i, pins[i], rpins[i + 1]);
	dfs2(0);
	for(int i = 0; i <= n; i++) if(rpins[i + 1] && 1 <= pint[m] && pint[m] <= K) query[rpins[i + 1]].emplace_back(i, pint[m]); // , printf("$3(%d): %d -- %d\n", i, rpins[i + 1], pint[m]);
	dfs3(K + 1);
	// for(int i = 0; i <= n; i++) printf("ans[%d] = %d\n", i, ans[i]);
	int mx = *std::max_element(ans, ans + n + 1);
	int cnt = std::count(ans, ans + n + 1, mx);
	int ll = n + 1, rr = -1;
	for(int i = 0; i <= n; i++) if(ans[i] == mx) ll = std::min(ll, i), rr = std::max(rr, i);
	printf("%d %d %d %d\n", mx, cnt, ll, rr);
	return 0;
} /*
gpgggpppg
pg
gpgg
*/