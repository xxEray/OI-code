#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, Q;
int a[N];

struct BIT {
	int t[N];
	void init() { for(int i = 1; i <= n; i++) t[i] = 0; }
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	int query(int l, int r) { return query(r) - query(l - 1); }
} bit;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &Q);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		bit.init();
		int sum = 0;
		for(int i = 1; i <= n; i++) sum += a[i], bit.add(i, (a[i] == 2));
		while(Q--) {
			int t, p, v;
			scanf("%d", &t);
			if(t == 1) {
				scanf("%d", &v);
				if(v > sum) { puts("NO"); continue; }
				if(bit.query(1, n) == n) { puts((v & 1) ? "NO" : "YES"); continue; }
				v = sum - v;
				int l = 1, r = n;
				while(l < r) {
					int mid = (l + r) >> 1;
					if(bit.query(1, mid) == mid) l = mid + 1;
					else r = mid;
				}
				int ll = l - 1;
				l = 1, r = n + 1;
				while(l < r) {
					int mid = (l + r) >> 1;
					if(bit.query(mid, n) == n - mid + 1) r = mid;
					else l = mid + 1;
				}
				int rr = n - l + 1;
				if((v & 1) && v <= 2 * std::min(ll, rr) - 1) puts("NO");
				else puts("YES");
			} else {
				scanf("%d%d", &p, &v);
				if(a[p] == v) continue;
				if(a[p] == 1) sum++, bit.add(p, 1);
				else sum--, bit.add(p, -1);
				a[p] = v;
			}
		}
	}
	return 0;
}