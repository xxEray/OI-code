#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n, K, Q;
int a[N];

int f[N];
struct SegmentTree1 {
	int t[N << 2];
	void build(int x = 1, int l = 0, int r = n + 1) {
		if(l == r) { t[x] = a[l]; return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	int findld(int qr, int qv, int x = 1, int l = 0, int r = n + 1) {
		if(l == r) return t[x] < qv ? l : INF;
		int mid = (l + r) >> 1;
		if(qr <= mid) return findld(qr, qv, x << 1, l, mid);
		else {
			int ret;
			if(qr > r && t[x << 1 | 1] < qv) ret = mid + 1;
			else ret = findld(qr, qv, x << 1 | 1, mid + 1, r);
			if(ret == mid + 1) {
				if(t[x << 1] < qv) return l;
				else return std::min(ret, findld(qr, qv, x << 1, l, mid));
			} else return ret;
		}
	}
	int findrd(int ql, int qv, int x = 1, int l = 0, int r = n + 1) {
		if(l == r) return t[x] < qv ? l : -INF;
		int mid = (l + r) >> 1;
		if(ql > mid) return findrd(ql, qv, x << 1 | 1, mid + 1, r);
		else {
			int ret;
			if(ql < l && t[x << 1] < qv) ret = mid;
			else ret = findrd(ql, qv, x << 1, l, mid);
			if(ret == mid) {
				if(t[x << 1 | 1] < qv) return r;
				else return std::max(ret, findrd(ql, qv, x << 1 | 1, mid + 1, r));
			} else return ret;
		}
	}
	int findlu(int qr, int qv, int x = 1, int l = 0, int r = n + 1) { return findld(qr, qv + 1) - 1; }
	int findru(int ql, int qv, int x = 1, int l = 0, int r = n + 1) { return findrd(ql, qv + 1) + 1; }
	void set(int qind, int qv, int x = 1, int l = 0, int r = n + 1) {
		if(l == r) { t[x] = qv; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) set(qind, qv, x << 1, l, mid);
		else set(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
} sega;
struct SegmentTree2 {
	LL t[N << 2], lazy[N << 2];
	void build(int x = 1, int l = 0, int r = n + 1) {
		lazy[x] = 0;
		if(l == r) { t[x] = f[l]; return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] + t[x << 1 | 1];
	}
	void setlazy(int x, LL v, int len) { lazy[x] += v, t[x] += v * len; }
	void lazydown(int x, int l, int r, int mid) {
		setlazy(x << 1, lazy[x], mid - l + 1);
		setlazy(x << 1 | 1, lazy[x], r - mid);
		lazy[x] = 0;
	}
	void add(int ql, int qr, LL qv, int x = 1, int l = 0, int r = n + 1) {
		if(ql <= l && r <= qr) { setlazy(x, qv, r - l + 1); return; }
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] + t[x << 1 | 1];
	}
	LL query(int ql, int qr, int x = 1, int l = 0, int r = n + 1) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return query(ql, qr, x << 1, l, mid) + query(ql, qr, x << 1 | 1, mid + 1, r);
	}
	void set(int x, LL v) { add(x, x, v - get(x)); }
	LL get(int x) { return query(x, x); }
} segf;

std::vector<int> tin[N];
void getf() {
	std::set<int> st;
	std::map<int, int> mp;
	f[0] = f[n + 1] = -1, st.insert(0), st.insert(n + 1);
	int cnt = 0;
	for(int i = 1; i <= n; i++) mp[a[i]] = 0;
	for(auto &p : mp) p.second = ++cnt;
	for(int i = 1; i <= n; i++) tin[mp[a[i]]].push_back(i);
	for(auto it = mp.rbegin(); it != mp.rend(); it++) {
		auto &vct = tin[it->second];
		for(int i : vct) {
			auto itt = st.lower_bound(i);
			f[i] = std::max(f[*itt], f[*std::prev(itt)]) + 1;
		}
		for(int i : vct) st.insert(i);
	}
	// printf("f: "); for(int i = 1; i <= n; i++) printf("%d ", f[i]); puts("");
}

int main() {
#ifndef DEBUG
	freopen("summer.in", "r", stdin);
	freopen("summer.out", "w", stdout);
#endif
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &Q);
	a[0] = a[n + 1] = INF;
	getf();
	sega.build(), segf.build();
	while(Q--) {
		int x, l, r;
		scanf("%d%d%d", &x, &l, &r);
		if(a[x] == a[x + 1]) { printf("%lld\n", segf.query(l, r) * K + (LL)(r - l + 1) * (n - 1)); continue; }
		if(x > 1 && a[x - 1] < std::min(a[x], a[x + 1])) {
			int p = sega.findld(x - 1, std::min(a[x], a[x + 1]));
			if(a[p - 1] != std::min(a[x], a[x + 1])) segf.add(p, x - 1, (a[x] < a[x + 1] ? -1 : 1));
		}
		if(x + 1 < n && a[x + 2] < std::min(a[x], a[x + 1])) {
			int q = sega.findrd(x + 2, std::min(a[x], a[x + 1]));
			if(a[q + 1] != std::min(a[x], a[x + 1])) segf.add(x + 2, q, (a[x] < a[x + 1] ? 1 : -1));
		}
		sega.set(x, a[x + 1]), sega.set(x + 1, a[x]);
		std::swap(a[x], a[x + 1]);
		if(a[x] > a[x + 1]) {
			segf.set(x, std::max(segf.get(sega.findlu(x, a[x])), segf.get(sega.findru(x, a[x]))) + 1);
			segf.set(x + 1, std::max(segf.get(sega.findlu(x + 1, a[x + 1])), segf.get(sega.findru(x + 1, a[x + 1]))) + 1);
		} else {
			segf.set(x + 1, std::max(segf.get(sega.findlu(x + 1, a[x + 1])), segf.get(sega.findru(x + 1, a[x + 1]))) + 1);
			segf.set(x, std::max(segf.get(sega.findlu(x, a[x])), segf.get(sega.findru(x, a[x]))) + 1);
		}
		// printf("a: "); for(int i = 1; i <= n; i++) printf("%d ", a[i]); puts("");
		// printf("f: "); for(int i = 1; i <= n; i++) printf("%lld ", segf.get(i)); puts("");
		printf("%lld\n", segf.query(l, r) * K + (LL)(r - l + 1) * (n - 1));
	}
	return 0;
} /*
7 7
4 3 2 1 2 3 4
5
1 1 3
2 3 5
3 2 5
4 1 5
5 1 5
*/