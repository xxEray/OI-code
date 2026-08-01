#include <bits/stdc++.h>

typedef unsigned long long ull;

const int N = (1 << 20) + 5;
const ull inv3 = 12297829382473034411ull;

int n;
ull a[N], b[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dfn[N], sz[N], fa[N], idfn[N];
int time_stamp;
void dfs(int u) {
	dfn[u] = ++time_stamp, sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		dfs(v);
		sz[u] += sz[v];
	}
}

struct BIT {
	ull t[N];
	void add(int x, ull v) { while(x <= n) t[x] += v, x += x & -x; }
	ull query(int r) { ull ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	ull query(int l, int r) { return query(r) - query(l - 1); }
} bit, bitr;

struct Query { int t, l, r, id; } q[4 * N];
struct Ret { int u, ans; } out[2 * N];
int cn, cq;

ull presum[N], power9[N];
ull calc(int l, int r) { return presum[r] - presum[l - 1]; }

int tag[N];
void dfs2(int u, int ff, int bl) {
	tag[u] = bl;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != ff) {
		int v = edge[i].to;
		dfs2(v, u, bl);
	}
}
void getans(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) dfs2(edge[i].to, u, edge[i].to);
	int l = std::max(1, 2 * u - n), r = std::min(n, 2 * u - 1);
	for(int i = l; i <= r; i++) if(i != u && tag[i] != tag[2 * u - i]) {
		printf("YES %d %d %d\n", i, u, 2 * u - i);
		return;
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1);
	for(int i = 1; i <= n; i++) idfn[dfn[i]] = i;
	a[1] = 3;
	for(int i = 2; i <= n; i++) a[i] = a[i - 1] * 3;
	for(int i = 1; i <= n; i++) presum[i] = presum[i - 1] + a[i];
	power9[0] = 1;
	for(int i = 1; i <= n; i++) power9[i] = power9[i - 1] * 9;
	b[1] = inv3;
	for(int i = 2; i <= n; i++) b[i] = b[i - 1] * inv3;
	for(int u = 1; u <= n; u++) {
		int l = std::max(1, 2 * u - n), r = std::min(n, 2 * u - 1);
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
			int v = edge[i].to;
			cn++, out[cn].u = u;
			cq++, q[cq].l = l, q[cq].r = r, q[cq].t = dfn[v] - 1, q[cq].id = -cn;
			cq++, q[cq].l = l, q[cq].r = r, q[cq].t = dfn[v] + sz[v] - 1, q[cq].id = cn;
		}
		cn++, out[cn].u = u, out[cn].ans += calc(l, r) - calc(2 * u - r, 2 * u - l);
		cq++, q[cq].l = l, q[cq].r = r, q[cq].t = dfn[u] - 1, q[cq].id = cn;
		cq++, q[cq].l = l, q[cq].r = r, q[cq].t = dfn[u] + sz[u] - 1, q[cq].id = -cn;
	}
	std::sort(q + 1, q + cq + 1, [&](const Query &x, const Query &y) { return x.t < y.t; });
	// printf("q: "); for(int i = 1; i <= cq; i++) printf("[%d, %d, %d, %d] ", q[i].t, q[i].l, q[i].r, q[i].id); puts("");
	for(int i = 0, j = 1; i <= n; i++) {
		if(i) {
			int k = idfn[i];
			bit.add(k, a[k]), bitr.add(k, b[k]);
		}
		while(j <= cq && q[j].t == i) {
			ull val = bit.query(q[j].l, q[j].r) - power9[out[std::abs(q[j].id)].u] * bitr.query(q[j].l, q[j].r);
			// printf("[%d, %d, %d, %d]: %llu\n", q[j].t, q[j].l, q[j].r, q[j].id, val);
			out[std::abs(q[j].id)].ans += (q[j].id > 0 ? 1 : -1) * val;
			j++;
		}
	}
	for(int i = 1; i <= cn; i++) if(out[i].ans) {
		getans(out[i].u);
		return 0;
	}
	puts("NO");
	return 0;
} /*
10
5 8
8 1
1 10
10 2
2 7
7 3
3 6
6 4
4 9
*/