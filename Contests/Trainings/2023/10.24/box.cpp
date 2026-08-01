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
		static char c[130]; int top = 0;
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

typedef __int128_t LL;

const int N = 2e5 + 5;

int n, Q;
struct Node { int a, w; } a[N];

struct BIT {
	LL t[N];
	void add(int x, LL v) { while(x <= n) t[x] += v, x += x & -x; }
	LL query(int r) { LL ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	LL query(int l, int r) { return l > r ? 0 : query(r) - query(l - 1); }
	void set(int x, LL v) { add(x, v - query(x, x)); }
} bit;

struct SegmentTree {
	int t[N << 2], lazy[N << 2];
	void setlazy(int x, int v) { if(v) t[x] = lazy[x] = v; }
	void lazydown(int x) { setlazy(x << 1, lazy[x]), setlazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	void modify(int ql, int qr, int qv, int x = 1, int l = 0, int r = n + 1) {
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
	}
	int query(int qind, int x = 1, int l = 0, int r = n + 1) {
		if(l == r) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qind <= mid) return query(qind, x << 1, l, mid);
		else return query(qind, x << 1 | 1, mid + 1, r);
	}
} seg;

void update(int i) {
	if(i < 1 || i > n) return;
	LL ret = 0;
	if(seg.query(i - 1) != seg.query(i)) ret += (LL)a[i].w * a[i].a;
	else ret += (LL)std::max(a[i].a - a[i - 1].a, 0) * a[i].w;
	if(seg.query(i + 1) != seg.query(i)) ret += (LL)a[i].w * a[i].a;
	else ret += (LL)std::max(a[i].a - a[i + 1].a, 0) * a[i].w;
	bit.set(i, ret);
}

std::set<std::pair<int, int>> st;

int main() {
#ifndef DEBUG
	freopen("box.in", "r", stdin);
	freopen("box.out", "w", stdout);
#endif
	read(n), read(Q);
	for(int i = 1; i <= n; i++) { int c; read(a[i].a), read(c), read(a[i].w); seg.modify(i, i, c); }
	for(int i = 1; i <= n; ) {
		int j = i;
		while(j < n && seg.query(j + 1) == seg.query(j)) j++;
		st.insert({i, j});
		i = j + 1;
	}
	for(int i = 1; i <= n; i++) update(i);
	while(Q--) {
		int t;
		read(t);
		if(t == 1) {
			int i;
			read(i), read(a[i].a), read(a[i].w);
			update(i - 1), update(i), update(i + 1);
		} else if(t == 2) {
			int l, r, c;
			read(l), read(r), read(c);
			seg.modify(l, r, c);
			while(true) {
				auto it = st.lower_bound({l, 0});
				if(it != st.end() && it->second <= r) update(it->first), update(it->second), st.erase(it);
				else break;
			}
			{
				auto it = st.lower_bound({l, 0});
				if(it != st.begin()) {
					it--;
					if(it->second >= r) {
						int ll = it->first, rr = it->second;
						st.erase(it);
						if(ll <= l - 1) st.insert({ll, l - 1});
						if(r + 1 <= rr) st.insert({r + 1, rr});
					} else if(it->second >= l) {
						update(it->second);
						int ll = it->first;
						st.erase(it);
						if(ll <= l - 1) st.insert({ll, l - 1});
					}
				}
			}
			{
				auto it = st.lower_bound({l, 0});
				if(it != st.end() && it->first <= r) {
					update(it->first);
					int rr = it->second;
					st.erase(it);
					if(r + 1 <= rr) st.insert({r + 1, rr});
				}
			}
			update(l - 1), update(l), update(r), update(r + 1);
			st.insert({l, r});
			// printf("st: "); for(const auto &[x, y] : st) printf("[%d, %d] ", x, y); puts("");
		} else {
			int l, r;
			read(l), read(r);
			LL ret = bit.query(l, r);
			write(ret + (seg.query(l - 1) == seg.query(l)) * (LL)std::min(a[l - 1].a, a[l].a) * a[l].w + (seg.query(r + 1) == seg.query(r)) * (LL)std::min(a[r + 1].a, a[r].a) * a[r].w, '\n');
		}
	}
	return 0;
} /*
5 20
2 3 3
2 5 5
2 5 5
3 3 5
2 3 1
2 3 4 5
2 3 3 4
2 1 1 2
2 2 5 1
2 2 4 3
2 2 4 4
3 4 5
2 4 5 3
2 1 2 2
2 3 4 5
2 2 5 5
2 1 5 2
2 2 2 5
2 2 3 3
2 1 5 2
2 2 5 5
3 4 5
2 2 2 5
2 1 2 1
2 2 5 2

*/