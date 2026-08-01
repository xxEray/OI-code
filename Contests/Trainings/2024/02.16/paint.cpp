#include <bits/stdc++.h>

typedef unsigned long long ull;

const int N = 1000 + 5;

int n, m;

struct BIT {
	int t[N];
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	void set(int x, int v) { add(x, v - get(x)); }
	int get(int x) { return query(x) - query(x - 1); }
	int sum(int l, int r) { return query(r) - query(l - 1); }
} a[N];

ull w[N];

int main() {
#ifndef DEBUG
	freopen("paint.in", "r", stdin);
	freopen("paint.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	while(m--) {
		int t; scanf("%d", &t);
		int l, r, x; ull v;
		if(t == 1) {
			scanf("%d%d%d", &l, &r, &x);
			for(int i = l; i <= r; i++) a[x].set(i, 1);
		} else if(t == 2) {
			scanf("%d%d%d", &l, &r, &x);
			for(int i = l; i <= r; i++) a[x].set(i, 0);
		} else if(t == 3) {
			scanf("%d%d%llu", &l, &r, &v);
			int i;
			for(i = 1; i <= n; i++) if(a[i].sum(l, r) < r - l + 1) break;
			for(int j = l; j <= r; j++) if(a[i].get(j) == 0) w[j] += v;
		} else if(t == 4) {
			scanf("%d%d", &l, &r);
			ull ans = 0;
			for(int i = l; i <= r; i++) ans += w[i];
			printf("%llu\n", ans);
		}
	}
	return 0;
}