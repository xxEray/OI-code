#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 5e5 + 5;

int n, K;
int a[N];

struct SegmentTree {
	int sum[N << 2], mn[N << 2];
	void modify(int qind, int qv, int x = 1, int l = 1, int r = 100000) {
		if(l == r) { mn[x] = sum[x] = qv; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		sum[x] = sum[x << 1] + sum[x << 1 | 1];
		mn[x] = std::min(mn[x << 1], mn[x << 1 | 1]);
	}
	int get(int qind, int x = 1, int l = 1, int r = 100000) {
		if(l == r) return sum[x];
		int mid = (l + r) >> 1;
		if(qind <= mid) return get(qind, x << 1, l, mid);
		else return get(qind, x << 1 | 1, mid + 1, r);
	}
	int getmin(int ql, int qr, int x = 1, int l = 1, int r = 100000) {
		ql = std::max(ql, 1), qr = std::min(qr, 100000);
		if(ql > qr) return 500001;
		if(ql <= l && r <= qr) return mn[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return getmin(ql, qr, x << 1, l, mid);
		else if(ql > mid) return getmin(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::min(getmin(ql, qr, x << 1, l, mid), getmin(ql, qr, x << 1 | 1, mid + 1, r));
	}
	int getsum(int ql, int qr, int x = 1, int l = 1, int r = 100000) {
		ql = std::max(ql, 1), qr = std::min(qr, 100000);
		if(ql > qr) return 0;
		if(ql <= l && r <= qr) return sum[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return getsum(ql, qr, x << 1, l, mid);
		else if(ql > mid) return getsum(ql, qr, x << 1 | 1, mid + 1, r);
		else return getsum(ql, qr, x << 1, l, mid) + getsum(ql, qr, x << 1 | 1, mid + 1, r);
	}
} segsum, segmin;

int f[N][2];

int main() {
	for(int i = 1; i <= 100000; i++) segmin.modify(i, 500001);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= n; i++) f[i][0] = f[i][1] = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		LL ans = 0;
		for(int i = n; i >= 1; i--) {
			ans += segsum.get(a[i]);
			int nxt0 = segmin.getmin(a[i] - K, a[i] - 1), nxt1 = segmin.getmin(a[i] + 1, a[i] + K);
			f[i][0] = f[nxt0][0] + (nxt0 == 500001 ? segsum.getsum(a[i] - K, a[i] - 1) : segsum.getsum(a[nxt0], a[i] - 1));
			f[i][1] = f[nxt1][1] + (nxt1 == 500001 ? segsum.getsum(a[i] + 1, a[i] + K) : segsum.getsum(a[i] + 1, a[nxt1]));
			segmin.modify(a[i], i);
			segsum.modify(a[i], segsum.get(a[i]) + 1);
			ans += f[i][0] + f[i][1];
			// printf("%d: %d, %d\n", i, f[i][0], f[i][1]);
		}
		printf("%lld\n", ans + n);
		for(int i = 1; i <= n; i++) segmin.modify(a[i], 500001), segsum.modify(a[i], 0);
	}
	return 0;
} /*
4
3 0
1 1 1
4 2
4 8 6 8
6 4
7 2 5 8 3 8
20 23
110 57 98 14 20 1 60 82 108 37 82 73 8 46 38 35 106 115 58 112
*/