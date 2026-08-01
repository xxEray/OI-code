#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;
const int N_LOG_N = 5e6 + 5;

int a[N], posb[N];
int n;

int c[N_LOG_N];
int cnt;
int tmp[N], cc;

struct SegmentTree {
	int t[N << 2];
	void set_max(int qind, int qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = std::max(t[x], qv); return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) set_max(qind, qv, x << 1, l, mid);
		else set_max(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql > qr) return 0;
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::max(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); posb[x] = i; }
	for(int i = 1; i <= n; i++) {
		cc = 0;
		for(int j = a[i]; j <= n; j += a[i]) tmp[++cc] = posb[j];
		std::sort(tmp + 1, tmp + cc + 1);
		for(int j = cc; j >= 1; j--) c[++cnt] = tmp[j];
	}
	// for(int i = 1; i <= cnt; i++) printf("%d ", c[i]);
	// puts("");
	int ans = 0;
	for(int i = 1; i <= cnt; i++) {
		int ret = seg.query(1, c[i] - 1) + 1;
		ans = std::max(ans, ret);
		seg.set_max(c[i], ret);
	}
	printf("%d\n", ans);
	return 0;
}