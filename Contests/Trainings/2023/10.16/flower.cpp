#include <bits/stdc++.h>

const int N = 3e4 + 5;
const int MAXQ = 3e5 + 5;
const int INF = 0x3f3f3f3f;

#define SZ(x) ((int)(x).size())

int n, Q;
std::pair<int, int> a[N];
struct Query { int l, r, id; } q[MAXQ];
bool operator<(Query x, Query y) { return x.r < y.r; }
std::vector<std::pair<int, int>> vct;

inline int distance(int i, int j) { return !i || !j ? INF : std::max(std::abs(a[i].first - a[j].first), std::abs(a[i].second - a[j].second)); }

struct SegmentTree {
	struct SegNode { int mnl, mnr, mn, ell, elr, el, erl, err, er; } t[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		t[x] = {0, 0, INF, 0, 0, INF, 0, 0, INF};
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	SegNode calc(SegNode x, SegNode y) {
		SegNode z;
		if(x.mn > y.mn) std::swap(x, y);
		z.mnl = x.mnl, z.mnr = x.mnr, z.mn = x.mn;
		z.ell = x.ell, z.elr = x.elr, z.el = x.el;
		if(y.mnl != x.mnl && y.mnr != x.mnl && z.el > y.mn) z.ell = y.mnl, z.elr = y.mnr, z.el = y.mn;
		if(y.ell != x.mnl && y.elr != x.mnl && z.el > y.el) z.ell = y.ell, z.elr = y.elr, z.el = y.el;
		if(y.erl != x.mnl && y.err != x.mnl && z.el > y.er) z.ell = y.erl, z.elr = y.err, z.el = y.er;
		z.erl = x.erl, z.err = x.err, z.er = x.er;
		if(y.mnl != x.mnr && y.mnr != x.mnr && z.er > y.mn) z.erl = y.mnl, z.err = y.mnr, z.er = y.mn;
		if(y.ell != x.mnr && y.elr != x.mnr && z.er > y.el) z.erl = y.ell, z.err = y.elr, z.er = y.el;
		if(y.erl != x.mnr && y.err != x.mnr && z.er > y.er) z.erl = y.erl, z.err = y.err, z.er = y.er;
		return z;
	}
	void modify(int qind, int qvl, int qvr, int x = 1, int l = 1, int r = n) {
		// if(x == 1) printf("[%d] insert (%d, %d)\n", qind, qvl, qvr);
		if(l == r) { t[x] = calc(t[x], (SegNode){qvl, qvr, distance(qvl, qvr), 0, 0, INF, 0, 0, INF}); return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qvl, qvr, x << 1, l, mid);
		else modify(qind, qvl, qvr, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	SegNode query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		// if(x == 1) printf("query [%d, %d]\n", ql, qr);
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int out[MAXQ];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].first, &a[i].second);
	scanf("%d", &Q);
	for(int i = 1; i <= Q; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	std::sort(q + 1, q + Q + 1);
	for(int k = 0; k <= 28; k++) {
		std::map<std::pair<int, int>, std::vector<int>> mp;
		for(int i = 1; i <= n; i++) mp[{a[i].first >> k, a[i].second >> k}].push_back(i);
		for(const auto &[pr, vc] : mp) {
			const auto &[x, y] = pr;
			for(int ox : {-1, 0, 1}) for(int oy : {-1, 0, 1}) if(mp.count({x + ox, y + oy})) {
				const auto &vc2 = mp[{x + ox, y + oy}];
				for(int i = 0, j = 0; i < SZ(vc); i++) {
					while(j < SZ(vc2) && vc2[j] < vc[i]) j++;
					for(int t = j - 1; t >= std::max(0, j - 3); t--) vct.push_back({vc[i], vc2[t]});
				}
				for(int i = SZ(vc) - 1, j = SZ(vc2) - 1; i >= 0; i--) {
					while(j >= 0 && vc2[j] > vc[i]) j--;
					for(int t = j + 1; t <= std::min(SZ(vc2) - 1, j + 3); t++) vct.push_back({vc[i], vc2[t]});
				}
			}
		}
	}
	for(auto &[x, y] : vct) if(x > y) std::swap(x, y);
	std::sort(vct.begin(), vct.end(), [&](std::pair<int, int> x, std::pair<int, int> y) { return x.second == y.second ? x.first < y.first : x.second < y.second; });
	vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
	// for(const auto &[x, y] : vct) printf("(%d, %d)\n", x, y);
	seg.build();
	for(int i = 1, j = 1, k = 0; i <= n; i++) {
		while(k < SZ(vct) && vct[k].second == i) seg.modify(vct[k].first, vct[k].first, vct[k].second), k++;
		while(j <= Q && q[j].r == i) {
			auto &&p = seg.query(q[j].l, q[j].r);
			// printf("%d: (%d, %d) (%d, %d) (%d, %d)\n", q[j].id, p.mnl, p.mnr, p.ell, p.elr, p.erl, p.err);
			out[q[j].id] = std::max(p.el, p.er);
			j++;
		}
	}
	for(int i = 1; i <= Q; i++) printf("%d\n", out[i]);
	return 0;
} /*
6
1 2
3 2
5 7
9 9
11 14
12 1
10
1 3
1 4
1 5
1 6
2 4
2 5
2 6
3 5
3 6
4 6
*/