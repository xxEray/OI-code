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

int n, Q;
LL a[N][2];
LL base;

struct FHQ {
	int c[N][2], w[N], sz[N]; LL sum[N], v[N];
	int tot, rt;
	void init() { tot = 0; }
	int nw(LL val) { tot++, w[tot] = (rand() << 15 | rand()), v[tot] = val, sz[tot] = 1, sum[tot] = val; return tot; }
	void pushup(int x) { sz[x] = sz[c[x][0]] + sz[c[x][1]] + 1, sum[x] = sum[c[x][0]] + sum[c[x][1]] + v[x]; }
	void split(int root, LL val, int &x, int &y) {
		if(!root) x = y = 0;
		else if(v[root] <= val) x = root, split(c[root][1], val, c[x][1], y), pushup(x);
		else y = root, split(c[root][0], val, x, c[y][0]), pushup(y);
	}
	int merge(int x, int y) {
		if(!x || !y) return x ^ y;
		else if(w[x] > w[y]) { c[x][1] = merge(c[x][1], y), pushup(x); return x; }
		else { c[y][0] = merge(x, c[y][0]), pushup(y); return y; }
	}
	void insert(LL val) {
		int x, y;
		split(rt, val - 1, x, y);
		rt = merge(merge(x, nw(val)), y);
	}
	void remove(LL val) {
		int x, y, z;
		split(rt, val, x, z);
		split(x, val - 1, x, y);
		if(y) y = merge(c[y][0], c[y][1]);
		rt = merge(merge(x, y), z);
	}
	LL presum(LL val) {
		int x, y;
		split(rt, val, x, y);
		LL ret = (LL)val * sz[x] - sum[x];
		rt = merge(x, y);
		return ret;
	}
	LL sufsum(LL val) {
		int x, y;
		split(rt, val, x, y);
		LL ret = sum[y] - (LL)val * sz[y];
		rt = merge(x, y);
		return ret;
	}
} treapx, treapy;

int main() {
	read(n), read(Q), read(base);
	for(int i = 1; i <= n; i++) {
		LL x, y, x_, y_;
		read(x_), read(y_);
		x = x_ + y_, y = x_ - y_;
		a[i][0] = x, a[i][1] = y;
		treapx.insert(x), treapy.insert(y);
	}
	LL lastans = 0;
	while(Q--) {
		int t, p; LL a1, b1, a2, b2, x, y, x_, y_;
		read(t);
		if(t == 0) read(p);
		read(a1), read(b1), read(a2), read(b2);
		x_ = (a1 * lastans + b1) % base, y_ = (a2 * lastans + b2) % base;
		x = x_ + y_, y = x_ - y_;
		// printf("x_ = %lld, y_ = %lld\n", x_, y_);
		if(t == 0) treapx.remove(a[p][0]), treapy.remove(a[p][1]), a[p][0] = x, a[p][1] = y, treapx.insert(x), treapy.insert(y);
		else write((lastans = 2LL * (n - 1) + treapx.presum(x) + treapx.sufsum(x) + treapy.presum(y) + treapy.sufsum(y)), '\n');
		lastans %= base;
	}
	return 0;
}