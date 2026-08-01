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

const int N = 1e6 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
LL E;
LL a[N], b[N];

LL pre[N];

LL tmp[N];
void discrete() {
	for(int i = 0; i <= n; i++) tmp[i] = pre[i];
	std::sort(tmp, tmp + n + 1);
	int c = std::unique(tmp, tmp + n + 1) - tmp - 1;
	for(int i = 0; i <= n; i++) pre[i] = std::lower_bound(tmp, tmp + c + 1, pre[i]) - tmp + 1;
}

struct BIT {
	LL t[N];
	void add(int x, LL v) { while(x <= n + 1) t[x] += v, x += x & -x; }
	LL query(int r) { LL ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
} bit;

struct SegmentTree {
	LL t[N << 2], lazy[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		t[x] = E, lazy[x] = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void setlazy(int x, LL v) { t[x] += v, lazy[x] += v; }
	void lazydown(int x) { setlazy(x << 1, lazy[x]), setlazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	void add(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		if(ql > qr) return;
		if(l == r) {
			if(t[x] >= 0) {
				t[x] += qv;
				if(t[x] < 0) bit.add(pre[l - 1], -1);
			} else t[x] += qv;
			if(t[x] < 0) t[x] = LLINF;
			return;
		}
		if(ql <= l && r <= qr && t[x] + qv >= 0) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
	}
} seg;

int main() {
#ifndef DEBUG
	freopen("top.in", "r", stdin);
	freopen("top.out", "w", stdout);
#endif
	read(n), read(E);
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 1; i <= n; i++) read(b[i]);
	for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] - a[i] + b[i];
	discrete();
	LL ans = 0;
	std::vector<std::pair<int, LL>> vct{{0, LLINF}};
	seg.build();
	for(int i = 1; i <= n; i++) {
		bit.add(pre[i - 1], 1);
		seg.add(1, i, std::min(-a[i] + b[i], 0LL));
		while(!vct.empty() && vct.back().second <= std::min(a[i], b[i])) {
			int p = vct.back().first; LL val = vct.back().second;
			vct.pop_back();
			seg.add(vct.back().first + 1, p, val - std::min(a[i], b[i]));
		}
		seg.add(i, i, -std::min(a[i], b[i]));
		vct.emplace_back(i, std::min(a[i], b[i]));
		ans += bit.query(pre[i]);
		// for(int j = 1; j <= i; j++) if(seg.t[j] >= 0 && pre[i] - pre[j - 1] >= 0) printf("[%d, %d]\n", j, i);
	}
	write(ans, '\n');
	return 0;
}