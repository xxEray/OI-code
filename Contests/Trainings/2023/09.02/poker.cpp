#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n, m, K;
int edge[N][2];
struct Node { int l, r, id; } a[2 * N];
int ca;
bool out[N];

int cnt[N], cnte[N], lm[N], rm[N];
struct DSU {
	int fa[N];
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }
} dsu;

struct BIT {
	int t[N];
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	int query(int l, int r) { return query(r) - query(l - 1); }
} bit;

int main() {
// #ifndef DEBUG
// 	freopen("poker.in", "r", stdin);
// 	freopen("poker.out", "w", stdout);
// #endif
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) dsu.fa[i] = i;
	for(int i = 1; i <= K; i++) { int u, v; scanf("%d%d", &u, &v); edge[i][0] = u, edge[i][1] = v; dsu.merge(u, v); }
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) ca++, scanf("%d%d", &a[ca].l, &a[ca].r), a[ca].id = i;
	for(int i = 1; i <= n; i++) lm[i] = n + 1, rm[i] = 0;
	for(int i = 1; i <= n; i++) {
		cnt[dsu.find(i)]++;
		lm[dsu.find(i)] = std::min(lm[dsu.find(i)], i);
		rm[dsu.find(i)] = std::max(rm[dsu.find(i)], i);
	}
	for(int i = 1; i <= K; i++) cnte[dsu.find(edge[i][0])]++;
	for(int i = 1; i <= n; i++) if(dsu.find(i) == i && cnt[i] > cnte[i]) a[++ca] = {lm[i], rm[i], 0};
	std::sort(a + 1, a + ca + 1, [&](Node x, Node y) { return x.r < y.r; });
	for(int i = 1; i <= ca; ) {
		int j;
		for(j = i; j <= ca && a[j].r == a[i].r; j++) if(!a[j].id) bit.add(a[j].l, 1);
		for(j = i; j <= ca && a[j].r == a[i].r; j++) if(a[j].id) out[a[j].id] = (bit.query(a[j].l, n) ? false : true);
		i = j;
	}
	for(int i = 1; i <= m; i++) puts(out[i] ? "Yes" : "No");
	return 0;
} /*
5 2
1 3
2 4
15
1 1
1 2
1 3
1 4
1 5
2 2
2 3
2 4
2 5
3 3
3 4
3 5
4 4
4 5
5 5
*/
