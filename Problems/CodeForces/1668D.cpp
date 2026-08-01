#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int a[N];
int n;

int pre[N];
LL presum[N];
LL tmp[N];
int seg_tot;
void discrete() {
	for(int i = 0; i <= n; i++) tmp[i] = presum[i];
	std::sort(tmp, tmp + n + 1);
	int n_ = std::unique(tmp, tmp + n + 1) - tmp - 1;
	for(int i = 0; i <= n; i++) pre[i] = std::lower_bound(tmp, tmp + n_ + 1, presum[i]) - tmp + 1;
	seg_tot = n_ + 1;
	// for(int i = 0; i <= n; i++) printf("%d ", pre[i]);
	// puts("");
}

struct SegmentTree {
	int t[N << 2];
	int initial() { return -INF; }
	int calc(int x, int y) { return std::max(x, y); }
	void build(int x = 1, int l = 1, int r = seg_tot) {
		int mid = (l + r) >> 1;
		t[x] = initial();
		if(l < r) build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int qind, int qv, int x = 1, int l = 1, int r = seg_tot) {
		if(l == r) { t[x] = calc(t[x], qv); return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = seg_tot) {
		if(ql > qr) return initial();
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1, ret = initial();
		if(ql <= mid) ret = calc(ret, query(ql, qr, x << 1, l, mid));
		if(qr > mid) ret = calc(ret, query(ql, qr, x << 1 | 1, mid + 1, r));
		return ret;
	}
} segp, segz;

int f[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) presum[i] = presum[i - 1] + a[i];
		discrete();
		segp.build(), segz.build();
		f[0] = 0;
		segp.modify(pre[0], 0), segz.modify(pre[0], 0);
		for(int i = 1; i <= n; i++) {
			f[i] = f[i - 1] - 1;
			f[i] = std::max(f[i], i + segp.query(1, pre[i] - 1));
			f[i] = std::max(f[i], segz.query(pre[i], pre[i]));
			segp.modify(pre[i], f[i] - i), segz.modify(pre[i], f[i]);
		}
		// for(int i = 1; i <= n; i++) printf("f[%d] = %d\n", i, f[i]);
		printf("%d\n", f[n]);
	}
	return 0;
}