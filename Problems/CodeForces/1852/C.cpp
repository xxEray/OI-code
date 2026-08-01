#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, K;
int a[N];
bool b[N];

struct SegmentTree {
	LL t[N << 2], lazy[N << 2];
	void setlazy(int x, LL v) { t[x] += v, lazy[x] += v; }
	void lazydown(int x) { setlazy(x << 1, lazy[x]), setlazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	void build(int x = 1, int l = 1, int r = n + 1) {
		t[x] = lazy[x] = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void add(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n + 1) {
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
	}
	LL query(int ql, int qr, int x = 1, int l = 1, int r = n + 1) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::min(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		a[n + 1] = 0;
		for(int i = n + 1; i >= 1; i--) a[i] = (a[i] - a[i - 1] + K) % K;
		std::set<std::pair<LL, int>> st0, st1;
		seg.build();
		LL now = 0;
		for(int i = 1; i <= n + 1; i++)
			if(a[i] <= K - a[i]) {
				now -= a[i], seg.add(i, i, now);
				st0.insert({(K - a[i]) % K - a[i], i});
				b[i] = 0;
			} else {
				now += K - a[i], seg.add(i, i, now);
				st1.insert({a[i] - (K - a[i]) % K, i});
				b[i] = 1;
				while(now > 0) {
					int x = st1.begin()->second;
					st1.erase(st1.begin());
					b[x] = 0, seg.add(x, i, -K), now -= K;
				}
			}
		while(now < 0) {
			int x = st0.begin()->second;
			st0.erase(st0.begin());
			if(seg.query(x, n + 1) > -K) continue;
			b[x] = 1, seg.add(x, n + 1, K), now += K;
		}
		LL ans = 0;
		for(int i = 1; i <= n + 1; i++) if(b[i]) ans += (K - a[i]) % K;
		printf("%lld\n", ans);
	}
	return 0;
}