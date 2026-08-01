#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cstring>

const int N = 2e5 + 5;
const int MX = 4e6;

int a[N];
int n, Q;

struct SegmentTree {
	int t[MX * 4 + 5]; short lazy[MX * 4 + 5];
	void build() {
		memset(lazy, -1, sizeof(lazy));
	}
	void set_lazy(int x, int len, int z) { if(z != -1) t[x] = len * z, lazy[x] = z; }
	void lazy_down(int x, int l, int r) {
		int mid = (l + r) >> 1;
		set_lazy(x << 1, mid - l + 1, lazy[x]);
		set_lazy(x << 1 | 1, r - mid, lazy[x]);
		lazy[x] = -1;
	}
	int find(int qind, int qv, int x = 1, int l = 1, int r = MX) {
		// printf("find(%d, %d, %d)\n", x, l, r);
		if(l == r) return t[x] == qv ? l : 0;
		int mid = (l + r) >> 1;
		lazy_down(x, l, r);
		if(qind > mid) return find(qind, qv, x << 1 | 1, mid + 1, r);
		else {
			int ret = find(qind, qv, x << 1, l, mid);
			if(ret == 0 && t[x << 1 | 1] != !qv * (r - mid)) ret = find(qind, qv, x << 1 | 1, mid + 1, r);
			return ret;
		}
	}
	void modify(int ql, int qr, int qv, int x = 1, int l = 1, int r = MX) {
		// printf("modify(%d, %d, %d, %d)\n", qv, x, l, r);
		if(ql > qr) return;
		if(ql <= l && r <= qr) { set_lazy(x, r - l + 1, qv); return; }
		int mid = (l + r) >> 1;
		lazy_down(x, l, r);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] + t[x << 1 | 1];
	}
	int rmost_1(int x = 1, int l = 1, int r = MX) {
		if(l == r) return l;
		int mid = (l + r) >> 1;
		lazy_down(x, l, r);
		if(t[x << 1 | 1]) return rmost_1(x << 1 | 1, mid + 1, r);
		else return rmost_1(x << 1, l, mid);
	}
} seg;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) {
		// puts("----");
		int ind = seg.find(a[i], 0);
		if(ind) ind--;
		// for(int j = 1; j <= 10; j++) printf("%d ", seg.t[j]);
		// printf("\n%d: ind = %d\n", a[i], ind);
		seg.modify(a[i], ind, 0), ind ? seg.modify(ind + 1, ind + 1, 1) : seg.modify(a[i], a[i], 1);
		// for(int j = 1; j <= 10; j++) printf("%d ", seg.t[j]);
		// puts("");
	}
	while(Q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		int ind = seg.find(a[x], 1);
		if(ind) ind--;
		seg.modify(a[x], ind, 1), ind ? seg.modify(ind + 1, ind + 1, 0) : seg.modify(a[x], a[x], 0);
		a[x] = y;
		ind = seg.find(a[x], 0);
		if(ind) ind--;
		seg.modify(a[x], ind, 0), ind ? seg.modify(ind + 1, ind + 1, 1) : seg.modify(a[x], a[x], 1);
		printf("%d\n", seg.rmost_1());
	}
	return 0;
}