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

const int N = 1e4 + 5;
const int M = 3e5 + 5;
const int B = 30;
const int INF = 0x3f3f3f3f;

int n, m;
struct Node { int x, y, yid; } a[N];
struct Query { int xl, xr, yl, yr, id; } q[M];

int tmp[N + 2 * M];
void discrete() {
	int c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i].y;
	for(int i = 1; i <= m; i++) tmp[++c] = q[i].yl, tmp[++c] = q[i].yr;
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i].yid = std::lower_bound(tmp + 1, tmp + c + 1, a[i].y) - tmp;
	for(int i = 1; i <= m; i++) q[i].yl = std::lower_bound(tmp + 1, tmp + c + 1, q[i].yl) - tmp;
	for(int i = 1; i <= m; i++) q[i].yr = std::lower_bound(tmp + 1, tmp + c + 1, q[i].yr) - tmp;
	for(int i = 1; i <= m; i++) {
		q[i].xl = std::lower_bound(a + 1, a + n + 1, q[i].xl, [&](const Node &x, const int &y) { return x.x < y; }) - a;
		q[i].xr = std::upper_bound(a + 1, a + n + 1, q[i].xr, [&](const int &x, const Node &y) { return x < y.x; }) - a - 1;
	}
}

struct SegNode {
	int retx, rety;
	int prex, prey;
	int sufx, sufy;
	SegNode() : retx(0), rety(1), prex(0), prey(0), sufx(0), sufy(0) {}
};
SegNode calc(SegNode x, SegNode y) {
	SegNode z;
	if(x.rety == 1 && x.retx == 0) z.retx = y.retx, z.rety = y.rety;
	else if(y.rety == 1 && y.retx == 0) z.retx = x.retx, z.rety = x.rety;
	else if((LL)x.rety * y.retx <= (LL)y.rety * x.retx) z.retx = x.retx, z.rety = x.rety;
	else z.retx = y.retx, z.rety = y.rety;
	if(x.sufx && y.prex && ((z.rety == 1 && z.retx == 0) || ((LL)(y.prey - x.sufy) * z.retx <= (LL)z.rety * std::abs(y.prex - x.sufx))))
		z.retx = std::abs(y.prex - x.sufx), z.rety = y.prey - x.sufy;
	z.prex = (x.prex ? x.prex : y.prex), z.prey = (x.prey ? x.prey : y.prey);
	z.sufx = (y.sufx ? y.sufx : x.sufx), z.sufy = (y.sufy ? y.sufy : x.sufy);
	return z;
}
struct SegmentTree {
	SegNode t[(N + 2 * M) << 2];
	int sz[(N + 2 * M) << 2], vx[(N + 2 * M) << 2], vy[(N + 2 * M) << 2];
	void insert(int qind, const std::pair<int, int> &p, int x = 1, int l = 1, int r = n + 2 * m) {
		if(l == r) {
			sz[x]++;
			vx[x] ^= p.first, vy[x] ^= p.second;
			if(sz[x] > 1) t[x].rety = 0, t[x].retx = 1, t[x].prex = t[x].sufx = t[x].prey = t[x].sufy = 0;
			else t[x].rety = 1, t[x].retx = 0, t[x].prex = t[x].sufx = vx[x], t[x].prey = t[x].sufy = vy[x];
			return;
		}
		int mid = (l + r) >> 1;
		if(qind <= mid) insert(qind, p, x << 1, l, mid);
		else insert(qind, p, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	void erase(int qind, const std::pair<int, int> &p, int x = 1, int l = 1, int r = n + 2 * m) {
		if(l == r) {
			sz[x]--;
			vx[x] ^= p.first, vy[x] ^= p.second;
			if(sz[x] > 1) t[x].rety = 0, t[x].retx = 1, t[x].prex = t[x].sufx = t[x].prey = t[x].sufy = 0;
			else t[x].rety = 1, t[x].retx = 0, t[x].prex = t[x].sufx = vx[x], t[x].prey = t[x].sufy = vy[x];
			return;
		}
		int mid = (l + r) >> 1;
		if(qind <= mid) erase(qind, p, x << 1, l, mid);
		else erase(qind, p, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	SegNode query(int ql, int qr, int x = 1, int l = 1, int r = n + 2 * m) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
	// int mx;
	// void build() {
	// 	for(mx = 1; mx <= n + 2 * m; mx <<= 1);
	// }
	// void insert(int x, std::pair<int, int> p) {
	// 	// printf("insert [%d] (%d,%d)\n", x, p.first, p.second);
	// 	x += mx, sz[x]++;
	// 	vx[x] ^= p.first, vy[x] ^= p.second;
	// 	if(sz[x] > 1) t[x].rety = 0, t[x].retx = 1, t[x].prex = t[x].sufx = t[x].prey = t[x].sufy = 0;
	// 	else t[x].rety = 1, t[x].retx = 0, t[x].prex = t[x].sufx = vx[x], t[x].prey = t[x].sufy = vy[x];
	// 	for(x >>= 1; x; x >>= 1) t[x] = calc(t[x << 1], t[x << 1 | 1]);
	// }
	// void erase(int x, std::pair<int, int> p) {
	// 	// printf("erase [%d] (%d,%d)\n", x, p.first, p.second);
	// 	x += mx, sz[x]--;
	// 	vx[x] ^= p.first, vy[x] ^= p.second;
	// 	if(sz[x] > 1) t[x].rety = 0, t[x].retx = 1, t[x].prex = t[x].sufx = t[x].prey = t[x].sufy = 0;
	// 	else t[x].rety = 1, t[x].retx = 0, t[x].prex = t[x].sufx = vx[x], t[x].prey = t[x].sufy = vy[x];
	// 	for(x >>= 1; x; x >>= 1) t[x] = calc(t[x << 1], t[x << 1 | 1]);
	// }
	// SegNode query(int l, int r) {
	// 	l += mx, r += mx;
	// 	SegNode retl, retr;
	// 	for(l--, r++; l ^ r ^ 1; l >>= 1, r >>= 1) {
	// 		if(~l & 1) retl = calc(retl, t[l ^ 1]);
	// 		if(r & 1) retr = calc(t[r ^ 1], retr);
	// 	}
	// 	return calc(retl, retr);
	// }
} seg;

int outx[M], outy[M];

void add(int i) {
	seg.insert(a[i].yid, {a[i].x, a[i].y});
}

void del(int i) {
	seg.erase(a[i].yid, {a[i].x, a[i].y});
}

int main() {
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; i++) read(a[i].x), read(a[i].y);
	std::sort(a + 1, a + n + 1, [&](const Node &x, const Node &y) { return x.x < y.x; });
	for(int i = 1; i <= m; i++) read(q[i].xl), read(q[i].xr), read(q[i].yl), read(q[i].yr), q[i].id = i;
	discrete();
	std::sort(q + 1, q + m + 1, [&](const Query &x, const Query &y) {
		return (x.xl / B) ^ (y.xl / B) ? x.xl < y.xl : ((x.xl / B & 1) ? x.xr < y.xr : x.xr > y.xr);
	});
	// seg.build();
	int l = 1, r = 0;
	for(int i = 1; i <= m; i++) {
		while(l > q[i].xl) add(--l);
		while(r < q[i].xr) add(++r);
		while(l < q[i].xl) del(l++);
		while(r > q[i].xr) del(r--);
		auto res = seg.query(q[i].yl, q[i].yr);
		int g = std::__gcd(res.retx, res.rety);
		outx[q[i].id] = res.retx / g, outy[q[i].id] = res.rety / g;
	}
	for(int i = 1; i <= m; i++) write(outy[i], ' '), write(outx[i], '\n');
	return 0;
} /*
10 10
19 36
8 38
15 47
6 35
15 7
19 1
9 41
9 33
11 35
18 5
7 7 13 49
13 13 1 42
12 20 11 49
9 20 1 41
1 19 5 39
5 20 3 42
13 20 6 44
17 20 1 48
8 16 2 42
13 20 6 49
*/