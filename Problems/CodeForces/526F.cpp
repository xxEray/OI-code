#include <cstdio>
#include <algorithm>

const int N = 3e5 + 5;
const int INF = 0x3f3f3f3f;

int a[N];
int n;

std::vector<int> mnq, mxq;

struct SegmentTree {
	int t[N << 2], lazy[N << 2], cnt[N << 2];
	void set_lazy(int x, int v) { t[x] += v, lazy[x] += v; }
	void lazy_down(int x) { if(lazy[x]) set_lazy(x << 1, lazy[x]), set_lazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	void build(int x = 1, int l = 1, int r = n) {
		cnt[x] = r - l + 1;
		if(l < r) { int mid = (l + r) >> 1; build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r); }
	}
	void add(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		// if(x == 1 && qv != INF && qv != -INF) printf("add(%d, %d, %d)\n", ql, qr, qv);
		if(ql <= l && r <= qr) { set_lazy(x, qv); return; }
		lazy_down(x);
		int mid = (l + r) >> 1;
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
		cnt[x] = (t[x] == t[x << 1] ? cnt[x << 1] : 0) + (t[x] == t[x << 1 | 1] ? cnt[x << 1 | 1] : 0);
	}
	int min_count(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) {
			// if(x == 1) printf("min_count(%d, %d) = %d\n", ql, qr, cnt[x]);
			return cnt[x];
		}
		lazy_down(x);
		int mid = (l + r) >> 1, retl = 0, retr = 0;
		if(ql <= mid) retl = min_count(ql, qr, x << 1, l, mid);
		if(qr > mid) retr = min_count(ql, qr, x << 1 | 1, mid + 1, r);
		// if(x == 1) printf("min_count(%d, %d) = %d\n", ql, qr, (t[x] == t[x << 1] ? retl : 0) + (t[x] == t[x << 1 | 1] ? retr : 0));
		return (t[x] == t[x << 1] ? retl : 0) + (t[x] == t[x << 1 | 1] ? retr : 0);
	}
} seg;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) { int x, y; scanf("%d%d", &x, &y); a[x] = y; }
	seg.build();
	long long ans = 0;
	#define last(x) ((int)(x).size() == 1 ? 0 : (x)[(int)(x).size() - 2])
	seg.add(1, n, INF);
	for(int i = 1; i <= n; i++) {
		seg.add(i, i, -INF);
		// printf("Case %d\n", i);
		while(!mxq.empty() && a[mxq.back()] <= a[i]) seg.add(last(mxq) + 1, mxq.back(), -a[mxq.back()]), mxq.pop_back();
		while(!mnq.empty() && a[mnq.back()] >= a[i]) seg.add(last(mnq) + 1, mnq.back(), +a[mnq.back()]), mnq.pop_back();
		mxq.push_back(i), seg.add(last(mxq) + 1, i, +a[i]);
		mnq.push_back(i), seg.add(last(mnq) + 1, i, -a[i]);
		if(i > 1) seg.add(1, i - 1, -1);
		ans += seg.min_count(1, i); 
	}
	printf("%lld\n", ans); 
	return 0;
}