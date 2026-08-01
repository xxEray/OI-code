#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;

int last[N], a[N];
std::vector<std::array<int, 3>> op[N];
std::vector<int> q[N];

LL out[N];

struct SegmentTree {
	LL mn[N << 2], sc[N << 2], cnt[N << 2], sum[N << 2], hsum[N << 2], tag1[N << 2], tag2[N << 2], tag3[N << 2];
	void pushtag1(int x, LL v) {
		mn[x] += v, tag1[x] += v;
	}
	void pushtag2(int x, LL v) {
		hsum[x] += mn[x] * cnt[x] * v + sum[x] * v;
		tag2[x] += v, tag3[x] += tag1[x] * v;
	}
	void pushtag3(int x, LL v) {
		hsum[x] += v * cnt[x];
		tag3[x] += v;
	}
	void pushdown(int x) {
		pushtag2(x << 1, tag2[x]), pushtag2(x << 1 | 1, tag2[x]), tag2[x] = 0;
		if(mn[x << 1] <= mn[x << 1 | 1]) pushtag3(x << 1, tag3[x]);
		if(mn[x << 1 | 1] <= mn[x << 1]) pushtag3(x << 1 | 1, tag3[x]);
		tag3[x] = 0;
		if(mn[x << 1] <= mn[x << 1 | 1]) pushtag1(x << 1, tag1[x]);
		if(mn[x << 1 | 1] <= mn[x << 1]) pushtag1(x << 1 | 1, tag1[x]);
		tag1[x] = 0;
	}
	void pushup(int x) {
		mn[x] = std::min(mn[x << 1], mn[x << 1 | 1]);
		cnt[x] = (mn[x] == mn[x << 1]) * cnt[x << 1] + (mn[x] == mn[x << 1 | 1]) * cnt[x << 1 | 1];
		sc[x] = std::min(mn[x] == mn[x << 1] ? sc[x << 1] : mn[x << 1], mn[x] == mn[x << 1 | 1] ? sc[x << 1 | 1] : mn[x << 1 | 1]);
		sum[x] = sum[x << 1] + sum[x << 1 | 1] + (mn[x << 1] >= sc[x]) * mn[x << 1] * cnt[x << 1] + (mn[x << 1 | 1] >= sc[x]) * mn[x << 1 | 1] * cnt[x << 1 | 1];
		hsum[x] = hsum[x << 1] + hsum[x << 1 | 1];
	}
	void build(int x = 1, int l = 1, int r = m) {
		mn[x] = 0, cnt[x] = r - l + 1, sc[x] = LLINF, sum[x] = 0, hsum[x] = 0, tag1[x] = tag2[x] = tag3[x] = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void copy() { pushtag2(1, 1); }
	void modify(int ql, int qr, LL qv, int x = 1, int l = 1, int r = m) {
		assert(1 <= ql && ql <= qr && qr <= m);
		if(mn[x] >= qv) return;
		if(ql <= l && r <= qr && sc[x] > qv) { pushtag1(x, qv - mn[x]); return; }
		int mid = (l + r) >> 1;
		pushdown(x);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		pushup(x);
	}
	LL query(int ql, int qr, int x = 1, int l = 1, int r = m) {
		assert(1 <= ql && ql <= qr && qr <= m);
		if(ql <= l && r <= qr) return hsum[x];
		int mid = (l + r) >> 1;
		pushdown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return query(ql, qr, x << 1, l, mid) + query(ql, qr, x << 1 | 1, mid + 1, r);
	}
} seg;

int main() {
#ifndef DEBUG
	freopen("array.in", "r", stdin);
	freopen("array.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int t = 1; t <= m; t++) {
		int x, p;
		scanf("%d%d", &x, &p);
		if(last[x]) op[x].push_back({last[x], t - 1, a[x]});
		last[x] = t, a[x] = p;
		q[x].emplace_back(t);
	}
	for(int i = 1; i <= n; i++) if(last[i]) op[i].push_back({last[i], m, a[i]});
	seg.build();
	for(int i = 1; i <= n; i++) {
		for(auto [l, r, v] : op[i]) seg.modify(l, r, v); // , printf("modify(%d, %d, %d)\n", l, r, v);
		seg.copy();
		for(auto x : q[i]) out[x] = seg.query(1, x); // , printf("query(%d, %d) = %lld\n", 1, x, out[x]);
	}
	for(int i = 1; i <= m; i++) printf("%lld\n", out[i]);
	return 0;
} /*
5 6
3 4
1 2
2 4
1 4
3 5
1 2
*/