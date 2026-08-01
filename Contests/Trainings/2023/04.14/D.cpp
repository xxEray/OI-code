#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long long LL;

const int N = 1e5 + 5;
const int M = 5e5 + 5;

int n, m;
int a[N];

struct SegmentTree {
	LL t[N << 2], lazy[N << 2];
	void setlazy(int x, int len, LL v) { t[x] += len * v, lazy[x] += v; }
	void lazy_down(int x, int l, int r) {
		int mid = (l + r) >> 1;
		setlazy(x << 1, mid - l + 1, lazy[x]), setlazy(x << 1 |  1, r - mid, lazy[x]);
		lazy[x] = 0;
	}
	void build(int x = 1, int l = 1, int r = n) {
		t[x] = lazy[x] = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void add(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { setlazy(x, r - l + 1, qv); return; }
		int mid = (l + r) >> 1;
		lazy_down(x, l, r);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] + t[x << 1 | 1];
	}
	LL query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazy_down(x, l, r);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return query(ql, qr, x << 1, l, mid) + query(ql, qr, x << 1 | 1, mid + 1, r);
	}
} seg;

struct Query { int l, r, id; } q[M];
bool operator<(Query x, Query y) { return x.r < y.r; }
LL out[M];

int go[20][N], lg[N];
void preprocess() {
	lg[0] = -1;
	for(int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1, go[0][i] = a[i];
	for(int j = 1; j < 20; j++)
		for(int i = 1; i + (1 << j) - 1 <= n; i++)
			go[j][i] = (go[j - 1][i] & go[j - 1][i + (1 << (j - 1))]);
}
int getand(int l, int r) {
	int k = lg[r - l + 1];
	return go[k][l] & go[k][r - (1 << k) + 1];
}

bool is_square(int x) { int y = round(sqrt(x)); return y * y == x; }

int main() {
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
		seg.build();
		preprocess();
		std::sort(q + 1, q + m + 1);
		for(int i = 1, k = 1; i <= n; i++) {
			int j = i;
			while(true) {
				int v = getand(j, i);
				// printf("[%d, %d] -> %d\n", j, i, v);
				int l = 1, r = j;
				while(l < r) {
					int mid = (l + r) >> 1;
					if(getand(mid, i) == getand(j, i)) r = mid;
					else l = mid + 1;
				}
				l--;
				int nj = l;
				if(is_square(v)) seg.add(nj + 1, j, 1); // , printf("[%d, %d] += %d\n", nj + 1, j, 1);
				if(nj == 0) break;
				j = nj;
			}
			while(k <= m && q[k].r == i)
				out[q[k].id] = seg.query(q[k].l, q[k].r), k++;
				// printf("ans[%d] = query(%d, %d)\n", q[k].id, q[k].l, q[k].r);
		}
		for(int i = 1; i <= m; i++) printf("%lld\n", out[i]);
	}
	return 0;
} /*
1
3 2
1 2 3
2 2
1 3
*/