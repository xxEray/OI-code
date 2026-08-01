#include <cstdio>
#include <algorithm>
#include <set>

typedef long long LL;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
struct Node { int v, id, to; } a[N];
int ori[N];

struct SegNode { int v, id; };
SegNode calc(SegNode x, SegNode y) {
	SegNode z;
	z.v = std::min(x.v, y.v);
	z.id = (z.v == x.v ? x.id : y.id);
	return z;
}
struct SegmentTree {
	SegNode t[N << 2];
	int lazy[N << 2];
	inline void build() { build(1, 1, n); }
	void set_lazy(int x, int v) { lazy[x] += v, t[x].v += v; }
	void lazy_down(int x) { set_lazy(x << 1, lazy[x]), set_lazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	void build(int x, int l, int r) {
		lazy[x] = 0;
		if(l == r) { t[x] = {INF, l}; return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	inline void set(int qind, int qv) { set(qind, qv, 1, 1, n); }
	void set(int qind, int qv, int x, int l, int r) {
		if(l == r) { t[x] = {qv, l}; return; }
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(qind <= mid) set(qind, qv, x << 1, l, mid);
		else set(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	inline void add(int ql, int qr, int qv) { add(ql, qr, qv, 1, 1, n); }
	void add(int ql, int qr, int qv, int x, int l, int r) {
		if(ql > qr) return;
		if(ql <= l && r <= qr) { set_lazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	inline SegNode query(int ql, int qr) { return query(ql, qr, 1, 1, n); }
	SegNode query(int ql, int qr, int x, int l, int r) {
		if(ql > qr) return {INF, 0};
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

struct BIT {
	int t[N];
	void init() { for(int i = 1; i <= n; i++) t[i] = 0; }
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	int query(int l, int r) { return query(r) - (l > 1 ? query(l - 1) : 0); }
} bit;

std::set<int> limit, present;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i].v), a[i].id = i;
		std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.v < y.v; });
		for(int i = 1; i <= n; i++) a[i].to = i, ori[i] = a[i].id;
		std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.id < y.id; });
		seg.build(), limit.clear(), present.clear(), bit.init();
		LL ans = 0;
		for(int i = 1; i <= n; i++) {
			int j = a[i].to;
			present.insert(j), bit.add(j, 1);
			auto it = present.lower_bound(j);
			int last;
			if(it == present.begin()) last = 0;
			else it--, last = a[ori[*it]].v - seg.query(*it, *it).v;
			if(a[i].v == last) {
				limit.insert(j);
				seg.set(j, 0);
			} else {
				ans += a[i].v - (last + 1);
				seg.set(j, a[i].v - (last + 1));
				it = limit.lower_bound(j);
				int r;
				if(it == limit.end()) r = n;
				else r = *it - 1;
				SegNode t;
				if((t = seg.query(j + 1, r)).v == 0) {
					int k = t.id;
					limit.insert(k);
					seg.add(j + 1, k - 1, -1);
					ans -= bit.query(j + 1, k - 1);
				} else {
					seg.add(j + 1, r, -1);
					ans -= bit.query(j + 1, r);
				}
			}
			printf("%lld ", ans);
		}
		puts("");
	}
	return 0;
}