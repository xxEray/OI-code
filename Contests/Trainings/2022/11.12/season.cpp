#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;

std::vector<std::array<int, 3>> op[N];

int cl[N];
int color(int x) { return x == cl[x] ? x : cl[x] = color(cl[x]); }
void merge(int x, int y) { (x = color(x)) != (y = color(y)) ? cl[x] = y : 0; }
struct Node { int major, id, sid; LL val, scv; };
Node calc(Node x, Node y) {
	Node z;
	z.scv = LLINF;
	if(x.val > y.val) z.major = y.major, z.val = y.val, z.id = y.id;
	else z.major = x.major, z.val = x.val, z.id = x.id;
	if(x.major == z.major) { if(x.scv < z.scv) z.scv = x.scv, z.sid = x.sid; }
	else { if(x.val < z.scv) z.scv = x.val, z.sid = x.id; }
	if(y.major == z.major) { if(y.scv < z.scv) z.scv = y.scv, z.sid = y.sid; }
	else { if(y.val < z.scv) z.scv = y.val, z.sid = y.id; }
	return z;
}
std::pair<LL, int> get(Node x, int diff) { return x.major == diff ? std::make_pair(x.scv, x.sid) : std::make_pair(x.val, x.id); }
struct SegmentTree {
	Node t[N << 2];
	LL lazy[N << 2];
	void set_lazy(int x, LL v) { t[x].val += v, t[x].scv += v, lazy[x] += v; }
	void lazy_down(int x) {
		set_lazy(x << 1, lazy[x]), set_lazy(x << 1 | 1, lazy[x]);
		lazy[x] = 0;
	}
	void build(int x = 1, int l = 1, int r = n) {
		lazy[x] = 0;
		if(l == r) { t[x] = (Node){color(l), l, 0, 0, LLINF}; return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	void modify(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { set_lazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	Node query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

std::pair<LL, int> out[N];

int main() {
	// freopen("season.in", "r", stdin);
	// freopen("season.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int x1, x2, y1, y2, w;
		scanf("%d%d%d%d%d", &x1, &x2, &y1, &y2, &w);
		op[y1].push_back({x1, x2, w});
		op[y2 + 1].push_back({x1, x2, -w});
		op[x1].push_back({y1, y2, w});
		op[x2 + 1].push_back({y1, y2, -w});
	}
	for(int i = 1; i <= n; i++) cl[i] = i;
	int scc = n;
	LL ans = 0;
	while(scc > 1) {
		seg.build();
		for(int i = 1; i <= n; i++) out[i] = {LLINF, 0};
		for(int i = 1; i <= n; i++) {
			for(auto v : op[i]) seg.modify(v[0], v[1], v[2]);
			out[color(i)] = std::min(out[color(i)], get(seg.query(1, n), color(i)));
		}
		for(int u = 1; u <= n; u++) if(out[u].first < LLINF) {
			LL w = out[u].first;
			int v = out[u].second;
			if(color(u) != color(v)) merge(u, v), scc--, ans += w;
		}
	}
	printf("%lld\n", ans);
	return 0;
}