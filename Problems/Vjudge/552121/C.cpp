#include <cstdio>
#include <algorithm>

const int N = 2.01e5 + 5;

int n, m, Q;
int a[N];

struct SegmentTree {
	int t[N << 2], lazy[N << 2];
	void build(int x = 1, int l = 0, int r = n + 100) {
		t[x] = lazy[x] = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void set_lazy(int x, int len, int v) { t[x] += v * len, lazy[x] += v; }
	void lazy_down(int x, int l, int r) {
		int mid = (l + r) >> 1;
		set_lazy(x << 1, mid - l + 1, lazy[x]);
		set_lazy(x << 1 | 1, r - mid, lazy[x]);
		lazy[x] = 0;
	}
	int query(int qind, int x = 1, int l = 0, int r = n + 100) {
		if(l == r) return t[x];
		int mid = (l + r) >> 1;
		lazy_down(x, l, r);
		if(qind <= mid) return query(qind, x << 1, l, mid);
		else return query(qind, x << 1 | 1, mid + 1, r);
	}
	int rfind(int ql, int qv, int x = 1, int l = 0, int r = n + 100) {
		if(l == r) return t[x] == qv ? l + 1 : l;
		int mid = (l + r) >> 1;
		lazy_down(x, l, r);
		if(ql > mid) return rfind(ql, qv, x << 1 | 1, mid + 1, r);
		if(ql < l) {
			if(t[x << 1] == (mid - l + 1) * qv) return rfind(ql, qv, x << 1 | 1, mid + 1, r);
			else return rfind(ql, qv, x << 1, l, mid);
		}
		int ret = rfind(ql, qv, x << 1, l, mid);
		if(ret <= mid) return ret;
		if(t[x << 1 | 1] == (r - mid) * qv) return r + 1;
		else return rfind(ql, qv, x << 1 | 1, mid + 1, r);
	}
	int rmost(int x = 1, int l = 0, int r = n + 100) {
		if(l == r) return l;
		int mid = (l + r) >> 1;
		lazy_down(x, l, r);
		if(t[x << 1 | 1]) return rmost(x << 1 | 1, mid + 1, r);
		else return rmost(x << 1, l, mid);
	}
	void add(int ql, int qr, int qv, int x = 1, int l = 0, int r = n + 100) {
		if(ql > qr) return;
		if(ql <= l && r <= qr) { set_lazy(x, r - l + 1, qv); return; }
		int mid = (l + r) >> 1;
		lazy_down(x, l, r);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] + t[x << 1 | 1];
	}
} seg;

void add(int x) {
	int j = seg.rfind(x, m - 1);
	// printf("add %d (rfind=%d)\n", x, j);
	// for(int i = 0; i <= 8; i++) printf("%d ", seg.query(i));
	// puts("");
	seg.add(j, j, 1), seg.add(x, j - 1, -(m - 1));
	// for(int i = 0; i <= 8; i++) printf("%d ", seg.query(i));
	// puts("");
}

void sub(int x) {
	int j = seg.rfind(x, 0);
	// printf("sub %d (rfind=%d)\n", x, j);
	// for(int i = 0; i <= 8; i++) printf("%d ", seg.query(i));
	// puts("");
	seg.add(j, j, -1), seg.add(x, j - 1, m - 1);
	// for(int i = 0; i <= 8; i++) printf("%d ", seg.query(i));
	// puts("");
}

int answer() {
	int j = seg.rmost();
	if(seg.rfind(0, 0) == j) return j;
	else return j + 1;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &Q);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), add(a[i]);
		while(Q--) {
			int k, x;
			scanf("%d%d", &k, &x);
			sub(a[k]), add(x);
			a[k] = x;
			printf("%d ", answer());
		}
		puts("");
		seg.build();
	}
	return 0;
} /*
1
4 2 1
1 3 4 4
3 3
4 3
4 4
3 4
2 4
1 2
2 2
3 2
4 2
4 3
4 4
3 3
4 3
4 4
3 4
2 3
3 3
4 3
4 4
3 4
2 4
1 3
2 3
3 3
4 3
4 4
3 4
2 4
1 4
*/