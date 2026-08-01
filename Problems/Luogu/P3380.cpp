#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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

const int N = 5e4 + 5;
const int NONE = 2147483647;
const int V = 1e8;

int n, Q;
int a[N];

int c[N * 200][2], sz[N * 200], v[N * 200], w[N * 200];
struct FHQ {
	int root;
	int nw(int val) { static int tot = 0; tot++, c[tot][0] = c[tot][1] = 0, sz[tot] = 1, v[tot] = val, w[tot] = (rand() << 15 | rand()); return tot; }
	void pushup(int x) { sz[x] = sz[c[x][0]] + sz[c[x][1]] + 1; }
	int merge(int x, int y) {
		if(!x || !y) return x ^ y;
		if(w[x] < w[y]) { c[x][1] = merge(c[x][1], y), pushup(x); return x; }
		else { c[y][0] = merge(x, c[y][0]), pushup(y); return y; }
	}
	void split(int rt, int val, int &x, int &y) {
		if(!rt) { x = y = 0; return; }
		if(v[rt] <= val) x = rt, split(c[x][1], val, c[x][1], y), pushup(x);
		else y = rt, split(c[y][0], val, x, c[y][0]), pushup(y);
	}
	void insert(int val) {
		int x, y;
		split(root, val - 1, x, y);
		root = merge(x, merge(nw(val), y));
	}
	void erase(int val) {
		int x, y, z;
		split(root, val - 1, x, y);
		split(y, val, y, z);
		if(y) y = merge(c[y][0], c[y][1]);
		root = merge(x, merge(y, z));
	}
	int between(int lv, int rv) {
		int x, y, z;
		split(root, lv - 1, x, y);
		split(y, rv, y, z);
		int ret = sz[y];
		root = merge(x, merge(y, z));
		return ret;
	}
};
struct SegNode { SegNode *ls, *rs; FHQ t; };
SegNode t[N * 200], *rt;
SegNode *nw() { static int tot = 0; tot++; return &t[tot]; }
struct SegmentTree {
	void insert(int qind, int qv, SegNode *x = rt, int l = 0, int r = V) {
		if(l == r) { x->t.insert(qind); return; }
		int mid = (l + r) >> 1;
		if(qv <= mid) x->ls ? 0 : x->ls = nw(), insert(qind, qv, x->ls, l, mid);
		else x->rs ? 0 : x->rs = nw(), insert(qind, qv, x->rs, mid + 1, r);
		x->t.insert(qind);
	}
	void erase(int qind, int qv, SegNode *x = rt, int l = 0, int r = V) {
		if(l == r) { x->t.erase(qind); return; }
		int mid = (l + r) >> 1;
		if(qv <= mid) erase(qind, qv, x->ls, l, mid);
		else erase(qind, qv, x->rs, mid + 1, r);
		x->t.erase(qind);
	}
	int rank(int ql, int qr, int qv, SegNode *x = rt, int l = 0, int r = V) {
		if(!x) return 0;
		if(l == r) return 0;
		int mid = (l + r) >> 1;
		if(qv <= mid) return rank(ql, qr, qv, x->ls, l, mid);
		else return rank(ql, qr, qv, x->rs, mid + 1, r) + (x->ls ? x->ls->t.between(ql, qr) : 0);
	}
	int at(int ql, int qr, int qk, SegNode *x = rt, int l = 0, int r = V) {
		if(l == r) return l;
		int mid = (l + r) >> 1, ret = (x->ls ? x->ls->t.between(ql, qr) : 0);
		if(ret < qk) return at(ql, qr, qk - ret, x->rs, mid + 1, r);
		else return at(ql, qr, qk, x->ls, l, mid);
	}
	int prev(int ql, int qr, int qv, SegNode *x = rt, int l = 0, int r = V) {
		if(!x) return -NONE;
		if(l == r) return l == qv || x->t.between(ql, qr) == 0 ? -NONE : l;
		int mid = (l + r) >> 1;
		if(qv <= mid) return prev(ql, qr, qv, x->ls, l, mid);
		else {
			int ret = prev(ql, qr, qv, x->rs, mid + 1, r);
			if(ret == -NONE) ret = prev(ql, qr, qv, x->ls, l, mid);
			return ret;
		}
	}
	int next(int ql, int qr, int qv, SegNode *x = rt, int l = 0, int r = V) {
		if(!x) return NONE;
		if(l == r) return l == qv || x->t.between(ql, qr) == 0 ? NONE : l;
		int mid = (l + r) >> 1;
		if(qv > mid) return next(ql, qr, qv, x->rs, mid + 1, r);
		else {
			int ret = next(ql, qr, qv, x->ls, l, mid);
			if(ret == NONE) ret = next(ql, qr, qv, x->rs, mid + 1, r);
			return ret;
		}
	}
} seg;

int main() {
	srand(time(0));
	read(n), read(Q);
	for(int i = 1; i <= n; i++) read(a[i]);
	rt = nw();
	for(int i = 1; i <= n; i++) seg.insert(i, a[i]);
	while(Q--) {
		int type, l, r, p, x, k;
		read(type);
		if(type == 1) read(l), read(r), read(x), write(seg.rank(l, r, x) + 1, '\n');
		else if(type == 2) read(l), read(r), read(k), write(seg.at(l, r, k), '\n');
		else if(type == 3) read(p), read(x), seg.erase(p, a[p]), a[p] = x, seg.insert(p, a[p]);
		else if(type == 4) read(l), read(r), read(x), write(seg.prev(l, r, x), '\n');
		else if(type == 5) read(l), read(r), read(x), write(seg.next(l, r, x), '\n');
		else return -1;
	}
	return 0;
} /*
9 6
4 2 2 1 9 4 0 1 1
2 1 4 3
3 4 10
2 1 4 3
1 2 5 9
4 3 9 5
5 2 8 5
*/