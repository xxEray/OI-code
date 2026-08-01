#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int n;
int p[N], q[N];

struct Node { int l, r, v; };
std::vector<Node> vct[N];
int c;

std::set<int> zero, one;

struct SegmentTree {
	int t[N << 2], lazy[N << 2];
	LL sum[N << 2];
	void setlazy(int x, int v) { t[x] += v, lazy[x] += v; }
	void lazydown(int x) { setlazy(x << 1, lazy[x]), setlazy(x << 1 | 1, lazy[x]); lazy[x] = 0; }
	void add(int ql, int qr, int qv, int x = 1, int l = 0, int r = n) {
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
		sum[x] = ((t[x] == t[x << 1]) * sum[x << 1] + (t[x] == t[x << 1 | 1]) * sum[x << 1 | 1]) % MOD;
	}
	void setf(int qind, LL qv, int x = 1, int l = 0, int r = n) {
		if(l == r) { sum[x] = qv; return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qind <= mid) setf(qind, qv, x << 1, l, mid);
		else setf(qind, qv, x << 1 | 1, mid + 1, r);
		sum[x] = ((t[x] == t[x << 1]) * sum[x << 1] + (t[x] == t[x << 1 | 1]) * sum[x << 1 | 1]) % MOD;
	}
	LL query(int ql, int qr, int x = 1, int l = 0, int r = n) {
		if(ql <= l && r <= qr) return t[x] == 0 ? sum[x] : 0;
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return (query(ql, qr, x << 1, l, mid) + query(ql, qr, x << 1 | 1, mid + 1, r)) % MOD;
	}
} seg;

LL f[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &p[i]), q[p[i]] = i;
	for(int i = 1; i <= n; i++) one.insert(i);
	zero.insert(0), zero.insert(n + 1), one.insert(0), one.insert(n + 1);
	for(int i = 1; i <= n; i++) {
		one.erase(q[i]), zero.insert(q[i]);
		int l = *--one.lower_bound(q[i]) + 1;
		int mid = *one.upper_bound(q[i]) - 1;
		if(mid == n) continue;
		int r = *zero.upper_bound(mid) - 1;
		// printf("l = %d, mid = %d, r = %d\n", l, mid, r);
		// [mid + 1 .. r], [l - 1 .. mid - 1]
		// printf("%d: disable ([%d..%d], [%d..%d])\n", i, mid + 1, r, l - 1, mid - 1);
		vct[mid + 1].push_back({l - 1, mid - 1, 1}), vct[r + 1].push_back({l - 1, mid - 1, -1});
	}
	f[0] = 1, seg.setf(0, f[0]);
	for(int i = 1; i <= n; i++) {
		for(auto &t : vct[i]) seg.add(t.l, t.r, t.v);
		f[i] = seg.query(0, n);
		seg.setf(i, f[i]);
		// printf("f[%d] = %lld\n", i, f[i]);
	}
	printf("%lld\n", f[n]);
	return 0;
} /*
4
3 2 4 1
*/