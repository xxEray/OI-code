#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;
const LL MOD = 998244353;
const int V = 1e9;

int n;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

struct SegNode { LL cnt, ret, lazy; int ls, rs; } t[N * 200];
int nw() { static int tot = 0; tot++; t[tot].lazy = 1; return tot; }
void setlazy(int x, LL v) { if(x) (t[x].cnt *= v) %= MOD, (t[x].ret *= v) %= MOD, (t[x].lazy *= v) %= MOD; }
void lazydown(int x) { if(x) setlazy(t[x].ls, t[x].lazy), setlazy(t[x].rs, t[x].lazy), t[x].lazy = 1; }
void add(int qind, LL qv, int x, int l = 1, int r = V) {
	if(!x) return;
	if(l == r) { (t[x].cnt += qv) %= MOD, (t[x].ret += l * qv) %= MOD; return; }
	int mid = (l + r) >> 1;
	lazydown(x);
	if(qind <= mid) t[x].ls ? 0 : t[x].ls = nw(), add(qind, qv, t[x].ls, l, mid);
	else t[x].rs ? 0 : t[x].rs = nw(), add(qind, qv, t[x].rs, mid + 1, r);
	t[x].cnt = (t[t[x].ls].cnt + t[t[x].rs].cnt) % MOD;
	t[x].ret = (t[t[x].ls].ret + t[t[x].rs].ret) % MOD;
}
int merge(int x, int y, LL vx, LL vy, int l = 1, int r = V) {
	if(!x || !y) {
		if(x) setlazy(x, vx);
		if(y) setlazy(y, vy);
		return x ^ y;
	}
	int mid = (l + r) >> 1;
	if(l == r) {
		t[x].cnt = (t[x].cnt * vx % MOD + t[y].cnt * vy % MOD + t[x].cnt * t[y].cnt % MOD) % MOD;
		t[x].ret = t[x].cnt * l % MOD;
		t[x].lazy = 1;
		return x;
	}
	lazydown(x), lazydown(y);
	int z = nw();
	t[z].ls = merge(t[x].ls, t[y].ls, (vx + t[t[y].rs].cnt) % MOD, (vy + t[t[x].rs].cnt) % MOD, l, mid);
	t[z].rs = merge(t[x].rs, t[y].rs, vx, vy, mid + 1, r);
	t[z].cnt = (t[t[z].ls].cnt + t[t[z].rs].cnt) % MOD;
	t[z].ret = (t[t[z].ls].ret + t[t[z].rs].ret) % MOD;
	return z;
}

LL power2[N];

int f[N];
int sz[N];
int rt;
LL ans;
void dfs(int u, int fa) {
	f[u] = nw();
	add(a[u], 1, f[u]);
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		sz[u] += sz[v];
		f[u] = merge(f[u], f[v], power2[sz[v] - 1], 0);
	}
	(ans += t[f[u]].ret * power2[std::max(n - sz[u] - 1, 0)]) %= MOD;
}


int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	power2[0] = 1;
	for(int i = 1; i <= n; i++) power2[i] = power2[i - 1] * 2 % MOD;
	dfs(1, 0);
	printf("%lld\n", ans);
	return 0;
} /*
6
9 9 8 24 43 53
1 2
1 3
2 4
2 5
3 6
*/