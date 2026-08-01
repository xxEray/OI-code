#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int n, m, Q;

std::vector<std::pair<int, int>> q[N];

struct SegmentTree1 {
	int t[N << 2], tag[N << 2];
	void setlazy(int x, int len) { t[x] = len - t[x], tag[x] ^= 1; }
	void lazydown(int x, int l, int r, int mid) { if(tag[x]) setlazy(x << 1, mid - l + 1), setlazy(x << 1 | 1, r - mid), tag[x] = 0; }
	void flip(int ql, int qr, int x = 1, int l = 1, int r = m) {
		// assert(1 <= ql && ql <= qr && qr <= m);
		if(ql <= l && r <= qr) { setlazy(x, r - l + 1); return; }
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(ql <= mid) flip(ql, qr, x << 1, l, mid);
		if(qr > mid) flip(ql, qr, x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] + t[x << 1 | 1];
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = m) {
		// assert(1 <= ql && ql <= qr && qr <= m);
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return query(ql, qr, x << 1, l, mid) + query(ql, qr, x << 1 | 1, mid + 1, r);
	}
} segc;

struct Seg2Node { int cnt; LL sumi, sumv; };
Seg2Node calc(Seg2Node x, Seg2Node y) {
	Seg2Node z;
	z.cnt = x.cnt + y.cnt, z.sumi = (x.sumi + y.sumi) % MOD;
	z.sumv = (x.sumv + x.cnt * y.sumi + y.sumv) % MOD;
	return z;
}
struct SegmentTree2 {
	Seg2Node t[N << 2];
	void add(int qind, LL qv, int x = 1, int l = 1, int r = n) {
		// assert(1 <= qind && qind <= n);
		if(l == r) {
			t[x].cnt += qv;
			(t[x].sumi += (LL)qv * l) %= MOD;
			t[x].sumv = (LL)t[x].cnt * (t[x].cnt - 1) / 2 % MOD * l % MOD;
			return;
		}
		int mid = (l + r) >> 1;
		if(qind <= mid) add(qind, qv, x << 1, l, mid);
		else add(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	Seg2Node query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		// assert(1 <= ql && ql <= qr && qr <= n);
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} segv;

struct Node {
	int l, r, val;
	Node() {}
	Node(int l_, int r_, int val_) : l(l_), r(r_), val(val_) {}
};
bool operator<(Node x, Node y) { return std::tie(x.l, x.r, x.val) < std::tie(y.l, y.r, y.val); }
std::set<Node> st;

std::vector<int> vct;

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= Q; i++) {
		int x1, x2, y1, y2;
		scanf("%d%d%d%d", &x1, &x2, &y1, &y2);
		q[x1].emplace_back(y1, y2), q[x2 + 1].emplace_back(y1, y2);
	}
	st.emplace(1, m, 0);
	LL ans = 0;
	for(int i = 1; i <= n; i++) {
		vct.clear();
		for(auto [l, r] : q[i]) vct.emplace_back(l), vct.emplace_back(r + 1);
		std::sort(vct.begin(), vct.end());
		std::vector<int> vct2;
		for(int x : vct)
			if(vct2.empty() || vct2.back() != x) vct2.emplace_back(x);
			else vct2.pop_back();
		vct.swap(vct2);
		auto solve = [&](int l, int r) {
			auto it = st.upper_bound({l, m + 1, 0});
			if(it != st.begin()) {
				--it;
				if(it->r >= l) {
					auto [vl, vr, vv] = *it;
					st.erase(it);
					if(vl < l) st.emplace(vl, l - 1, vv);
					if(vr > r) st.emplace(r + 1, vr, vv), st.emplace(l, r, vv);
					else st.emplace(l, vr, vv);
				}
			}
			it = st.upper_bound({r, m + 1, 0});
			if(it != st.begin()) {
				--it;
				if(it->r >= r) {
					auto [vl, vr, vv] = *it;
					st.erase(it);
					st.emplace(vl, r, vv);
					if(vr > r) st.emplace(r + 1, vr, vv);
				}
			}
			while(true) {
				it = st.lower_bound({l, 0, 0});
				if(it == st.end() || it->r > r) break;
				auto [vl, vr, vv] = *it;
				st.erase(it);
				int cn = segc.query(vl, vr);
				if(vv) segv.add(vv, -cn);
				segc.flip(vl, vr);
				cn = segc.query(vl, vr);
				segv.add(i, cn);
			}
			st.emplace(l, r, i);
		};
		if(vct.size() & 1) vct.emplace_back(m + 1);
		for(int j = 0; j < (int)vct.size(); j += 2) solve(vct[j], vct[j + 1] - 1);
		// printf("i = %d:\n", i);
		// printf("  st: "); for(auto [l, r, v] : st) printf("[%d, %d](%d) ", l, r, v); puts("");
		// printf("  segc: "); for(int j = 1; j <= m; j++) printf("%d ", segc.query(j, j)); puts("");
		// printf("  segv: "); for(int j = 1; j <= n; j++) printf("[%d]%d ", j, segv.query(j, j).cnt); puts("");
		auto res = segv.query(1, n);
		// printf("(cnt=%d, sumi=%lld, cntv=%lld, sumv=%lld)\n", res.cnt, res.sumi, (LL)res.cnt * (res.cnt - 1) / 2 % MOD, res.sumv);
		(ans += (i + 1) * (LL)res.cnt % MOD * m % MOD - res.sumi * m % MOD + MOD) %= MOD;
		(ans += MOD - (i + 1) * ((LL)res.cnt * (res.cnt - 1) / 2 % MOD) % MOD + res.sumv) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
} /*
3 3 2
1 2 3 3
3 3 3 3
*/