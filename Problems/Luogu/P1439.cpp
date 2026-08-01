#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n;
int a[N], b[N];

int ib[N];

struct BIT {
	int t[N];
	void modify(int x, int v) { while(x <= n) t[x] = std::max(t[x], v), x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret = std::max(ret, t[r]), r -= r & -r; return ret; }
} bit;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++) ib[b[i]] = i;
	for(int i = 1; i <= n; i++) a[i] = ib[a[i]];
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		int f = bit.query(a[i] - 1) + 1;
		bit.modify(a[i], f);
		ans = std::max(ans, f);
	}
	printf("%d\n", ans);
	return 0;
}