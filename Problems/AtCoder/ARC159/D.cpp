#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
int l[N], r[N];

LL f[N];

struct SegNode { LL t; int ls, rs; };
struct SegmentTree {
	SegNode t[N * 20];
	int tot;
	SegmentTree() { tot = 1; t[0].t = t[1].t = -LLINF; }
	int nw() { tot++; t[tot] = {-LLINF, 0, 0}; return tot; }
	void modify(int qind, LL qv, int x = 1, int l = 0, int r = 1000000000) {
		// t[qind].t = std::max(t[qind].t, qv);
		if(l == r) { t[x].t = std::max(t[x].t, qv); return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) t[x].ls ? 0 : t[x].ls = nw(), modify(qind, qv, t[x].ls, l, mid);
		else t[x].rs ? 0 : t[x].rs = nw(), modify(qind, qv, t[x].rs, mid + 1, r);
		t[x].t = std::max(t[t[x].ls].t, t[t[x].rs].t);
	}
	LL query(int ql, int qr, int x = 1, int l = 0, int r = 1000000000) {
		// LL ret = -LLINF;
		// for(int i = ql; i <= qr; i++) ret = std::max(ret, t[i].t);
		// return ret;
		if(ql > qr) return -LLINF;
		if(!x) return -LLINF;
		if(ql <= l && r <= qr) return t[x].t;
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, t[x].ls, l, mid);
		else if(ql > mid) return query(ql, qr, t[x].rs, mid + 1, r);
		else return std::max(query(ql, qr, t[x].ls, l, mid), query(ql, qr, t[x].rs, mid + 1, r));
	}
} seg1, seg2;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &l[i], &r[i]);
	LL ans = 0;
	f[0] = 0;
	seg1.modify(0, 0), seg2.modify(0, 0);
	for(int i = 1; i <= n; i++) {
		f[i] = std::max(f[i], r[i] - l[i] + 1 + seg1.query(0, l[i] - 1));
		f[i] = std::max(f[i], r[i] + seg2.query(l[i], r[i]));
		seg1.modify(r[i], f[i]), seg2.modify(r[i], f[i] - r[i]);
		ans = std::max(ans, f[i]);
		// printf("f[%d] = %lld\n", i, f[i]);
	}
	printf("%lld\n", ans);
	return 0;
}