// WA on Sample

#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL MAXV = 1e18;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, Q;
LL a[N], b[N];

LL ans;
std::set<std::pair<int, int>> st;

struct SegmentTree {
	LL t[N << 2];
	LL initial;
	LL (*calc)(LL, LL);
	void build(int x = 1, int l = 1, int r = n) {
		t[x] = initial;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int qind, int qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = qv; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	LL query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} segsum, segmax;
LL mymax(LL x, LL y) { return x < y ? y : x; }
LL mysum(LL x, LL y) { return x + y; }

struct SegmentTree2 {
	struct SegNode { int sz; LL sum; int ls, rs; };
	SegNode t[N * 70];
	int cnt;
	int nw() { cnt++; t[cnt].sz = t[cnt].sum = t[cnt].ls = t[cnt].rs = 0; return cnt; }
	void build() { cnt = 0; nw(); }
	void modify(LL qind, int qv, int x = 1, LL l = 1, LL r = MAXV) {
		if(qind < 1) return;
		if(l == r) { t[x].sz += qv, t[x].sum += qv * l; return; }
		LL mid = (l + r) >> 1;
		if(qind <= mid) t[x].ls ? 0 : t[x].ls = nw(), modify(qind, qv, t[x].ls, l, mid);
		else t[x].rs ? 0 : t[x].rs = nw(), modify(qind, qv, t[x].rs, mid + 1, r);
		t[x].sz = t[t[x].ls].sz + t[t[x].rs].sz;
		t[x].sum = t[t[x].ls].sum + t[t[x].rs].sum;
	}
	LL sumall() { return t[1].sum; }
	int query(LL qv, int x = 1, LL l = 1, LL r = MAXV) {
		if(l == r) { assert(t[x].sum >= qv); return qv / l; }
		assert(x);
		LL mid = (l + r) >> 1;
		if(t[t[x].rs].sum >= qv) return query(qv, t[x].rs, l, mid);
		else return t[t[x].rs].sz + query(qv - t[t[x].rs].sum, t[x].ls, mid + 1, r);
	}
} segv;

void add(int i, LL v) {
	if(i < 1 || i >= n) return;
	auto it = --st.upper_bound({i, n + 1});
	int l = it->first, r = it->second;
	st.erase({l, r});
	segv.modify(-(segsum.query(l, r) - segmax.query(l, r)), -1);
	if(a[i] < 0 && a[i] + v > 0) {
		segv.modify(-(segsum.query(l, r) - segmax.query(l, r)), -1);
		if(i > l) st.insert({l, i - 1});
		if(i < r) st.insert({i + 1, r});
		st.insert({i, i});
		a[i] += v;
		ans += a[i];
		segmax.modify(i, a[i]), segsum.modify(i, a[i]);
		if(i > l) segv.modify(-(segsum.query(l, i - 1) - segmax.query(l, i - 1)), 1);
		if(i < r) segv.modify(-(segsum.query(i + 1, r) - segmax.query(i + 1, r)), 1);
	} else if(a[i] > 0 && a[i] + v < 0) {
		if(i > l) st.insert({l, i - 1});
		if(i < r) st.insert({i + 1, r});
		st.insert({i, i});
		ans -= a[i];
		a[i] += v;
		segmax.modify(i, a[i]), segsum.modify(i, a[i]);
	} else {
		if(a[i] > 0) ans -= a[i];
		else segv.modify(-(segsum.query(l, r) - segmax.query(l, r)), -1);
		a[i] += v;
		segmax.modify(i, a[i]), segsum.modify(i, a[i]);
		if(a[i] > 0) ans += a[i];
		else segv.modify(-(segsum.query(l, r) - segmax.query(l, r)), 1);
	}
}

int main() {
#ifndef DEBUG
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	segmax.initial = -LLINF, segmax.calc = mymax;
	segsum.initial = 0, segsum.calc = mysum;
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &Q);
		for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
		for(int i = n - 1; i >= 1; i--) a[i] = b[i + 1] - b[i];
		n--;
		segmax.build(), segsum.build(), segv.build();
		for(int i = 1; i <= n; i++) segmax.modify(i, a[i]), segsum.modify(i, a[i]);
		ans = 0;
		for(int i = 1; i <= n; ) {
			int j = i;
			while((a[j] > 0) == (a[i] > 0)) j++;
			st.insert({i, j - 1});
			if(a[i] > 0) ans += segsum.query(i, j - 1);
			else segv.modify(-(segsum.query(i, j - 1) - segmax.query(i, j - 1)), 1);
			i = j;
		}
		while(Q--) {
			int type;
			scanf("%d", &type);
			if(type == 0) {
				int l, r; LL c;
				scanf("%d%d%lld", &l, &r, &c);
				add(l - 1, c), add(r, -c);
			} else {
				printf("%lld ", ans);
				if(segv.sumall() < ans) printf("-1\n");
				else printf("%d\n", segv.query(ans));
			}
		}
	}
	return 0;
} /*
2
5 9
9 10 7 6 8
1
0 4 5 2
0 3 5 4`
1
0 2 5 -2
0 3 5 -3
0 4 5 -2
0 5 5 -4
1
4 3
2 4 3 5
1
0 3 3 3
1
*/