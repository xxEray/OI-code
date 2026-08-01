#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;

int n, lenall;

char s[2 * N];
int st[N], len[N];

int trie[N][26], ctrie;
int id[N];
int end[N];

int sa[2 * N], rk[2 * N], tin[2 * N], tp[2 * N], ht[N];
void get_sa() {
	int m = 'z';
	auto basic_sort = [&]() {
		for(int i = 0; i <= m; i++) tin[i] = 0;
		for(int i = 1; i <= lenall; i++) tin[rk[i]]++;
		for(int i = 1; i <= m; i++) tin[i] += tin[i - 1];
		for(int i = lenall; i >= 1; i--) sa[tin[rk[tp[i]]]--] = tp[i];
	};
	for(int i = 1; i <= lenall; i++) rk[i] = s[i], tp[i] = i;
	basic_sort();
	for(int i = 1, p = 0; p < lenall; i <<= 1, m = p) {
		p = 0;
		for(int j = 1; j <= i; j++) tp[++p] = lenall - j + 1;
		for(int j = 1; j <= lenall; j++) if(sa[j] > i) tp[++p] = sa[j] - i;
		basic_sort();
		for(int j = 1; j <= lenall; j++) tp[j] = rk[j];
		rk[sa[1]] = p = 1;
		for(int j = 2; j <= lenall; j++)
			rk[sa[j]] = (tp[sa[j - 1]] == tp[sa[j]] && tp[sa[j - 1] + i] == tp[sa[j] + i] ? p : ++p);
	}
	for(int i = 1; i <= lenall; i++) {
		int j = ht[rk[i - 1]];
		if(j) j--;
		while(std::max(sa[rk[i] - 1], i) + j <= lenall && s[sa[rk[i] - 1] + j] == s[i + j]) j++;
		ht[rk[i]] = j;
	}
}
struct SparseTable {
	int go[21][N];
	void init() {
		for(int i = 2; i <= lenall; i++) go[0][i] = ht[i];
		for(int j = 1; j <= 20; j++)
			for(int i = 2; i + (1 << j) - 1 <= lenall; i++)
				go[j][i] = std::min(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
	}
	int lcp(int i, int j) {
		if(i == j) return lenall - i + 1;
		// assert(i != j);
		int l = rk[i], r = rk[j];
		if(l > r) std::swap(l, r);
		int k = 31 ^ __builtin_clz(r - l);
		// printf("lcp(%d, %d) = %d\n", i, j, std::min(go[k][l + 1], go[k][r - (1 << k) + 1]));
		return std::min(go[k][l + 1], go[k][r - (1 << k) + 1]);
	}
} ST;

struct String {
	int l1, r1, l2, r2;
	String() {}
	String(int l1_, int r1_, int l2_, int r2_) : l1(l1_), r1(r1_), l2(l2_), r2(r2_) {}
};
int print(int x) { /* printf(" = %d\n", x); */ return x; }
int compare(char x, char y) { return x == y ? 0 : (x < y ? -1 : 1); }
int compare(String x, String y) {
	// printf("compare [%d,%d]+[%d,%d] [%d,%d]+[%d,%d]", x.l1, x.r1, x.l2, x.r2, y.l1, y.r1, y.l2, y.r2);
	int op = 1;
	if(x.r1 - x.l1 < y.r1 - y.l1) op = -1, std::swap(x, y);
	int len1 = std::min(x.r1 - x.l1 + 1, y.r1 - y.l1 + 1);
	int lc = ST.lcp(x.l1, y.l1);
	if(lc < len1) return print(op * compare(s[x.l1 + lc], s[y.l1 + lc]));
	int len2 = std::min(x.r1 - x.l1 + 1 - len1, y.r2 - y.l2 + 1);
	lc = ST.lcp(x.l1 + len1, y.l2);
	if(lc < len2) return print(op * compare(s[x.l1 + len1 + lc], s[y.l2 + lc]));
	int len3 = std::min(x.r2 - x.l2 + 1, y.r2 - y.l2 + 1 - len2);
	lc = ST.lcp(x.l2, y.l2 + len2);
	if(lc < len3) return print(op * compare(s[x.l2 + lc], s[y.l2 + len2 + lc]));
	if(x.r1 - x.l1 + x.r2 - x.l2 != y.r1 - y.l1 + y.r2 - y.l2)
		return print(op * (x.r1 - x.l1 + x.r2 - x.l2 < y.r1 - y.l1 + y.r2 - y.l2 ? -1 : 1));
	return print(0);
}
bool operator<(String x, String y) { return compare(x, y) == -1; }

LL ans;
int dfn[N], ep[N], sz[N], cnt[N];
int time_stamp;
std::vector<int> vct;
inline int ed(int i) { return st[i] + len[i] - 1; }
int ccnt;
void predfs(int u) {
	// printf("predfs %d\n", u);
	sz[u] = 1;
	dfn[u] = ++time_stamp;
	ccnt += end[u], cnt[u] = ccnt;
	for(int c = 0; c < 26; c++) if(trie[u][c]) {
		int v = trie[u][c];
		predfs(v);
		sz[u] += sz[v];
	}
}

struct BIT {
	int t[N];
	void add(int x, int v) { while(x <= time_stamp) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
} bit;

struct Node { String s; int w, type; LL multi; };
bool type;
bool operator<(const Node &x, const Node &y) {
	int ret = compare(x.s, y.s);
	if(ret == 0) return type ? (std::abs(x.type) < std::abs(y.type)) : (std::abs(x.type) > std::abs(y.type));
	else return ret < 0;
}
std::vector<Node> vct1, vct2;
void dfs(int u) {
	if(end[u]) {
		ans += (LL)end[u] * (end[u] - 1) * (end[u] - 2) / 6;
		vct2.push_back({String(st[id[u]], ed(id[u]), st[id[u]], ed(id[u])), time_stamp, 2, (LL)end[u] * (end[u] - 1) / 2});
		ans -= (LL)end[u] * (end[u] - 1) / 2 * end[u];
		for(int v : vct) {
			// printf("u = %d, v = %d\n", u, v);
			// printf("ans = %lld\n", ans);
			String tmp;
			if(compare({st[id[v]], ed(id[v]), st[id[u]], ed(id[u])}, {st[id[u]], ed(id[u]), st[id[v]], ed(id[v])}) == 1)
				tmp = String(st[id[u]], ed(id[u]), st[id[v]], ed(id[v]));
			else tmp = String(st[id[v]], ed(id[v]), st[id[u]], ed(id[u]));
			vct2.push_back({tmp, dfn[u] + sz[u] - 1, -2, (LL)end[u] * end[v]});
			vct2.push_back({tmp, dfn[u], 2, (LL)end[u] * end[v]});
			vct1.push_back({String(st[id[u]] + len[id[v]], ed(id[u]), 1, 0), dfn[u] - 1, -2, (LL)end[u] * end[v]});
			ans += (LL)(cnt[u] - end[u]) * end[u] * end[v];
			if(compare({st[id[v]], ed(id[v]), st[id[v]], ed(id[v])}, {st[id[u]], ed(id[u]), 1, 0}) == 1)
				ans -= (LL)end[v] * end[u] * end[v];
			// printf("ans = %lld\n", ans);
		}
	}
	if(end[u]) vct.emplace_back(u);
	for(int c = 0; c < 26; c++) if(trie[u][c]) {
		int v = trie[u][c];
		dfs(v);
	}
	if(end[u]) vct.pop_back();
}

int main() {
#ifndef DEBUG
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
	scanf("%d", &n);
	st[0] = 1;
	for(int i = 1; i <= n; i++) {
		st[i] = st[i - 1] + len[i - 1];
		scanf("%s", s + st[i]);
		len[i] = strlen(s + st[i]);
		int now = 0;
		for(int j = 0; j < len[i]; j++) {
			int c = s[st[i] + j] - 'a';
			if(!trie[now][c]) trie[now][c] = ++ctrie;
			now = trie[now][c];
		}
		end[now]++, id[now] = i;
		ep[i] = now;
	}
	lenall = st[n] + len[n] - 1;
	get_sa(), ST.init();
	predfs(0), dfs(0);
	for(int i = 1; i <= n; i++) {
		vct1.push_back({String(st[i], ed(i), 1, 0), dfn[ep[i]], 1, 1});
		vct2.push_back({String(st[i], ed(i), 1, 0), dfn[ep[i]], 1, 1});
	}
	std::sort(vct2.begin(), vct2.end());
	// printf("ans = %lld\n", ans);
	for(const auto &[_, w, t, multi] : vct2) {
		// printf("s = [%d,%d]+[%d,%d], w = %d, t = %d, multi=%lld\n", _.l1, _.r1, _.l2, _.r2, w, t, multi);
		if(std::abs(t) == 1) {
			bit.add(w, (t > 0 ? 1 : -1) * multi);
		} else ans += bit.query(w) * (t > 0 ? 1 : -1) * multi;
	}
	// printf("ans = %lld\n", ans);
	type = true;
	for(int i = 1; i <= time_stamp; i++) bit.t[i] = 0;
	std::sort(vct1.begin(), vct1.end());
	for(const auto &[_, w, t, multi] : vct1) {
		// printf("s = [%d,%d]+[%d,%d], w = %d, t = %d, multi=%lld\n", _.l1, _.r1, _.l2, _.r2, w, t, multi);
		if(std::abs(t) == 1) {
			bit.add(w, (t > 0 ? 1 : -1) * multi);
		} else ans += bit.query(w) * (t > 0 ? 1 : -1) * multi;
	}
	printf("%lld\n", ans);
	return 0;
} /*
3
e
ee
eeb
*/