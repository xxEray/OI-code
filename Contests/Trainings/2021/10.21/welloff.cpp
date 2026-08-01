#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int n, Q;

struct Segment {
	int t[N << 2], lazy[N << 2];
	void lazy_down(int x) {
		if(!lazy[x]) return;
		lazy[x << 1] = std::max(lazy[x << 1], lazy[x]);
		lazy[x << 1 | 1] = std::max(lazy[x << 1 | 1], lazy[x]);
		t[x << 1] = std::max(t[x << 1], lazy[x]);
		t[x << 1 | 1] = std::max(t[x << 1 | 1], lazy[x]);
		lazy[x] = 0;
	}
	void set(int qind, int qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = qv, lazy[x] = 0; return; }
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(qind <= mid) set(qind, qv, x << 1, l, mid);
		else set(qind, qv, x << 1 | 1, mid + 1, r);
	}
	void set_max(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { t[x] = lazy[x] = std::max(lazy[x], qv); return; }
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(ql <= mid) set_max(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) set_max(ql, qr, qv, x << 1 | 1, mid + 1, r);
	}
	int query(int qind, int x = 1, int l = 1, int r = n) {
		if(l == r) return t[x];
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(qind <= mid) return query(qind, x << 1, l, mid);
		else return query(qind, x << 1 | 1, mid + 1, r);
	}
} seg;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); seg.set(i, x); }
	scanf("%d", &Q);
	while(Q--) {
		int t, x, y;
		scanf("%d", &t);
		if(t == 1) {
			scanf("%d%d", &x, &y);
			seg.set(x, y);
		} else if(t == 2) {
			scanf("%d", &x);
			seg.set_max(1, n, x);
		}
	}
	for(int i = 1; i <= n; i++) printf("%d ", seg.query(i));
	return 0;
} /*
3
6699 22698 1500 
3
2 28626
2 3203
1 2 18362

*/
