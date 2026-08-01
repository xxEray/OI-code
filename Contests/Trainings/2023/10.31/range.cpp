#include <bits/stdc++.h>

typedef long long LL;

const int N = 8e5 + 5;
const int MAXQ = 2e6 + 5;
const LL MOD = 998244353;

int n, Q;
struct Node { int l, r; } a[N];
struct Query { int l, r, id; } q[MAXQ];

LL out[MAXQ];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

struct BIT {
	void add(int x, LL v) { while(x <= n) (t[x] += v) %= MOD, x += x & -x; }
	LL query(int l, int r) { return (query(r) - query(l - 1) + MOD) % MOD; }
private:
	LL t[N];
	LL query(int r) { LL ret = 0; while(r) (ret += t[r]) %= MOD, r -= r & -r; return ret; }
};

struct HistorySum {
	BIT ts, ti;
	int t;
	void add(int x, LL v) { ti.add(x, v), ts.add(x, (MOD - v) * (t - 1 + MOD) % MOD);}
	void new_copy() { t++; }
	LL query(int l, int r) { return (ti.query(l, r) * t % MOD + ts.query(l, r)) % MOD; }
};

struct SuffixHistorySum {
	HistorySum t1, t2;
	void add(int x, LL v) { if(x) /* printf("add %d %lld\n", x, v),  */t1.add(x, v), t2.add(x, x * v % MOD); }
	void new_copy() { /* printf("new_copy\n");  */t1.new_copy(), t2.new_copy(); }
	LL query(int l, int r) { return /* printf("query %d %d\n", l, r),  */(t2.query(l, r) - t1.query(l, r) * (l - 1 + MOD) % MOD + MOD) % MOD; }
} seg;

struct Segment { int l, r, v; };
bool operator<(const Segment &x, const Segment &y) { return x.l == y.l ? (x.r == y.r ? x.v < y.v : x.r < y.r) : x.l < y.l; }
std::set<Segment> st;

int main() {
#ifndef DEBUG
	freopen("range.in", "r", stdin);
	freopen("range.out", "w", stdout);
#endif
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r);
	for(int i = 1; i <= Q; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	std::sort(q + 1, q + Q + 1, [&](Query x, Query y) { return x.r < y.r; });
	st.insert({1, n, 0});
	for(int i = 1, j = 1; i <= n; i++) {
		seg.new_copy();
		int l = a[i].l, r = a[i].r;
		while(true) {
			auto it = st.lower_bound({l, 0, 0});
			if(it != st.end() && it->r <= r) {
				seg.add(it->v, MOD - (it->r - it->l));
				st.erase(it);
			} else break;
		}
		{
			auto it = st.lower_bound({l, 0, 0});
			if(it != st.begin()) {
				it--;
				if(it->r >= l) {
					if(it->r > r) {
						int vl = it->l, vr = it->r, vv = it->v;
						seg.add(vv, MOD - (r - l));
						st.erase(it);
						if(vl < l) st.insert({vl, l, vv});
						if(r < vr) st.insert({r, vr, vv});
					} else {
						int vl = it->l, vv = it->v;
						seg.add(vv, MOD - (it->r - l));
						st.erase(it);
						if(vl < l) st.insert({vl, l, vv});
					}
				}
			}
		}
		{
			auto it = st.lower_bound({l, 0, 0});
			if(it != st.end() && it->l <= r) {
				int vr = it->r, vv = it->v;
				seg.add(vv, MOD - (r - it->l));
				st.erase(it);
				if(r < vr) st.insert({r, vr, vv});
			}
		}
		st.insert({l, r, i});
		seg.add(i, r - l);
		while(j <= Q && q[j].r == i) out[q[j].id] = seg.query(q[j].l, q[j].r) * inv(((LL)(q[j].r - q[j].l + 1) * (q[j].r - q[j].l) / 2 + (q[j].r - q[j].l + 1)) % MOD) % MOD, j++;
	}
	for(int i = 1; i <= Q; i++) printf("%lld\n", out[i]);
	return 0;
}