#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D, out[D], *O = out;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
	void wrtc(char c) { (O == out + D ? fwrite(O = out, 1, D, stdout) : 0), *O++ = c; }
	template<typename T> void write(T x, char ch = 0) {
		static char c[60]; int top = 0;
		if(x < 0) wrtc('-'), x = -x;
		do c[++top] = x % 10, x /= 10; while(x);
		while(top) wrtc(c[top--] + '0');
		if(ch) wrtc(ch);
	}
	void flush() { fwrite(out, 1, O - out, stdout); }
	struct Flusher { ~Flusher() { flush(); } } flusher;
}
using FIO::write;
using FIO::read;

typedef long long LL;

const int N = (1 << 18) + 5;

int n, Q;
int a[N];

struct SegmentTree {
	LL *t[20][N << 2];
	void build(int d = n, int x = 1, int l = 0, int r = (1 << n) - 1) {
		for(int i = 0; i <= n; i++) t[i][x] = new LL[1 << d];
		if(l == r) {
			for(int i = 0; i <= n; i++) t[i][x][0] = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(d - 1, x << 1, l, mid), build(d - 1, x << 1 | 1, mid + 1, r);
		for(int i = 0; i <= n; i++)
			for(int j = 0; j < (1 << d); j++) {
				int v = (j >> (d - 1) & 1), nj = (j & ((1 << (d - 1)) - 1));
				t[i][x][j] = (i >= v ? t[i - v][x << 1][nj] : 0) + (i >= !v ? t[i - !v][x << 1 | 1][nj] : 0);
			}
	}
	int ql, qr;
	LL query(int qx, int qd, int d = n, int x = 1, int l = 0, int r = (1 << n) - 1) {
		if(qd < 0) return 0;
		if(ql <= l && r <= qr) return t[qd][x][qx];
		int mid = (l + r) >> 1;
		int v = (qx >> (d - 1) & 1), nqx = (qx & ((1 << (d - 1)) - 1));
		if(qr <= mid) return query(nqx, qd - v, d - 1, x << 1, l, mid);
		else if(ql > mid) return query(nqx, qd - !v, d - 1, x << 1 | 1, mid + 1, r);
		else return query(nqx, qd - v, d - 1, x << 1, l, mid) + query(nqx, qd - !v, d - 1, x << 1 | 1, mid + 1, r);
	}
} seg;

int main() {
#ifndef DEBUG
	freopen("counting.in", "r", stdin);
	freopen("counting.out", "w", stdout);
#endif
	read(n), read(Q);
	for(int i = 0; i < (1 << n); i++) read(a[i]);
	seg.build();
	while(Q--) {
		int x, p, q;
		read(x), read(p), read(q);
		seg.ql = std::max(x - p, 0), seg.qr = std::min(x + p, (1 << n) - 1);
		write(seg.query(x, q), '\n');
	}
	return 0;
} /*
3 3
1 8 4 7 2 3 6 5
4 2 2
6 3 1
3 1 3
*/