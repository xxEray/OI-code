#include <bits/stdc++.h>

// #ifndef DEBUG
// 	#define assert(...) ((void)0)
// #endif

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
int a[N];

int occ[N], prv[N];

LL sum[N];

struct Segment {
	LL k, b;
	Segment() : k(0), b(-LLINF) {}
	Segment(LL k_, LL b_) : k(k_), b(b_) {}
	LL at(LL x) const { return k * x + b; }
};
struct LiChaoTree {
	struct Node { Segment v; Node *ls, *rs; };
	static Node buff[N * 100];
	static Node *nw() { static int k = 1; return &buff[k++]; }
	Node *rt;
	inline void insert(const Segment &qv) { insert(qv, rt, 0, 40000000000); }
	void insert(Segment qv, Node *&x, LL l, LL r) {
		if(!x) x = nw();
		if(l == r) {
			if(x->v.at(l) < qv.at(l)) x->v = qv;
			return;
		}
		LL mid = (l + r) >> 1;
		if(x->v.at(mid) < qv.at(mid)) std::swap(x->v, qv);
		if(qv.at(l) > x->v.at(l)) insert(qv, x->ls, l, mid);
		if(qv.at(r) > x->v.at(r)) insert(qv, x->rs, mid + 1, r);
	}
	inline LL query(LL qx) const { return query(qx, rt, 0, 40000000000); }
	LL query(LL qx, Node *x, LL l, LL r) const {
		if(!x) return -LLINF;
		if(l == r) return x->v.at(qx);
		LL mid = (l + r) >> 1;
		if(qx <= mid) return std::max(query(qx, x->ls, l, mid), x->v.at(qx));
		else return std::max(query(qx, x->rs, mid + 1, r), x->v.at(qx));
	}
};
LiChaoTree::Node LiChaoTree::buff[N * 100];
struct SegmentTree {
	LiChaoTree t[N << 2];
	void insert(int qind, Segment qv, int x = 1, int l = 0, int r = n) {
		assert(0 <= qind && qind <= n);
		t[x].insert(qv);
		if(l == r) return;
		int mid = (l + r) >> 1;
		if(qind <= mid) insert(qind, qv, x << 1, l, mid);
		else insert(qind, qv, x << 1 | 1, mid + 1, r);
	}
	LL query(int ql, int qr, LL qx, int x = 1, int l = 0, int r = n) {
		assert(0 <= ql && ql <= qr && qr <= n), assert(0 <= qx && qx <= 40000000000);
		if(!x) return -LLINF;
		if(ql <= l && r <= qr) return t[x].query(qx);
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, qx, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, qx, x << 1 | 1, mid + 1, r);
		else return std::max(query(ql, qr, qx, x << 1, l, mid), query(ql, qr, qx, x << 1 | 1, mid + 1, r));
	}
} seg, seg2;

std::vector<std::array<int, 3>> inserted[N];
std::set<std::pair<int, int>> st;

LL f[N];

int main() {
#ifndef DEBUG
	freopen("calculate.in", "r", stdin);
	freopen("calculate.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	for(int i = 1; i <= n; i++) prv[i] = occ[a[i]], occ[a[i]] = i;
	int mn = n + 1;
	for(int i = 0; i <= n; i++) if(occ[i] < mn) i - 1 >= 0 ? (void)st.emplace(i - 1, mn) : (void)0, mn = occ[i];
	if(mn) st.emplace(n, mn);
	// printf("st: "); for(auto &&[x, y] : st) printf("(%d, %d) ", x, y); puts("");
	for(int i = n; i >= 1; i--) {
		int last = a[i], lastv = 0, val = 0;
		while(true) {
			auto it = st.lower_bound({a[i], 0});
			if(it == st.end() || it->second < prv[i]) break;
			if(!val) val = it->second;
			else inserted[i].push_back({it->second + 1, lastv, last + 1});
			lastv = it->second, last = it->first;
			st.erase(it);
		}
		if(!val) continue;
		auto it = st.lower_bound({a[i] - 1, 0});
		if(a[i] > 0 && (it == st.end() || it->first > a[i] - 1)) assert(val), st.emplace(a[i] - 1, val);
		inserted[i].push_back({prv[i] + 1, lastv, last + 1});
		if(prv[i]) st.emplace(last, prv[i]);
		std::reverse(inserted[i].begin(), inserted[i].end());
		// printf("inserted[%d]: ", i); for(auto &&[l, r, v] : inserted[i]) printf("(%d, %d, %d) ", l, r, v); puts("");
		// printf("st: "); for(auto &&[x, y] : st) printf("(%d, %d) ", x, y); puts("");
	}
	st.clear();
	f[0] = 0, seg2.insert(0, {-sum[0], f[0]});
	for(int i = 1; i <= n; i++) {
		// if(!inserted[i].empty()) {
		// 	auto it = st.lower_bound({inserted[i].front()[0], 0});
		// 	if(it != st.end()) st.erase(it);
		// }
		for(auto &&[l, r, v] : inserted[i]) {
			// printf("[%d, %d](%d) => %lld\n", l, r, v, seg2.query(l - 1, r - 1, v));
			assert(l <= r);
			seg.insert(l, {v, seg2.query(l - 1, r - 1, v)});
			auto it2 = st.lower_bound({l, 0});
			if(it2 != st.begin()) {
				it2--;
				if(it2->first < l - 1) {
					auto it = st.lower_bound({l, 0});
					assert(it != st.end() && it->second <= r);
					st.insert({l - 1, it->second});
				}
			}
			while(true) {
				auto it = st.lower_bound({l, 0});
				if(it != st.end() && it->first <= r) st.erase(it);
				else break;
			}
			st.emplace(r, v);
		}
		f[i] = seg.query(std::max(i - m + 1, 0), i, sum[i]);
		auto it = st.lower_bound({i - m + 1, 0});
		if(it != st.end()) f[i] = std::max(f[i], seg2.query(std::max(i - m, 0), it->first - 1, it->second) + sum[i] * it->second);
		int rb = (st.empty() ? 0 : st.rbegin()->first);
		f[i] = std::max(f[i], seg2.query(rb, i, 0));
		seg2.insert(i, {-sum[i], f[i]});
		// printf("f[%d] = %lld\n", i, f[i]);
		// printf("st: "); for(auto &&[x, y] : st) printf("(%d, %d) ", x, y); puts("");
	}
	printf("%lld\n", f[n]);
	return 0;
} /*
11 8
7 11 7 6 9 4 10 4 0 11 11 
*/