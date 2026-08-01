#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

int n, Q;
int a[N];

LL f[N], g[N];

struct SegNode { LL f, fl, fr, fm; };
struct SegmentTree {
	SegNode t[N << 2];
	SegNode calc(SegNode x, SegNode y) {
		SegNode z;
		z.f = std::max(x.fr + y.f, x.f + y.fl);
		z.fl = std::max(x.fm + y.f, x.fl + y.fl);
		z.fr = std::max(x.fr + y.fr, x.f + y.fm);
		z.fm = std::max(x.fl + y.fm, x.fm + y.fr);
		return z;
	}
	void modify(int qind, LL qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = {qv, 0, 0, 0}; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	SegNode query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql > qr) return {0, 0, 0, 0};
		// printf("query(%d, %d): %lld %lld %lld %lld\n", l, r, t[x].f, t[x].fl, t[x].fr, t[x].fm);
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int main() {
	scanf("%d", &n);
	n--;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	LL sum = 0;
	for(int i = 1; i <= n; i++) sum += a[i];
	for(int i = 1; i <= n; i++) seg.modify(i, a[i]);
	scanf("%d", &Q);
	while(Q--) {
		int k, x;
		scanf("%d%d", &k, &x);
		sum -= a[k];
		a[k] = x, seg.modify(k, x);
		sum += a[k];
		printf("%lld\n", 2 * (sum - seg.query(2, n - 1).f));
	}
	return 0;
}