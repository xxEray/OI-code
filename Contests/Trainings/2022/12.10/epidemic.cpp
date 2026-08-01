#include <cstdio>
#include <algorithm>
#include <cassert>

typedef long long LL;
const int N = 1e5 + 5;

int n, Q;
LL a[N];

struct SegmentTree {
	LL ori[N << 2], t[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		if(l == r) { ori[x] = t[x] = a[l]; return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = ori[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	void modify_add(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { t[x] += qv; }
	}
	void modify_div(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {

	}
	LL query(int ql, int qr, int x = 1, int l = 1, int r = n) {

	}
	void reset(int ql, int qr, int x = 1, int l = 1, int r = n) {

	}
} seg;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	seg.build();
	while(Q--) {
		int t, l, r;
		LL x;
		scanf("%d%d%d%lld", &t, &l, &r, &x);
		if(t == 0) seg.modify_add(l, r, x);
		else if(t == 1) seg.modify_div(l, r, x);
		else if(t == 2) printf("%lld\n", seg.query(l, r));
		else if(t == 3) seg.reset(l, r);
		else assert(!"the type of the operation isn't in [0, 3]");
	}
	return 0;
}