#include <cstdio>

const int N = 3e5 + 5;

int n, m;

namespace SegTree {
	int t[N << 2];
	void set_xor(int qind, int qxor, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] ^= qxor; return; }
		int mid = l + ((r - l) >> 1);
		if(qind <= mid) set_xor(qind, qxor, x << 1, l, mid);
		else set_xor(qind, qxor, x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] ^ t[x << 1 | 1];
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return t[x];
		int mid = l + ((r - l) >> 1);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return query(ql, qr, x << 1, l, mid) ^ query(ql, qr, x << 1 | 1, mid + 1, r);
	}
}

int main() {
	std::scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		int x;
		std::scanf("%d", &x);
		SegTree::set_xor(i, x);
	}
	for(int i = 1; i <= m; i++) {
		int t, x, y;
		std::scanf("%d%d%d", &t, &x, &y);
		if(t == 1) SegTree::set_xor(x, y);
		else std::printf("%d\n", SegTree::query(x, y));
	}
	return 0;
}