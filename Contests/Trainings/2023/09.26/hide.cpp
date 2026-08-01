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
using FIO::wrtc;
using FIO::read;

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m, Q;

struct SegmentTree {
	int mn[N << 2], lazy[N << 2];
	void setlazy(int x, int v) { if(v > mn[x]) mn[x] = lazy[x] = v; }
	void lazydown(int x) { setlazy(x << 1, lazy[x]), setlazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	void modify_max(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		// printf("modify_max %d %d %d %d %d %d\n", ql, qr, qv, x, l, r);
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) modify_max(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify_max(ql, qr, qv, x << 1 | 1, mid + 1, r);
		mn[x] = std::min(mn[x << 1], mn[x << 1 | 1]);
	}
	int query_min(int ql, int qr, int x = 1, int l = 1, int r = n) {
		// printf("query_min %d %d %d %d %d\n", ql, qr, x, l, r);
		if(ql <= l && r <= qr) return mn[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query_min(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query_min(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::min(query_min(ql, qr, x << 1, l, mid), query_min(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

std::vector<int> vct[N];

struct Query { int l, r, id; } q[N];
int out[N];

int main() {
#ifndef DEBUG
	freopen("hide.in", "r", stdin);
	freopen("hide.out", "w", stdout);
#endif
	read(n), read(m), read(Q);
	for(int i = 1; i <= m; i++) {
		int l, r;
		read(l), read(r);
		vct[r].push_back(l);
	}
	for(int i = 1; i <= Q; i++) read(q[i].l), read(q[i].r), q[i].id = i;
	std::sort(q + 1, q + Q + 1, [&](Query x, Query y) { return x.r < y.r; });
	for(int i = 1, p = 1; i <= n; i++) {
		for(int j : vct[i]) seg.modify_max(j, i, j);
		while(p <= Q && q[p].r == i) out[q[p].id] = (seg.query_min(q[p].l, i) >= q[p].l), p++;
	}
	for(int i = 1; i <= Q; i++) puts(out[i] ? "YES" : "NO");
	return 0;
}