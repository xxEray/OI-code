#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n, m;

struct BIT {
	LL t[N];
	void add_(int x, LL v) { while(x <= n) t[x] += v, x += x & -x; }
	void add(int l, int r, LL v) { add_(l + 1, v),  add_(r + 2, -v); }
	LL query(int x) { x++; LL ret = 0; while(x) ret += t[x], x -= x & -x; return ret; }
} bit;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) {
		LL x;
		scanf("%lld", &x);
		bit.add(i, i, x);
	}
	for(int _ = 1; _ <= m; _++) {
		int pos;
		scanf("%d", &pos);
		LL val = bit.query(pos);
		bit.add(pos, pos, -val);
		bit.add(0, n - 1, val / n);
		val %= n;
		pos = (pos + 1) % n;
		if(pos + val - 1 < n) bit.add(pos, pos + val - 1, 1);
		else {
			bit.add(pos, n - 1, 1);
			bit.add(0, (pos + val - 1) % n, 1);
		}
		// for(int i = 0; i < n; i++) printf("%lld ", bit.query(i));
		// puts("");
	}
	for(int i = 0; i < n; i++) printf("%lld ", bit.query(i));
	return 0;
}