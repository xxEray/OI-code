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
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const LL NONE = -LLINF - 3;

int n, m, Q;

struct Query { LL v; int id; } q[N];
LL out[N];

std::vector<std::pair<LL, LL>> seq;

struct SegmentTree {
	LL t[N << 2], lazy[N << 2];
	void setlazy(int x, LL v) { t[x] = lazy[x] = v; }
	void lazydown(int x) { if(lazy[x] != NONE) setlazy(x << 1, lazy[x]), setlazy(x << 1 | 1, lazy[x]), lazy[x] = NONE; }
	void build(int x = 1, int l = 1, int r = n) {
		t[x] = -LLINF, lazy[x] = NONE;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int ql, int qr, LL qt, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr && t[x] != NONE) {
			// printf("[%d, %d] %lld\n", l, r, qt - t[x] - 1);
			if(t[x] > -LLINF) seq.push_back({qt - t[x] - 1, r - l + 1});
			setlazy(x, qt);
			return;
		}
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) modify(ql, qr, qt, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qt, x << 1 | 1, mid + 1, r);
		if(t[x << 1] == NONE || t[x << 1 | 1] == NONE || t[x << 1] != t[x << 1 | 1]) t[x] = NONE;
		else t[x] = t[x << 1];
	}
} seg;

int main() {
#ifndef DEBUG
	freopen("make.in", "r", stdin);
	freopen("make.out", "w", stdout);
#endif
	read(n), read(m), read(Q);
	seg.build();
	LL sum = 1;
	for(int i = 1; i <= m; i++) {
		int l, r;
		read(l), read(r);
		seg.modify(l, r, sum - l);
		sum += r - l + 1;
	}
	std::sort(seq.begin(), seq.end(), std::greater<std::pair<LL, LL>>());
	for(int i = 1; i <= Q; i++) read(q[i].v), q[i].id = i;
	std::sort(q + 1, q + Q + 1, [&](Query x, Query y) { return x.v > y.v; });
	sum = 0; int p = 0;
	for(int i = 1; i <= Q; i++) {
		while(p < (int)seq.size() && seq[p].first >= q[i].v) sum += seq[p].second, p++;
		out[q[i].id] = sum;
	}
	for(int i = 1; i <= Q; i++) write(out[i], ' ');
	FIO::wrtc('\n');
	return 0;
}