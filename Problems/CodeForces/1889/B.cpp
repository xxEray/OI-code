#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
LL c;
LL a[N], b[N];

LL tag;
struct SegmentTree {
	struct NodeValue { LL mx; int pos; };
	struct SegNode { NodeValue v; LL lazy, ext; } t[N << 2];
	void trim(int x, int l, int r) {
		while(t[x].v.pos < r && b[t[x].v.pos] + tag * t[x].v.pos < b[t[x].v.pos + 1] + tag * (t[x].v.pos + 1)) t[x].v.pos++;
		t[x].v.mx = b[t[x].v.pos] + tag * t[x].v.pos;
	}
	NodeValue calc(const NodeValue &x, const NodeValue &y) {
		NodeValue z;
		z.mx = std::max(x.mx, y.mx);
		if(z.mx == x.mx) z.pos = x.pos;
		else z.pos = y.pos;
		return z;
	}
	void build(int x = 1, int l = 1, int r = n) {
		t[x].lazy = 0;
		t[x].v = {-LLINF, r};
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int qind, LL qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x].v = {qv, l}, t[x].lazy = 0; return; }
		int mid = (l + r) >> 1;
		trim(x, l, r);
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x].v = calc(t[x << 1].v, t[x << 1 | 1].v);
		trim(x, l, r);
	}
	NodeValue query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return {t[x].v.mx + l * tag, t[x].v.pos};
		int mid = (l + r) >> 1;
		trim(x, l, r);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		tag = 0;
		scanf("%d%lld", &n, &c);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for(int i = 1; i <= n; i++) b[i] = -LLINF;
		seg.build();
		for(int i = n; i >= 1; i--) {
			if(i < n) tag += c;
			while(true) {
				if(i + 1 > n) break;
				auto [mx, pos] = seg.query(i + 1, n);
				// printf("query [%d, %d] = %lld,%d\n", i + 1, n, mx, pos);
				if(mx < -LLINF / 2 || mx < -a[i]) break;
				a[i] += a[pos], b[pos] = -LLINF, seg.modify(pos, -LLINF);
			}
			b[i] = a[i] - i * c * i - i * tag, seg.modify(i, a[i] - i * c * i - i * tag);
			// printf("%d: ", i); for(int j = i; j <= n; j++) printf("%lld ", seg.query(j, j).mx); puts("");
		}
		seg.modify(1, -LLINF);
		puts(seg.query(1, n).mx < -LLINF / 2 ? "Yes" : "No");
	}
	return 0;
}