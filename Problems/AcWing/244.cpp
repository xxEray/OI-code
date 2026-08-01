#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n;
int a[N];

int out[N];

struct BIT {
	int t[N];
	void init() { for(int i = 1; i <= n; i++) t[i] = 0; }
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	int query(int l, int r) { return l > r ? 0 : (query(r) - (l > 1 ? query(l - 1) : 0)); }
} bit;

int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) bit.add(i, 1);
	for(int i = n; i >= 1; i--) {
		int l = 2, r = n + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(bit.query(1, mid - 1) <= a[i]) l = mid + 1;
			else r = mid;
		}
		out[i] = l - 1, bit.add(out[i], -1);
	}
	for(int i = 1; i <= n; i++) printf("%d\n", out[i]);
	return 0;
}