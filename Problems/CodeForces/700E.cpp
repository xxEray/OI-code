#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
char s[N];

std::map<char, int> c[N << 1];
int lnk[N << 1], len[N << 1];
int tot, last;
void init_sam() { last = 0, tot = 0, lnk[0] = -1; }
void insert(int ch) {
	int cur = ++tot, p = last;
	len[cur] = len[p] + 1, last = cur;
	for(; ~p && !c[p][ch]; p = lnk[p]) c[p][ch] = cur;
	if(p == -1) lnk[cur] = 0;
	else {
		int q = c[p][ch];
		if(len[q] == len[p] + 1) lnk[cur] = q;
		else {
			int clone = ++tot;
			len[clone] = len[p] + 1;
			lnk[clone] = lnk[q], lnk[q] = clone;
			c[clone] = c[q];
			lnk[cur] = clone;
			for(; ~p && c[p][ch] == q; p = lnk[p]) c[p][ch] = clone;
		}
	}
}

struct SegNode { int cnt, ls, rs; } t[N * 40];
int cnt;
int merge(int x, int y, int l = 1, int r = n) {
	// printf("merge %d %d\n", l, r);
	if(!x || !y) return x ^ y;
	int z = ++cnt;
	if(l == r) { t[z].cnt = t[x].cnt || t[y].cnt; return z; }
	int mid = (l + r) >> 1;
	t[z].ls = merge(t[x].ls, t[y].ls, l, mid), t[z].rs = merge(t[x].rs, t[y].rs, mid + 1, r);
	t[z].cnt = t[t[z].ls].cnt + t[t[z].rs].cnt;
	return z;
}
void modify(int &x, int qind, int l = 1, int r = n) {
	if(!x) x = ++cnt;
	if(l == r) { t[x].cnt = 1; return; }
	int mid = (l + r) >> 1;
	if(qind <= mid) modify(t[x].ls, qind, l, mid);
	else modify(t[x].rs, qind, mid + 1, r);
	t[x].cnt = t[t[x].ls].cnt + t[t[x].rs].cnt;
}
int query(int x, int ql, int qr, int l = 1, int r = n) {
	if(!x) return 0;
	if(ql <= l && r <= qr) return t[x].cnt;
	int mid = (l + r) >> 1;
	if(qr <= mid) return query(t[x].ls, ql, qr, l, mid);
	else if(ql > mid) return query(t[x].rs, ql, qr, mid + 1, r);
	else return query(t[x].ls, ql, qr, l, mid) + query(t[x].rs, ql, qr, mid + 1, r);
}

int any[N << 1], id[N << 1];
std::vector<int> son[N << 1];
void dfs(int u) {
	for(int v : son[u]) {
		dfs(v);
		if(!any[u]) any[u] = any[v];
		id[u] = merge(id[u], id[v]);
	}
	// printf("endpos[%d]: ", u); for(int i = 1; i <= n; i++) if(query(id[u], i, i)) printf("%d ", i); puts("");
}

int top[N << 2], f[N << 2];
void dfs2(int u) {
	if(u) {
		int ff = top[lnk[u]];
		// printf("try %d -> %d\n", u, ff);
		if(!ff || query(id[ff], any[u] - len[u] + len[ff], any[u] - 1)) f[u] = f[ff] + 1, top[u] = u; // , printf("%d -> %d\n", u, ff);
		else f[u] = f[lnk[u]], top[u] = top[lnk[u]];
	}
	for(int v : son[u]) dfs2(v);
}

int main() {
	scanf("%*d%s", s + 1);
	n = strlen(s + 1);
	init_sam();
	for(int i = 1; i <= n; i++) insert(s[i]);
	// for(int i = 1; i <= tot; i++) printf("%d: lnk=%d, len=%d\n", i, lnk[i], len[i]);
	int now = 0;
	for(int i = 1; i <= n; i++) now = c[now][s[i]], any[now] = i, modify(id[now], i);
	for(int i = 1; i <= tot; i++) son[lnk[i]].emplace_back(i);
	dfs(0), dfs2(0);
	// for(int i = 1; i <= tot; i++) printf("%d: any=%d, top=%d, f=%d\n", i, any[i], top[i], f[i]);
	int ans = 0;
	for(int i = 0; i <= tot; i++) ans = std::max(ans, f[i]);
	printf("%d\n", ans);
	return 0;
} /*
abc

*/