#include <bits/stdc++.h>

const int N = 1e5 + 5;
const int M = 2e5 + 5;

int n, m;
char s[N], tmp[N];
struct Query { int l, r, id, out1, out2; std::string str; } qry[M];

struct SAM {
	int link[2 * N], nxt[2 * N][26], len[2 * N];
	int tot, last;
	SAM() { link[0] = -1; }
	void insert(char c) {
		int cur = ++tot, p = last;
		len[cur] = len[p] + 1, last = cur;
		for(; ~p && !nxt[p][c]; p = link[p]) nxt[p][c] = cur;
		if(p == -1) link[cur] = 0;
		else {
			int q = nxt[p][c];
			if(len[q] == len[p] + 1) link[cur] = q;
			else {
				int clone = ++tot;
				len[clone] = len[p] + 1;
				link[clone] = link[q], link[q] = clone;
				for(int i = 0; i < 26; i++) nxt[clone][i] = nxt[q][i];
				link[cur] = clone;
				for(; ~p && nxt[p][c] == q; p = link[p]) nxt[p][c] = clone;
			}
		}
	}
} sam;

std::vector<int> son[2 * N];

int dfn[2 * N], sz[2 * N], time_stamp;
void dfs(int u) {
	dfn[u] = ++time_stamp;
	sz[u] = 1;
	for(int v : son[u]) dfs(v), sz[u] += sz[v];
}

struct SegmentTree {
	int t[(N * 2) << 2];
	void modify(int qind, int qv, int x = 1, int l = 1, int r = time_stamp) {
		if(l == r) { t[x] = std::max(t[x], qv); return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = time_stamp) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::max(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int calc(int x) { return seg.query(dfn[x], dfn[x] + sz[x] - 1); }

int main() {
	scanf("%s%d", s + 1, &m);
	n = strlen(s + 1);
	for(int i = 1; i <= m; i++) scanf("%d%d%s", &qry[i].l, &qry[i].r, tmp), qry[i].str = tmp, qry[i].id = i;
	std::sort(qry + 1, qry + m + 1, [&](const Query &x, const Query &y) { return x.r < y.r; });
	for(int i = 1; i <= n; i++) sam.insert(s[i] - 'a');
	for(int i = 1; i <= sam.tot; i++) son[sam.link[i]].emplace_back(i);
	dfs(0);
	int now = 0;
	for(int i = 1, j = 1; i <= n; i++) {
		now = sam.nxt[now][s[i] - 'a'];
		seg.modify(dfn[now], i);
		for(; j <= m && qry[j].r == i; j++) {
			int p = 0;
			int aid = -1, ec = -1;
			{
				for(int c = qry[j].str[0] - 'a' + 1; c < 26; c++)
					if(sam.nxt[p][c] && calc(sam.nxt[p][c]) >= qry[j].l)
						{ aid = -1, ec = c; break; }
			}
			for(int k = 0; k < (int)qry[j].str.size(); k++) {
				p = sam.nxt[p][qry[j].str[k] - 'a'];
				if(!p) break;
				for(int c = (k + 1 == (int)qry[j].str.size() ? 0 : qry[j].str[k + 1] - 'a' + 1); c < 26; c++)
					if(sam.nxt[p][c] && calc(sam.nxt[p][c]) >= qry[j].l + k + 1)
						{ aid = k, ec = c; break; }
			}
			qry[j].out1 = aid, qry[j].out2 = ec;
		}
	}
	std::sort(qry + 1, qry + m + 1, [&](const Query &x, const Query &y) { return x.id < y.id; });
	for(int i = 1; i <= m; i++) {
		if(qry[i].out2 == -1) { puts("-1"); continue; }
		for(int j = 0; j <= qry[i].out1; j++) putchar(qry[i].str[j]);
		putchar(qry[i].out2 + 'a');
		puts("");
	}
	return 0;
}