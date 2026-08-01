#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 100 + 5;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
int a[N], b[N];

struct SegmentTree {
	int t[N << 2], lazy[N << 2];
	void setlazy(int x, int v, int len) { if(v != -1) t[x] = v * len, lazy[x] = v; }
	void lazydown(int x, int l, int r, int mid) { setlazy(x << 1, lazy[x], mid - l + 1), setlazy(x << 1 | 1, lazy[x], r - mid); lazy[x] = -1; }
	void modify(int qind, int qv, int x = 1, int l = 1, int r = 100000) {
		if(l == r) { lazy[x] = -1, t[x] = qv; return; }
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] + t[x << 1 | 1];
	}
	void set(int ql, int qr, int qv, int x = 1, int l = 1, int r = 100000) {
		if(ql <= l && r <= qr) { setlazy(x, qv, r - l + 1); return; }
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(ql <= mid) set(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) set(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] + t[x << 1 | 1];
	}
	int query(int qind, int x = 1, int l = 1, int r = 100000) {
		if(l == r) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(qind <= mid) return query(qind, x << 1, l, mid);
		else return query(qind, x << 1 | 1, mid + 1, r);
	}
	int next0(int qind, int x = 1, int l = 1, int r = 100000) {
		if(l == r) return t[x] == 0 ? l : INF;
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(qind > mid) return next0(qind, x << 1 | 1, mid + 1, r);
		else {
			int ret = INF;
			if(t[x << 1] < mid - l + 1) ret = std::min(ret, next0(qind, x << 1, l, mid));
			if(ret != INF) return ret;
			if(t[x << 1 | 1] < r - mid) ret = std::min(ret, next0(qind, x << 1 | 1, mid + 1, r));
			return ret;
		}
	}
	int next1(int qind, int x = 1, int l = 1, int r = 100000) {
		if(l == r) return t[x] == 1 ? l : INF;
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(qind > mid) return next1(qind, x << 1 | 1, mid + 1, r);
		else {
			int ret = INF;
			if(t[x << 1]) ret = std::min(ret, next1(qind, x << 1, l, mid));
			if(ret != INF) return ret;
			if(t[x << 1 | 1]) ret = std::min(ret, next1(qind, x << 1 | 1, mid + 1, r));
			return ret;
		}
	}
} seg;

char tmp[N];
void read(int *arr, int &cn) {
	memset(seg.t, 0, sizeof(seg.t)), memset(seg.lazy, -1, sizeof(seg.lazy));
	scanf("%s", tmp + 1);
	int len = strlen(tmp + 1), st = 100000;
	seg.modify(st, 1);
	for(int i = 1; i <= len; i++)
		if(tmp[i] == '1') st--, seg.modify(st, 0);
		else if(tmp[i] == '2') st--, seg.modify(st, 1);
		else if(tmp[i] == 'U') st++;
		else if(tmp[i] == 'L') {
			int j = seg.next1(st);
			assert(j != INF);
			seg.modify(j, 0);
			if(st <= j - 1) seg.set(st, j - 1, 1);
		} else if(tmp[i] == 'R') {
			int j = seg.next0(st);
			assert(j != INF);
			seg.modify(j, 1);
			if(st <= j - 1) seg.set(st, j - 1, 0);
		}
	for(int i = st; i <= 100000; i++) arr[++cn] = seg.query(i);
//	printf("read: "); for(int i = 1; i <= cn; i++) printf("%d", arr[i]);
//	puts("");
}

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	read(a, n), read(b, m);
	if(n > m) {
		for(int i = 1; i <= n; i++) std::swap(a[i], b[i]);
		std::swap(n, m);
	}
	LL base = m - n;
	for(int i = 1, j = m - n + 1; i <= n; i++, j++) b[i] = b[j];
	for(int i = n + 1; i <= m; i++) b[i] = 0;
	m = n;
	printf("a: "); for(int i = 1; i <= n; i++) printf("%d", a[i]); puts("");
	printf("b: "); for(int i = 1; i <= n; i++) printf("%d", b[i]); puts("");
	LL ans = 2 * n, ret = 0;
	for(int i = n; i >= 1; i--) {
		ret = ret * 2 + (a[i] - b[i]);
		if(ret < -(1 << 28) || ret > (1 << 28)) break;
		ans = std::min(ans, std::abs(ret) + 2 * (i - 1));
	}
	printf("%lld\n", ans + base);
	return 0;
} /*
221LU
12L2
*/
