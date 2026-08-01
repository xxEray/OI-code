#include <cstdio>
#include <algorithm>
#include <vector>
#include <assert.h>

typedef long long LL;

const int N = 2e5 + 5;

LL a[N];
struct Query { int l, r, id; } q[N];
int n, Q;

struct SegmentTree {
	LL t[N << 2], lazy[N << 2];
	void set_lazy(int x, LL v, int len) { lazy[x] = v, t[x] = v * len; }
	void lazy_down(int x, int l, int r) {
		if(!lazy[x]) return;
		int mid = (l + r) >> 1;
		lazy[x << 1] = lazy[x << 1 | 1] = lazy[x];
		t[x << 1] = lazy[x] * (mid - l + 1);
		t[x << 1 | 1] = lazy[x] * (r - mid);
		lazy[x] = 0;
	}
	void set(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { set_lazy(x, qv, r - l + 1); return; }
		int mid = (l + r) >> 1;
		lazy_down(x, l, r);
		if(ql <= mid) set(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) set(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] + t[x << 1 | 1];
	}
	LL query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { return t[x]; }
		int mid = (l + r) >> 1;
		lazy_down(x, l, r);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return query(ql, qr, x << 1, l, mid) + query(ql, qr, x << 1 | 1, mid + 1, r);
	}
} seg;

LL sum[N], out[N];

std::vector<int> que;
int main() {
	// n = 100;
	// while(true) {
	// 	char c[10];
	// 	scanf("%s", c);
	// 	if(c[0] == 's') { int x, y, z; scanf("%d%d%d", &x, &y, &z); seg.set(x, y, z); }
	// 	else { int l, r; scanf("%d%d", &l, &r); printf("%d\n", seg.query(l, r)); }
	// }
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= Q; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	std::sort(q + 1, q + Q + 1, [](Query x, Query y) { return x.l > y.l; });
	for(int i = n, j = 1; i >= 1; i--) {
		while(!que.empty() && a[que.back()] <= a[i]) que.pop_back();
		seg.set(i, (que.empty() ? n : que.back() - 1), a[i]);
		que.push_back(i);
		while(j <= Q && q[j].l == i) out[q[j].id] = seg.query(i, q[j].r) - (sum[q[j].r] - sum[i - 1]), j++;
	}
	for(int i = 1; i <= Q; i++) printf("%lld\n", out[i]);
	return 0;
}