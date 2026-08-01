#pragma GCC optimize("Ofast")

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

const int N = 1e5 + 5;
const int B = 1400;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, Q;
int a[N];
int pre[N];

struct Line {
	int k, b;
	Line() {}
	Line(int k_, int b_) : k(k_), b(b_) {}
	inline LL at(int x) { return b == INT_MIN ? LLINF : (LL)k * x + b; }
};
struct LiChaoTree {
	Line t[N << 2];
	void build(int x = 1, int l = 0, int r = n - 1) {
		t[x].k = 0, t[x].b = INT_MIN;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void insert(Line qv, int x = 1, int l = 0, int r = n - 1) {
		if(l == r) {
			if(t[x].at(l) > qv.at(l)) t[x] = qv;
			return;
		}
		int mid = (l + r) >> 1;
		if(qv.at(mid) < t[x].at(mid)) std::swap(qv, t[x]);
		if(qv.at(l) < t[x].at(l)) insert(qv, x << 1, l, mid);
		if(qv.at(r) < t[x].at(r)) insert(qv, x << 1 | 1, mid + 1, r);
	}
	LL query(int qx, int x = 1, int l = 0, int r = n - 1) {
		// assert(0 <= qx && qx <= n - 1);
		if(l == r) return t[x].at(qx);
		int mid = (l + r) >> 1;
		if(qx <= mid) return std::min(t[x].at(qx), query(qx, x << 1, l, mid));
		else return std::min(t[x].at(qx), query(qx, x << 1 | 1, mid + 1, r));
	}
} seg[N / B + 5];

Line b[N];

int main() {
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	// printf("%.3f\n", sizeof(seg) / 1024. / 1024);
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]), pre[i] = pre[i - 1] + a[i], b[i] = Line(-a[i], a[i] * i - pre[i]);
	// for(int i = 1; i <= n; i++) printf("%d: %dk%+d\n", i, b[i].k, b[i].b);
	for(int i = 1; i <= (n - 1) / B + 1; i++) seg[i].build();
	for(int i = 1; i <= n; i++) seg[(i - 1) / B + 1].insert(b[i]);
	read(Q);
	while(Q--) {
		int x, y, l, r;
		read(x), read(y);
		// assert(1 <= x && x <= y && y <= n);
		// assert(0 <= y - x && y - x <= n - 1);
		l = y - x + 1, r = y;
		LL ans = LLINF;
		if((l - 1) / B + 1 == (r - 1) / B + 1) {
			for(int i = l; i <= r; i++) ans = std::min(ans, b[i].at(y - x) + pre[y]);
		} else {
			for(int i = l; i <= ((l - 1) / B + 1) * B; i++) ans = std::min(ans, b[i].at(y - x) + pre[y]);
			for(int i = (r - 1) / B * B + 1; i <= r; i++) ans = std::min(ans, b[i].at(y - x) + pre[y]);
			for(int i = (l - 1) / B + 2; i <= (r - 1) / B; i++) /* assert(i <= N / B),  */ans = std::min(ans, seg[i].query(y - x) + pre[y]);
		}
		write(ans, '\n');
	}
	return 0;
}