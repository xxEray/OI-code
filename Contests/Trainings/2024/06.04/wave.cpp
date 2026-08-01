#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
int a[N], b[N], al[N], ar[N];

int cl[3 * N], cr[3 * N];

struct Edge { int to, nxt; } edge[6 * N << 1];
int head[3 * N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }

int vis[3 * N], dfn[3 * N], low[3 * N], stk[3 * N], bl[3 * N];
int time_stamp, scc, top;
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	stk[top++] = u;
	vis[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(vis[v] == 0) tarjan(v), low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
	}
	if(low[u] == dfn[u]) {
		scc++;
		do {
			top--;
			bl[stk[top]] = scc;
			vis[stk[top]] = 2;
		} while(stk[top] != u);
	}
}

std::vector<int> to[3 * N];
void dfs(int u) {
	if(vis[u]) return;
	vis[u] = true;
	for(int v : to[u]) dfs(v), cl[u] = std::max(cl[u], cl[v]), cr[u] = std::min(cr[u], cr[v]);
}

struct SegmentTree {
	LL t[N << 2], lz[N << 2];
	void setlazy(int x, LL v) { t[x] += v, lz[x] += v; }
	void lazydown(int x) { setlazy(x << 1, lz[x]), setlazy(x << 1 | 1, lz[x]), lz[x] = 0; }
	void build(int x = 1, int l = 0, int r = n + 1) {
		t[x] = 0, lz[x] = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int ql, int qr, LL qv, int x = 1, int l = 0, int r = n + 1) {
		if(ql > qr) return;
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
	}
	LL query(int ql, int qr, int x = 1, int l = 0, int r = n + 1) {
		if(ql > qr) return LLINF;
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::min(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

std::vector<std::pair<int, LL>> vct[N];
int prv[N], nxt[N];

int main() {
#ifndef DEBUG
	freopen("wave.in", "r", stdin);
	freopen("wave.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1, time_stamp = 0, scc = 0;
		scanf("%d", &n);
		// fprintf(stderr, "n = %d\n", n);
		for(int i = 1; i <= 3 * (n + 1); i++) head[i] = 0, vis[i] = 0, to[i].clear();
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
		a[n + 1] = b[n + 1] = 0;
		for(int i = n + 1; i >= 1; i--) a[i] -= a[i - 1], b[i] -= b[i - 1];
		ar[n + 1] = n + 2;
		for(int i = 1; i <= n; i++) scanf("%d", &ar[i]), ar[i]++;
		for(int i = 2; i <= n + 1; i++) scanf("%d", &al[i]);
		n++;
		for(int i = 1; i <= n; i++) a[i] -= b[i];
		// for(int i = 1; i <= n; i++) printf("%d: %d (%d, %d)\n", i, a[i], al[i], ar[i]);
		LL sum = 0;
		for(int i = 1; i <= n; i++) sum += a[i];
		if(sum) { puts("-1"); continue; }
		for(int i = 1; i <= n; i++) add_edge(i + n, i), add_edge(i + 2 * n, i);
		for(int i = 2; i <= n; i++) add_edge(i + n, i - 1 + n);
		for(int i = 1; i <= n - 1; i++) add_edge(i + 2 * n, i + 1 + 2 * n);
		for(int i = 2; i <= n; i++) if(1 <= al[i] && al[i] < i) add_edge(i, al[i] + n);
		for(int i = 1; i <= n - 1; i++) if(i < ar[i] && ar[i] <= n) add_edge(i, ar[i] + 2 * n);
		for(int i = 1; i <= 3 * n; i++) if(!vis[i]) tarjan(i);
		for(int i = 1; i <= scc; i++) cl[i] = 0, cr[i] = n + 1;
		// for(int i = 1; i <= n; i++) printf("bl[%d] = %d\n", i, bl[i]);
		for(int i = 1; i <= n; i++) cl[bl[i]] = std::max(cl[bl[i]], al[i]), cr[bl[i]] = std::min(cr[bl[i]], ar[i]);
		for(int u = 1; u <= 3 * n; u++) for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(bl[u] != bl[v]) to[bl[u]].emplace_back(bl[v]);
		}
		for(int i = 1; i <= scc; i++) vis[i] = 0;
		for(int i = 1; i <= scc; i++) dfs(i);
		nxt[n + 1] = n + 1;
		for(int i = n; i >= 1; i--) nxt[i] = (a[i] < 0 ? i : nxt[i + 1]);
		prv[0] = 0;
		for(int i = 1; i <= n + 1; i++) prv[i] = (a[i] < 0 || i == n + 1 ? i : prv[i - 1]);
		// for(int i = 1; i <= n; i++) printf("%d: %d (%d, %d)\n", i, a[i], prv[cl[bl[i]]], nxt[cr[bl[i]]]);
		for(int i = 0; i <= n + 1; i++) vct[i].clear();
		for(int i = 1; i <= n; i++) if(a[i] > 0) vct[prv[cl[bl[i]]]].emplace_back(nxt[cr[bl[i]]], a[i]);
		seg.build();
		for(int i = 1; i <= n; i++)
			if(a[i] < 0) seg.modify(1, i, -a[i]);
			else seg.modify(i, i, LLINF);
		a[n + 1] = 0;
		bool flag = true;
		for(int i = 0; i <= n + 1; i++) {
			for(auto [r, v] : vct[i]) seg.modify(1, r, -v);
			if(a[i] < 0 || i == 0 || i == n + 1) {
				seg.modify(i + 1, n + 1, -a[i]);
				flag &= (seg.query(i + 1, n + 1) >= 0);
				// printf("seg(i = %d): ", i); for(int j = 0; j <= n + 1; j++) printf("%lld ", seg.query(j, j)); puts("");
			}
		}
		puts(flag ? "YES" : "NO");
	}
	return 0;
} /*
2
2
6 3
4 6
3 3
1 1
4
1 2 6 1
5 1 2 4
2 5 5 5
1 2 3 2
*/