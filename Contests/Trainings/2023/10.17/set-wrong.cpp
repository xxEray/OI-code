#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, K;
int a[N];

struct SegmentTree {
	struct SegNode { int mn, rpos, lazy; } t[N << 2];
	SegNode calc(SegNode x, SegNode y) {
		SegNode z;
		z.mn = std::min(x.mn, y.mn);
		z.rpos = (y.mn == z.mn ? y.rpos : x.rpos);
		z.lazy = 0;
		return z;
	}
	void setlazy(int x, int v) { t[x].mn += v, t[x].lazy += v; }
	void lazydown(int x) { setlazy(x << 1, t[x].lazy), setlazy(x << 1 | 1, t[x].lazy), t[x].lazy = 0; }
	void build(int x = 1, int l = 1, int r = n) {
		t[x].mn = 0, t[x].rpos = l, t[x].lazy = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void add(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		if(x == 1) printf("add %d %d %d\n", ql, qr, qv);
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	SegNode query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(x == 1) printf("query %d %d\n", ql, qr);
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int last[N];
std::deque<int> qmx, qmn;

int main() {
#ifndef DEBUG
	freopen("set.in", "r", stdin);
	freopen("set.out", "w", stdout);
#endif
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	seg.build();
	int lb = 0;
	long long ans = 0;
	for(int i = 1; i <= n; i++) {
		while(!qmx.empty() && a[qmx.back()] <= a[i]) {
			int r = qmx.back();
			qmx.pop_back();
			int l = (qmx.empty() ? 1 : qmx.back() + 1);
			seg.add(l, r, -(a[r] + 1));
		}
		seg.add((qmx.empty() ? 1 : qmx.back() + 1), i, a[i] + 1);
		qmx.push_back(i);
		while(!qmn.empty() && a[qmn.back()] >= a[i]) {
			int r = qmn.back();
			qmn.pop_back();
			int l = (qmn.empty() ? 1 : qmn.back() + 1);
			seg.add(l, r, a[r]);
		}
		seg.add((qmn.empty() ? 1 : qmn.back() + 1), i, -a[i]);
		qmn.push_back(i);
		seg.add(last[a[i]] + 1, i, -1), last[a[i]] = i;
		if(i - K >= 1) {
			const auto &[v, p, _] = seg.query(1, i - K);
			if(!v) lb = std::max(lb, p);
			printf("%d: v = %d, p = %d\n", i, v, p);
		}
		ans += i - lb;
		printf("%d: ans = %lld\n", i, ans);
	}
	printf("%lld\n", ans);
	return 0;
}
