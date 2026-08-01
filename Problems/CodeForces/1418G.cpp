#include <cstdio>
#include <algorithm>

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int a[N];
int n;

struct SegmentTree {
	int t[N << 2], lazy[N << 2], cnt[N << 2];
	void set_lazy(int x, int v) { t[x] += v, lazy[x] += v; }
	void lazy_down(int x) { if(lazy[x]) set_lazy(x << 1, lazy[x]), set_lazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	void build(int x = 1, int l = 1, int r = n) { cnt[x] = r - l + 1; if(l < r) build(x << 1, l, (l + r) / 2), build(x << 1 | 1, (l + r) / 2 + 1, r); }
	void add(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		if(ql > qr) return;
		if(ql <= l && r <= qr) { set_lazy(x, qv); return; }
		lazy_down(x);
		int mid = (l + r) >> 1;
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
		cnt[x] = (t[x << 1] == t[x] ? cnt[x << 1] : 0) + (t[x << 1 | 1] == t[x] ? cnt[x << 1 | 1] : 0);
	}
	int min(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return t[x];
		lazy_down(x);
		int mid = (l + r) >> 1, ret = INF;
		if(ql <= mid) ret = std::min(ret, this->min(ql, qr, x << 1, l, mid));
		if(qr > mid) ret = std::min(ret, this->min(ql, qr, x << 1 | 1, mid + 1, r));
		return ret;
	}
	int min_count(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return cnt[x];
		lazy_down(x);
		int mid = (l + r) >> 1, ret1 = 0, ret2 = 0;
		if(ql <= mid) ret1 = min_count(ql, qr, x << 1, l, mid);
		if(qr > mid) ret2 = min_count(ql, qr, x << 1 | 1, mid + 1, r);
		return (t[x << 1] == t[x] ? ret1 : 0) + (t[x << 1 | 1] == t[x] ? ret2 : 0);
	}
} seg;

int tmp[N];
void preprocess() {
	for(int i = 1; i <= n; i++) tmp[i] = a[i];
	std::sort(tmp + 1, tmp + n + 1);
	int n_ = std::unique(tmp + 1, tmp + n + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i] = std::lower_bound(tmp + 1, tmp + n_ + 1, a[i]) - tmp;
}

int last[N], vis[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	preprocess();
	seg.build();
	int l = 1;
	long long ans = 0;
	for(int i = 1; i <= n; i++) {
		last[i] = vis[a[i]], vis[a[i]] = i;
		l = std::max(l, last[last[last[i]]] + 1);
		seg.add(last[last[last[i]]] + 1, last[last[i]], -1);
		seg.add(last[i] + 1, i, 1);
		if(seg.min(l, i) == 0) ans += seg.min_count(l, i);
	}
	printf("%lld\n", ans);
	return 0;
}