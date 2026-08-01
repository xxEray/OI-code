#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
struct Node { int v, id; } a[N], b[N];

int pa[N], pb[N], p[N], qa[N], qb[N];

struct BIT {
	int t[N];
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
} bit;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i].v), a[i].v += i, a[i].id = i;
	for(int i = 1; i <= n; i++) scanf("%d", &b[i].v), b[i].v += i, b[i].id = i;
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.v == y.v ? x.id < y.id : x.v < y.v; });
	std::sort(b + 1, b + n + 1, [&](Node x, Node y) { return x.v == y.v ? x.id < y.id : x.v < y.v; });
	for(int i = 1; i <= n; i++) if(a[i].v != b[i].v) { puts("-1"); return 0; }
	for(int i = 1; i <= n; i++) pa[a[i].id] = i, pb[b[i].id] = i;
	for(int i = 1; i <= n; i++) qa[pa[i]] = i, qb[pb[i]] = i;
	for(int i = 1; i <= n; i++) p[qa[i]] = qb[i];
	// printf("pa: "); for(int i = 1; i <= n; i++) printf("%d ", pa[i]); puts("");
	// printf("pb: "); for(int i = 1; i <= n; i++) printf("%d ", pb[i]); puts("");
	// printf("p: "); for(int i = 1; i <= n; i++) printf("%d ", p[i]); puts("");
	long long ans = 0;
	for(int i = n; i >= 1; i--) ans += bit.query(p[i] - 1), bit.add(p[i], 1);
	printf("%lld\n", ans);
	return 0;
}