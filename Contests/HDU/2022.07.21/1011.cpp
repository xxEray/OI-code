#include <cstdio>
#include <algorithm>
using std::min;
using std::max;

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int a[N];
int n, Q;

LL scmax(std::initializer_list<LL> list) {
	LL mx = -LLINF, scmx = -LLINF;
	for(auto v : list)
		if(v > mx) scmx = mx, mx = v;
		else if(v > scmx) scmx = v;
	return scmx;
}
LL scmin(std::initializer_list<LL> list) {
	LL mn = LLINF, scmn = LLINF;
	for(auto v : list)
		if(v < mn) scmn = mn, mn = v;
		else if(v < scmn) scmn = v;
	return scmn;
}

struct Node {
	LL t[2], mn[2], mx[2];
	Node() {}
	Node(LL _mx[], LL _mn[], LL _t[]) { t[0] = _t[0], t[1] = _t[1], mn[0] = _mn[0], mn[1] = _mn[1], mx[0] = _mx[0], mx[1] = _mx[1]; }
};
LL calc(LL x, LL y) { return y >= LLINF ? -LLINF : x * x - y * y; }
Node update(Node pl, Node pr) {
	Node p;
	p.mx[0] = max(pl.mx[0], pr.mx[0]);
	p.mx[1] = scmax({pl.mx[0], pl.mx[1], pr.mx[0], pr.mx[1]});
	p.mn[0] = min(pl.mn[0], pr.mn[0]);
	p.mn[1] = scmin({pl.mn[0], pl.mn[1], pr.mn[0], pr.mn[1]});
	p.t[0] = max({pl.t[0], pr.t[0], calc(pl.mx[0], pr.mn[0])});
	// if(calc(pl.mx[0], pr.mn[0]) > max({pl.t[0], pl.t[1], pr.t[0], pr.t[1]}))
	// 	p.t[1] = max({pl.t[0], pl.t[1], pr.t[0], pr.t[1], calc(pl.mx[1], pr.mn[1])});
	// else
	p.t[1] = scmax({pl.t[0], pl.t[1], pr.t[0], pr.t[1], calc(pl.mx[0], pr.mn[0]), calc(pl.mx[1], pr.mn[1])});
	return p;
}
struct SegmentTree {
	Node t[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		// printf("build(%d, %d, %d)\n", x, l, r);
		if(l == r) {
			t[x].t[0] = t[x].t[1] = -LLINF;
			t[x].mx[0] = a[l], t[x].mx[1] = -LLINF;
			t[x].mn[0] = a[l], t[x].mn[1] = LLINF;
			printf("[%d..%d]: t = {%lld, %lld}, mn = {%lld, %lld}, mx = {%lld, %lld}\n", l, r, t[x].t[0], t[x].t[1], t[x].mn[0], t[x].mn[1], t[x].mx[0], t[x].mx[1]);
			return;
		}
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = update(t[x << 1], t[x << 1 | 1]);
		printf("[%d..%d]: t = {%lld, %lld}, mn = {%lld, %lld}, mx = {%lld, %lld}\n", l, r, t[x].t[0], t[x].t[1], t[x].mn[0], t[x].mn[1], t[x].mx[0], t[x].mx[1]);
	}
	Node query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		// printf("query(%d, %d, %d, %d, %d)\n", ql, qr, x, l, r);
		if(ql <= l && r <= qr) { return Node(t[x].mx, t[x].mn, t[x].t); }
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return update(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &Q);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		seg.build();
		while(Q--) {
			int l, r;
			scanf("%d%d", &l, &r);
			auto p = seg.query(l, r);
			printf("(t=%lld,%lld  mn=%lld,%lld  mx=%lld,%lld), ans = ", p.t[0], p.t[1], p.mn[0], p.mn[1], p.mx[0], p.mx[1]);
			printf("%lld\n", p.t[0] + p.t[1]);
		}
	}
	return 0;
} /*
1
5 3
5 3 2 8 4
1 5
1 4
2 5
*/