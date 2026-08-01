#include <bits/stdc++.h>

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N], b[N], ia[N];

struct SegmentTree {
	int t[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		t[x] = -INF;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int qind, int qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = std::max(t[x], qv); return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql > qr) return -INF;
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::max(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg1, seg2;

int tmp[N];
void discrete() {
	int c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i];
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) ia[i] = std::lower_bound(tmp + 1, tmp + c + 1, a[i]) - tmp;
}

int mx[N];

int main() {
#ifndef DEBUG
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
	seg1.build(), seg2.build();
	discrete();
	for(int i = 1; i <= n; i++) mx[ia[i]] = std::max(mx[ia[i]], b[i]);
	for(int i = 1; i <= n; i++) seg1.modify(ia[i], a[i] + b[i]), seg2.modify(ia[i], b[i] - a[i]);
	int ans = 0;
	for(int i = 1; i <= n; i++)
		if(seg1.query(1, ia[i] - 1) < a[i] + b[i] && seg2.query(ia[i] + 1, n) < b[i] - a[i] && b[i] == mx[ia[i]])
			mx[ia[i]] = -INF, ans++;
	printf("%d\n", ans);
	return 0;
} /*
4
4 2
2 3
3 4
6 5
*/