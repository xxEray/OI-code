#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

int n;
int a[N];

struct BIT {
	LL t[N];
	void add(int x, LL v) { while(x <= n) t[x] += v, x += x & -x; }
	LL query(int r) { LL ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	LL query(int l, int r) { return query(r) - query(l - 1); }
} bitcnt, bitsum;

int main() {
#ifndef DEBUG
	freopen("swap.in", "r", stdin);
	freopen("swap.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	LL ans = 0;
	for(int i = 1; i <= n; i++) {
		ans += bitsum.query(a[i] + 1, n) - bitcnt.query(a[i] + 1, n) * a[i];
		bitcnt.add(a[i], 1), bitsum.add(a[i], a[i]);
	}
	printf("%lld\n", ans);
	return 0;
}