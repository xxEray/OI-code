#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;
const LL MOD = 998244353;
const int INF = 0x3f3f3f3f;

int n;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

struct SegValue { int mx, sc; LL sum; };
SegValue calc(const SegValue &x, const SegValue &y) {
	SegValue z;
	z.mx = std::max(x.mx, y.mx);
	z.sc = std::max(z.mx == x.mx ? x.sc : x.mx, z.mx == y.mx ? y.sc : y.mx);
	z.sum = ((z.mx == x.mx) * x.sum + (z.mx == y.mx) * y.sum) % MOD;
	return z;
}
struct SegNode { SegValue v; int lazy; SegNode *ls, *rs; };
SegNode buffer[N * 40];
SegNode *nw() { static int k = 0; k++; assert(k < N * 40); buffer[k].v = {0, 0, 0}, buffer[k].lazy = INF, buffer[k].ls = 0, buffer[k].rs = 0; return &buffer[k]; }
void setlazy(SegNode *&x, int v, int l, int r) { if(!x) x = nw(); if(v < x->lazy) x->v.mx = std::min(x->v.mx, v), x->lazy = v; }
void lazydown(SegNode *&x, int l, int r, int mid) {
	setlazy(x->ls, x->lazy, l, mid), setlazy(x->rs, x->lazy, mid + 1, r);
	x->lazy = INF;
}
struct SegmentTreeBeats {
	SegNode *rt;
	inline void modify(int qind, LL qv, LL qs) { modify(qind, qv, qs, rt, 1, n); }
	void modify(int qind, int qv, LL qs, SegNode *&x, int l, int r) {
		if(!x) x = nw();
		if(l == r) { /* printf("modify [%d] (%d, %lld)\n", qind, qv, qs);  */x->v = {qv, 0, qs}, x->lazy = INF; return; }
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(qind <= mid) modify(qind, qv, qs, x->ls, l, mid);
		else modify(qind, qv, qs, x->rs, mid + 1, r);
		x->v = calc(x->ls->v, x->rs->v);
	}
	inline LL modify_min(int ql, int qr, int qv) { return modify_min(ql, qr, qv, rt, 1, n); }
	LL modify_min(int ql, int qr, int qv, SegNode *&x, int l, int r) {
		if(!x) x = nw();
		if(x->v.mx <= qv) return 0;
		if(ql <= l && r <= qr && qv > x->v.sc) { /* printf("modfiy_min [%d, %d] (%d) => %lld\n", l, r, qv, x->v.sum);  */setlazy(x, qv, l, r); return x->v.sum; }
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		LL ret = 0;
		if(ql <= mid) ret += modify_min(ql, qr, qv, x->ls, l, mid);
		if(qr > mid) ret += modify_min(ql, qr, qv, x->rs, mid + 1, r);
		x->v = calc(x->ls->v, x->rs->v);
		return ret % MOD;
	}
} seg[N];
void merge(SegNode *&x, SegNode *&y, int l, int r) {
	if(!y || y->v.mx == 0) return;
	if(!x || x->v.mx == 0) { x = y; return; }
	// if(l == r) { printf("[%d]: x>mx = %d, y>mx = %d\n", l, x->v.mx, y->v.mx); exit(-1); }
	int mid = (l + r) >> 1;
	lazydown(x, l, r, mid), lazydown(y, l, r, mid);
	merge(x->ls, y->ls, l, mid), merge(x->rs, y->rs, mid + 1, r);
	x->v = calc(x->ls->v, x->rs->v);
}
inline void merge(SegmentTreeBeats &x, SegmentTreeBeats &y) { merge(x.rt, y.rt, 1, n); }

LL f[N];
void dfs(int u, int fa) {
	f[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		(f[u] += f[v]) %= MOD;
		if(1 <= a[u] - 1) (f[u] += seg[v].modify_min(1, a[u] - 1, a[u] - 1)) %= MOD;
	}
	seg[u].modify(a[u], n, f[u]);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) merge(seg[u], seg[edge[i].to]);
}

int main() {
#ifndef DEBUG
	freopen("heart.in", "r", stdin);
	freopen("heart.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	dfs(1, 0);
	for(int i = 1; i <= n; i++) printf("%lld\n", f[i]);
	return 0;
}