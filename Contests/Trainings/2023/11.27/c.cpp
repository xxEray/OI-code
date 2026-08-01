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

const int N = 2e5 + 5;
const LL BIG = 1e12;

int n, m;
struct Node { int v, l, r; } a[N];
struct Query { int l, r, id; } q[N];
LL out[N];

struct SegmentTree {
	LL mx[N << 2], hmx[N << 2], lazy[N << 2], hlazy[N << 2];
	void setlazy(int x, LL v, LL vmax) { hmx[x] = std::max(hmx[x], mx[x] + vmax), mx[x] += v, hlazy[x] = std::max(hlazy[x], lazy[x] + vmax), lazy[x] += v; }
	void lazydown(int x) {
		setlazy(x << 1, lazy[x], hlazy[x]), setlazy(x << 1 | 1, lazy[x], hlazy[x]);
		lazy[x] = hlazy[x] = 0;
	}
	void build(int x = 1, int l = 1, int r = n) {
		mx[x] = -2 * BIG, hmx[x] = -2 * BIG, lazy[x] = 0, hlazy[x] = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int qind, LL qv, int x = 1, int l = 1, int r = n) {
		// if(x == 1) printf("modify [%d] %lld\n", qind, qv);
		if(l == r) { mx[x] = qv, hmx[x] = std::max(hmx[x], qv), lazy[x] = hlazy[x] = 0; return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		mx[x] = std::max(mx[x << 1], mx[x << 1 | 1]);
		hmx[x] = std::max(hmx[x], mx[x]);
	}
	void add(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		// if(x == 1) printf("add [%d, %d] %lld\n", ql, qr, qv);
		if(ql <= l && r <= qr) { setlazy(x, qv, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		mx[x] = std::max(mx[x << 1], mx[x << 1 | 1]);
		hmx[x] = std::max(hmx[x], mx[x]);
	}
	LL query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		// if(x == 1) printf("query [%d, %d]\n", ql, qr);
		if(ql <= l && r <= qr) return hmx[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::max(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg1, seg2;

std::vector<int> op1[N], op2[N];

int main() {
#ifndef DEBUG
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i <= n; i++) read(a[i].v), read(a[i].l), read(a[i].r);
	read(m);
	for(int i = 1; i <= m; i++) read(q[i].l), read(q[i].r), q[i].id = i;
	std::sort(q + 1, q + m + 1, [&](Query x, Query y) { return x.r < y.r; });
	for(int i = 1; i <= n; i++) {
		if(i + a[i].l <= n) op1[i + a[i].l].emplace_back(i);
		if(i + a[i].r + 1 <= n) op2[i + a[i].r + 1].emplace_back(i);
	}
	seg1.build(), seg2.build();
	for(int i = 1, j = 1; i <= n; i++) {
		for(int k : op1[i]) seg1.modify(k, -a[k].v - BIG), seg2.modify(k, a[k].v - BIG);
		for(int k : op2[i]) seg1.modify(k, -BIG * 2), seg2.modify(k, -BIG * 2);
		int l = std::max(i - a[i].r, 1), r = i - a[i].l;
		if(l <= r) {
			seg1.add(l, r, BIG + a[i].v), seg2.add(l, r, BIG - a[i].v);
			seg1.add(l, r, -(BIG + a[i].v)), seg2.add(l, r, -(BIG - a[i].v));
		}
		for(; j <= m && q[j].r == i; j++) out[q[j].id] = std::max(seg1.query(q[j].l, q[j].r), seg2.query(q[j].l, q[j].r));
	}
	for(int i = 1; i <= m; i++) write(out[i] < 0 ? -1LL : out[i], '\n');
	return 0;
}