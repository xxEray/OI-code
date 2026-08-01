#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n, Q;

struct BIT {
	LL t[N];
	void init() { for(int i = 1; i <= n; i++) t[i] = 0; }
	void add(int x, LL v) { while(x <= n) t[x] += v, x += x & -x; }
	LL query(int r) { LL ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	void add(int l, int r, LL v) { add(r + 1, -v), add(l, v); }
} bit;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); bit.add(i, i, x); }
	while(Q--) {
		char s[2];
		scanf("%s", s);
		if(s[0] == 'C') { int l, r, v; scanf("%d%d%d", &l, &r, &v); bit.add(l, r, v); }
		else { int x; scanf("%d", &x); printf("%lld\n", bit.query(x)); }
	}
	return 0;
}