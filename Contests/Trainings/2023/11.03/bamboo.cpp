#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 998244353;

int n, m, K;

LL mod(LL x) { return x >= MOD ? x - MOD : x; }

struct SegmentTree {
	struct SegValue { LL sum, sumpre; int len; } t[N << 2];
	LL lazy[N << 2];
	SegValue calc(const SegValue &x, const SegValue &y) {
		SegValue z;
		z.len = x.len + y.len;
		z.sum = mod(x.sum + y.sum);
		z.sumpre = (x.sumpre + y.sumpre + x.sum * y.len) % MOD;
		return z;
	}
	void setlazy(int x, LL v) { (t[x].sum += t[x].len * v) %= MOD, (t[x].sumpre += (LL)t[x].len * (t[x].len + 1) / 2 % MOD * v) %= MOD, lazy[x] = mod(lazy[x] + v); }
	void lazydown(int x) { setlazy(x << 1, lazy[x]), setlazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	void build(int x = 1, int l = 1, int r = m) {
		t[x].len = r - l + 1;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void add(int ql, int qr, LL qv, int x = 1, int l = 1, int r = m) {
		if(ql > qr) return;
		// if(x == 1) printf("add [%d, %d] %lld\n", ql, qr, qv);
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	SegValue query(int ql, int qr, int x = 1, int l = 1, int r = m) {
		if(ql > qr) return {0, 0, 0};
		// if(x == 1) printf("query [%d, %d]\n", ql, qr);
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

std::vector<int> forbid[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

int main() {
#ifndef DEBUG
	freopen("bamboo.in", "r", stdin);
	freopen("bamboo.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &K);
	while(K--) { int u, v; scanf("%d%d", &u, &v); forbid[u].push_back(v); }
	seg.build();
	LL ans = 0;
	for(int i = n; i >= 1; i--) {
		std::sort(forbid[i].begin(), forbid[i].end());
		forbid[i].erase(std::unique(forbid[i].begin(), forbid[i].end()), forbid[i].end());
		LL P = inv(m - (int)forbid[i].size());
		(ans += P * seg.query(1, m - 1).sumpre) %= MOD;
		for(int j : forbid[i]) (ans += MOD - P * seg.query(1, j - 1).sum % MOD) %= MOD;
		LL E = P;
		seg.add(1, m, E);
		for(int j : forbid[i]) seg.add(j, j, MOD - E);
		// printf("%d(ans=%lld): ", i, ans); for(int j = 1; j <= m; j++) printf("%lld ", seg.query(j, j).sum); puts("");
	}
	printf("%lld\n", ans);
	return 0;
}