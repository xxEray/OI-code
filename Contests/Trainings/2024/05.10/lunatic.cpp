#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 5e4 + 5;
const int MAXQ = 5e5 + 5;

int n, m, Q;
struct Modify { int l, r, v; };
std::vector<Modify> a[N];

struct HistorySegmentTree {
	LL mx[N << 2], hmx[N << 2], add[N << 2], hadd[N << 2];
	bool clr[N << 2];
	void pushclr(int x) {
		if((x << 1 | 1) <= (n << 2)) {
			pushadd(x << 1, add[x], hadd[x]);
			pushadd(x << 1 | 1, add[x], hadd[x]);
		}
		add[x] = hadd[x] = 0, hmx[x] = mx[x], clr[x] = true;
	}
	void pushadd(int x, LL v, LL hv) {
		hmx[x] = std::max(hmx[x], mx[x] + hv), mx[x] += v;
		hadd[x] = std::max(hadd[x], add[x] + hv), add[x] += v;
	}
	void pushdown(int x) {
		if(clr[x]) {
			pushclr(x << 1), pushclr(x << 1 | 1);
			clr[x] = false;
		}
		pushadd(x << 1, add[x], hadd[x]), pushadd(x << 1 | 1, add[x], hadd[x]);
		add[x] = hadd[x] = 0;
	}
	void modify_add(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		// if(x == 1) printf("add [%d, %d] %lld\n", ql, qr, qv);
		if(ql <= l && r <= qr) { pushadd(x, qv, qv); return; }
		int mid = (l + r) >> 1;
		pushdown(x);
		if(ql <= mid) modify_add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify_add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		mx[x] = std::max(mx[x << 1], mx[x << 1 | 1]);
		hmx[x] = std::max(hmx[x << 1], hmx[x << 1 | 1]);
	}
	void modify_clear() { /* printf("clear\n"); */ pushclr(1); }
	LL query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return hmx[x];
		int mid = (l + r) >> 1;
		pushdown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::max(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

LL out[MAXQ];
struct Query { int ind, l, r, id; };
struct CatTree {
	std::vector<Query> tl[N << 2], tr[N << 2];
	void add_query(int ql, int qr, int vl, int vr, int vid, int x = 1, int l = 1, int r = n) {
		if(l == r) { tl[x].push_back({0, vl, vr, vid}); return; }
		int mid = (l + r) >> 1;
		if(qr <= mid) add_query(ql, qr, vl, vr, vid, x << 1, l, mid);
		else if(ql > mid) add_query(ql, qr, vl, vr, vid, x << 1 | 1, mid + 1, r);
		else {
			tl[x].push_back({ql, vl, vr, vid});
			tr[x].push_back({qr, vl, vr, vid});
		}
	}
	void solve(int x = 1, int l = 1, int r = n) {
		// printf("solve [%d, %d]\n", l, r);
		if(l == r) {
			for(auto [ll, rr, v] : a[l]) seg.modify_add(ll, rr, v);
			seg.modify_clear();
			for(auto [_, ll, rr, id] : tl[x]) out[id] = std::max(out[id], seg.query(ll, rr)); // , printf("query [%d, %d] = %lld\n", ll, rr, seg.query(ll, rr));
			// printf("solve [%d, %d] done\n", l, r);
			return;
		}
		int mid = (l + r) >> 1;
		solve(x << 1, l, mid);
		std::sort(tl[x].begin(), tl[x].end(), [&](const Query &p, const Query &q) { return p.ind > q.ind; });
		seg.modify_clear();
		for(int i = mid, j = 0; i >= l; i--) {
			while(j < (int)tl[x].size() && tl[x][j].ind == i) {
				auto &tmp = tl[x][j];
				out[tmp.id] = std::max(out[tmp.id], seg.query(tmp.l, tmp.r)); // , printf("query [%d, %d] = %lld\n", tmp.l, tmp.r, seg.query(tmp.l, tmp.r));
				j++;
			}
			for(auto [ll, rr, v] : a[i]) if(-v < 0) seg.modify_add(ll, rr, -v);
			for(auto [ll, rr, v] : a[i]) if(-v >= 0) seg.modify_add(ll, rr, -v);
		}
		for(int i = l; i <= mid; i++) for(auto [ll, rr, v] : a[i]) seg.modify_add(ll, rr, v);
		std::sort(tr[x].begin(), tr[x].end(), [&](const Query &p, const Query &q) { return p.ind < q.ind; });
		for(int i = mid + 1, j = 0; i <= r; i++) {
			for(auto [ll, rr, v] : a[i]) if(v < 0) seg.modify_add(ll, rr, v);
			if(i == mid + 1) seg.modify_clear();
			for(auto [ll, rr, v] : a[i]) if(v >= 0) seg.modify_add(ll, rr, v);
			while(j < (int)tr[x].size() && tr[x][j].ind == i) {
				auto &tmp = tr[x][j];
				out[tmp.id] = std::max(out[tmp.id], seg.query(tmp.l, tmp.r)); // , printf("query [%d, %d] = %lld\n", tmp.l, tmp.r, seg.query(tmp.l, tmp.r));
				j++;
			}
		}
		for(int i = r; i > mid; i--) for(auto [ll, rr, v] : a[i]) seg.modify_add(ll, rr, -v);
		solve(x << 1 | 1, mid + 1, r);
		// printf("solve [%d, %d] done\n", l, r);
	}
} cat;

int main() {
#ifndef DEBUG
	freopen("lunatic.in", "r", stdin);
	freopen("lunatic.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= m; i++) {
		int xl, xr, yl, yr, v;
		scanf("%d%d%d%d%d", &xl, &yl, &xr, &yr, &v);
		a[xl].push_back({yl, yr, v});
		a[xr + 1].push_back({yl, yr, -v});
	}
	for(int i = 1; i <= Q; i++) {
		int xl, xr, yl, yr;
		scanf("%d%d%d%d", &xl, &yl, &xr, &yr);
		cat.add_query(xl, xr, yl, yr, i);
	}
	cat.solve();
	for(int i = 1; i <= Q; i++) printf("%lld\n", out[i]);
	return 0;
} /*
5 5 5
1 1 4 5 4
4 1 4 1 100
1 3 3 3 3
1 1 5 5 8
2 4 4 5 8
2 1 2 1
4 1 5 4
1 2 3 5
2 1 5 3
1 3 5 5
*/