#include <bits/stdc++.h>

typedef long long LL;
const int N = 2e5 + 5;

int n;
int a[N];

struct BIT {
	int t[N];
	void init() { for(int i = 1; i <= n; i++) t[i] = 0; }
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	int query(int l, int r) { return query(r) - query(l - 1); }
} bit;

LL sum[N][2];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	bit.init();
	for(int i = 1; i <= n; i++) {
		sum[i][0] = bit.query(1, a[i] - 1);
		sum[i][1] = bit.query(a[i] + 1, n);
		bit.add(a[i], 1);
	}
	LL ans1 = 0, ans2 = 0;
	bit.init();
	for(int i = n; i >= 1; i--) {
		ans1 += sum[i][0] * bit.query(1, a[i] - 1);
		ans2 += sum[i][1] * bit.query(a[i] + 1, n);
		bit.add(a[i], 1);
	}
	printf("%lld %lld\n", ans2, ans1);
	return 0;
}