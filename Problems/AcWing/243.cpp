#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n, Q;

struct BIT {
	LL t1[N], t2[N];
	void init() { for(int i = 1; i <= n; i++) t1[i] = t2[i] = 0; }
	void add(int x, LL v) { LL o = x; while(x <= n) t1[x] += v, t2[x] += v * o, x += x & -x; }
	LL query(int r) { LL ret = 0, o = r; while(r) ret += (o + 1) * t1[r] - t2[r], r -= r & -r; return ret; }
	LL query(int l, int r) { return query(r) - (l > 1 ? query(l - 1) : 0); }
	void add(int l, int r, LL v) { add(r + 1, -v), add(l, v); }
} bit;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); bit.add(i, i, x); }
	while(Q--) {
		char s[2];
		scanf("%s", s);
		if(s[0] == 'C') { int l, r, v; scanf("%d%d%d", &l, &r, &v); bit.add(l, r, v); }
		else { int l, r; scanf("%d%d", &l, &r); printf("%lld\n", bit.query(l, r)); }
	}
	return 0;
}