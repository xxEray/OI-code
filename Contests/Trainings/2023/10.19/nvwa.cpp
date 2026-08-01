#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

LL n;
int Q;

struct SegmentTree {
	struct SegVal { LL cnt[2], top[2]; };
	struct SegNode { int ls, rs; SegVal v; LL lazy; } t[N * 100];
	int tot;
	int nw(LL l, LL r) {
		tot++;
		t[tot].v.top[0] = ((r + (~r & 1)) - (l + (l & 1)) + 1) >> 1;
		t[tot].v.top[1] = ((r - (~r & 1)) - (l - (l & 1)) + 1) >> 1;
		assert(t[tot].v.top[0] + t[tot].v.top[1] == r - l + 1);
		t[tot].ls = t[tot].rs = t[tot].v.cnt[0] = t[tot].v.cnt[1] = t[tot].lazy = 0;
//		printf("%d nw [%lld, %lld]: %lld %lld\n", tot, l, r, t[tot].v.top[0], t[tot].v.top[1]);
		return tot;
	}
	void build() { nw(1, n); }
	SegVal calc(const SegVal &x, const SegVal &y) {
		SegVal z;
		z.cnt[0] = x.cnt[0] + y.cnt[0];
		z.cnt[1] = x.cnt[1] + y.cnt[1];
		z.top[0] = x.top[0] + y.top[0];
		z.top[1] = x.top[1] + y.top[1];
		return z;
	}
	void setlazy(int x, LL v, LL l, LL r) {
		t[x].v.cnt[0] += (v >> 1) * (r - l + 1), t[x].v.cnt[1] += (v >> 1) * (r - l + 1);
		if(v & 1) {
			t[x].v.cnt[0] += t[x].v.top[0], t[x].v.cnt[1] += t[x].v.top[1];
			std::swap(t[x].v.top[0], t[x].v.top[1]);
		}
		t[x].lazy += v;
	}
	void lazydown(int x, LL l, LL r, LL mid) { if(t[x].lazy) setlazy(t[x].ls, t[x].lazy, l, mid), setlazy(t[x].rs, t[x].lazy, mid + 1, r), t[x].lazy = 0; }
	void add(LL ql, LL qr, LL qv, int x = 1, LL l = 1, LL r = n) {
//		printf("add [%lld, %lld] %lld, %d %lld %lld\n", ql, qr, qv, x, l, r);
		if(ql <= l && r <= qr) { setlazy(x, qv, l, r); return; }
		LL mid = (l + r) >> 1;
		if(!t[x].ls) t[x].ls = nw(l, mid);
		if(!t[x].rs) t[x].rs = nw(mid + 1, r);
		lazydown(x, l, r, mid);
		if(ql <= mid) add(ql, qr, qv, t[x].ls, l, mid);
		if(qr > mid) add(ql, qr, qv, t[x].rs, mid + 1, r);
		t[x].v = calc(t[t[x].ls].v, t[t[x].rs].v);
//		printf("t[%d]: %lld %lld %lld %lld\n", x, t[x].v.cnt[0], t[x].v.cnt[1], t[x].v.top[0], t[x].v.top[1]);
	}
	SegVal query(LL ql, LL qr, int x = 1, LL l = 1, LL r = n) {
//		printf("query [%lld, %lld], %d %lld %lld\n", ql, qr, x, l, r);
		if(ql <= l && r <= qr) return t[x].v;
		LL mid = (l + r) >> 1;
		if(!t[x].ls) t[x].ls = nw(l, mid);
		if(!t[x].rs) t[x].rs = nw(mid + 1, r);
		lazydown(x, l, r, mid);
		if(qr <= mid) return query(ql, qr, t[x].ls, l, mid);
		else if(ql > mid) return query(ql, qr, t[x].rs, mid + 1, r);
		else return calc(query(ql, qr, t[x].ls, l, mid), query(ql, qr, t[x].rs, mid + 1, r));
	}
} seg;

struct Node { LL l, r, val; };
bool operator<(Node x, Node y) { return x.l == y.l ? x.r < y.r : x.l < y.l; }
std::set<Node> st;
LL ans, sum;

int main() {
#ifndef DEBUG
	freopen("nvwa.in", "r", stdin);
	freopen("nvwa.out", "w", stdout);
#endif
	scanf("%lld%d", &n, &Q);
	seg.build();
	while(Q--) {
		LL l, r, d;
		scanf("%lld%lld%lld", &l, &r, &d);
		l++;
		sum += (r - l + 1) * d;
		seg.add(l, r, d);
		while(true) {
			auto &&it = st.lower_bound({l, 0, 0});
			if(it != st.end() && it->r <= r) ans -= it->val, st.erase(it);
			else break;
		}
		{
			auto &&it = st.lower_bound({l, 0, 0});
			if(it != st.begin()) {
				it--;
				if(it->r >= l - 1) ans -= it->val, l = std::min(l, it->l), r = std::max(r, it->r), st.erase(it);
			}
		}
		{
			auto &&it = st.lower_bound({l, 0, 0});
			if(it != st.end() && it->l <= r + 1) ans -= it->val, r = std::max(r, it->r), st.erase(it);
		}
		auto &&ret = seg.query(l, r);
//		printf("ret = [%lld, %lld, %lld, %lld]\n", ret.cnt[0], ret.cnt[1], ret.top[0], ret.top[1]);
		LL val = std::min(ret.cnt[0], ret.cnt[1]);
		st.insert({l, r, val});
		ans += val;
		printf("%lld %lld\n", ans, sum - ans);
	}
	return 0;
}
