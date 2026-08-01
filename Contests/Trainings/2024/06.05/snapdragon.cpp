#include <bits/stdc++.h>

namespace FIO {
	const int D = (1 << 23) + 1;
	char in[D], *I = in, *Iend = in, out[D], *O = out;
	char rdc() { return (I == Iend ? Iend = in + fread(I = in, 1, D, stdin) : 0), (I == Iend ? EOF : *I++); }
	template<typename T> void read(T &x) {
		char ch = rdc();
		while(ch < '0' || ch > '9') ch = rdc();
		for(x = 0; '0' <= ch && ch <= '9'; ch = rdc()) x = x * 10 + ch - '0';
	}
	void wrtc(char c) { (O == out + D ? fwrite(O = out, 1, D, stdout) : 0), *O++ = c; }
	void flush() { fwrite(out, 1, O - out, stdout); }
	struct Flusher { ~Flusher() { flush(); } } flusher;
}
using FIO::read;
using FIO::wrtc;

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m, Q;
std::vector<int> a[N];

struct Query { int l, r, id; } q[N];
bool out[N];

struct BIT {
private:
	int t[N];
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
public:
	void add(int l, int r, int v) { add(l, v), add(r + 1, -v); }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
} bit;

struct SegNode { int mn, sc, cnt; };
SegNode calc(const SegNode &x, const SegNode &y) {
	SegNode z;
	z.mn = std::min(x.mn, y.mn);
	z.sc = std::min(x.mn == z.mn ? x.sc : x.mn, y.mn == z.mn ? y.sc : y.mn);
	z.cnt = (x.mn == z.mn) * x.cnt + (y.mn == z.mn) * y.cnt;
	return z;
}
struct SegmentTree {
	SegNode t[N << 2];
	int lz[N << 2];
	void setlazy(int x, int v) { t[x].mn = std::max(t[x].mn, v), lz[x] = std::max(lz[x], v); }
	void lazydown(int x) { setlazy(x << 1, lz[x]), setlazy(x << 1 | 1, lz[x]), lz[x] = 0; }
	void build(int x = 1, int l = 1, int r = n) {
		t[x].sc = INF, t[x].cnt = r - l + 1;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		if(t[x].mn >= qv) return;
		if(ql <= l && r <= qr && t[x].sc > qv) {
			if(t[x].mn < qv) bit.add(t[x].mn + 1, qv, t[x].cnt);
			setlazy(x, qv);
			return;
		}
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
} seg;

int main() {
#ifndef DEBUG
	freopen("snapdragon.in", "r", stdin);
	freopen("snapdragon.out", "w", stdout);
#endif
	read(n), read(m), read(Q);
	for(int i = 1; i <= m; i++) { int l, r; read(l), read(r); a[r].emplace_back(l); }
	for(int i = 1; i <= Q; i++) read(q[i].l), read(q[i].r), q[i].id = i;
	std::sort(q + 1, q + Q + 1, [&](const Query &x, const Query &y) { return x.r < y.r; });
	seg.build();
	for(int i = 1, j = 1; i <= n; i++) {
		for(int k : a[i]) seg.modify(k, i, k);
		for(; j <= Q && q[j].r == i; j++) if(bit.query(q[j].l) == i - q[j].l + 1) out[q[j].id] = true;
	}
	for(int i = 1; i <= Q; i++)
		if(out[i]) wrtc('Y'), wrtc('E'), wrtc('S'), wrtc('\n');
		else wrtc('N'), wrtc('O'), wrtc('\n');
	return 0;
} /*
5 2 1
1 1
3 3
1 3
*/