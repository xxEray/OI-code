#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

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
const int M = 1e6 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
struct Node { int x, y; LL f; int lis; } a[N];

struct BIT {
	int t[M];
	void modify(int x, int v) { while(x <= m) t[x] = std::max(t[x], v), x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret = std::max(ret, t[r]), r -= r & -r; return ret; }
} bit;

// struct SegData { int x, y; LL f; };
// struct SegQuery { int x, y; int id; };
struct SegmentTree {
	std::vector<int> t[N << 2];
	std::vector<int> q[N << 2];
	int ls[N << 2], rs[N << 2];
	int cnt, tot;
	inline void build() { cnt = 0, tot = 1; build(1); }
	void build(int x) {
		t[x].clear(), q[x].clear();
		if(ls[x]) build(ls[x]);
		if(rs[x]) build(rs[x]);
		ls[x] = rs[x] = 0;
	}
	inline void addv(int qv) { return addv(++cnt, qv, 1, 1, n); }
	void addv(const int &qind, const int &qv, int x, int l, int r) {
		t[x].push_back(qv);
		if(l == r) return;
		int mid = (l + r) >> 1;
		if(qind <= mid) ls[x] ? 0 : ls[x] = ++tot, addv(qind, qv, ls[x], l, mid);
		else rs[x] ? 0 : rs[x] = ++tot, addv(qind, qv, rs[x], mid + 1, r);
	}
	inline void addq(int qv) { return addq(qv, 1); }
	void addq(const int &qv, int x) {
		if(t[x].empty()) return;
		if(a[t[x].front()].x > a[qv].x || a[t[x].back()].y > a[qv].y) return;
		if(a[t[x].back()].x < a[qv].x && a[t[x].front()].y < a[qv].y) { q[x].push_back(qv); return; }
		if(ls[x]) addq(qv, ls[x]);
		if(rs[x]) addq(qv, rs[x]);
	}
	inline LL calc(const int &i, const int &j) { return a[i].f + (LL)(a[j].x - a[i].x) * (a[j].y - a[i].y); };
	void cdq(const int &x, int lt, int rt, int lq, int rq) {
		if(lt > rt || lq > rq) return;
		int midq = (lq + rq) >> 1;
		LL ret = LLINF; int ind = 0;
		for(int i = lt; i <= rt; i++) if(calc(t[x][i], q[x][midq]) < ret) ret = calc(t[x][i], q[x][midq]), ind = i;
		a[q[x][midq]].f = std::min(a[q[x][midq]].f, ret);
		cdq(x, ind, rt, lq, midq - 1), cdq(x, lt, ind, midq + 1, rq);
	}
	inline void answer() { answer(1); }
	void answer(int x) {
		cdq(x, 0, (int)t[x].size() - 1, 0, (int)q[x].size() - 1);
		if(ls[x]) answer(ls[x]);
		if(rs[x]) answer(rs[x]);
	}
} seg;

int main() {
	freopen("mowing.in", "r", stdin);
	freopen("mowing.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; i++) read(a[i].x), read(a[i].y), a[i].f = LLINF;
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.x < y.x; });
	for(int i = 1; i <= n; i++) a[i].lis = bit.query(a[i].y) + 1, bit.modify(a[i].y, a[i].lis);
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.lis == y.lis ? x.x < y.x : x.lis < y.lis; });
	// for(int i = 1; i <= n; i++) printf("(%lld, %lld), lis=%d\n", a[i].x, a[i].y, a[i].lis);
	for(int j = 0, i = 1; i <= n; ) {
		seg.build();
		while(j < n && a[j + 1].lis == a[j].lis) seg.addv(j), j++;
		seg.addv(j), j++;
		while(i < n && a[i + 1].lis == a[i].lis) seg.addq(i), i++;
		seg.addq(i), i++;
		seg.answer();
	}
	// for(int i = 1; i <= n; i++) printf("(%lld, %lld), lis=%d, f=%lld\n", a[i].x, a[i].y, a[i].lis, a[i].f);
	LL ans = LLINF;
	for(int i = 1; i <= n; i++) if(a[i].lis == a[n].lis) ans = std::min(ans, a[i].f + (LL)(m - a[i].x) * (m - a[i].y));
	write(ans, '\n');
	return 0;
}