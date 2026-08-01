#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

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
const int D = 1500;
const int INF = 0x3f3f3f3f;

int n, Q;
int a[N];
struct Query { int l, r, k, id; } q[N];

std::vector<int> vct[N];

int block(int x) { return (x - 1) / D + 1; }

struct Barrett {
	__int128_t m; LL p;
	void init(LL p_) { p = p_; m = ((__int128_t)1 << 64) / p; }
} mod[N];
int operator/(LL x, Barrett y) {
	LL w = (__int128_t)x * y.m >> 64;
	if(x - w * y.p >= y.p) w++;
	// assert(w == x / y.p);
	return w;
}
int operator%(LL x, Barrett y) {
	LL w = x - ((__int128_t)x * y.m >> 64) * y.p;
	if(w >= y.p) w -= y.p;
	// assert(w == x % y.p);
	return w;
}

struct Line {
	int k, b;
	Line() : k(0), b(-INF) {}
	Line(int k_, int b_) : k(k_), b(b_) {}
	int at(int x) const { return k * x + b; }
};
struct LiChao {
	Line t[N << 2];
	void insert(Line qv) {
		int x = 1, l = 1, r = 100000;
		while(true) {
			if(l == r) {
				if(qv.at(l) > t[x].at(l)) t[x] = qv;
				break;
			}
			int mid = (l + r) >> 1;
			if(qv.at(mid) > t[x].at(mid)) std::swap(qv, t[x]);
			if(qv.at(l) > t[x].at(l)) x <<= 1, r = mid;
			else if(qv.at(r) > t[x].at(r)) x = x << 1 | 1, l = mid + 1;
			else break;
		}
	}
	int query(int qx) {
		int x = 1, l = 1, r = 100000;
		int ret = 0;
		while(true) {
			if(l == r) {
				ret = std::max(ret, t[x].at(qx));
				break;
			}
			int mid = (l + r) >> 1;
			ret = std::max(ret, t[x].at(qx));
			if(qx <= mid) x <<= 1, r = mid;
			else x = x << 1 | 1, l = mid + 1;
		}
		return ret;
	}
} seg[N / D + 15];

int out[N];

int main() {
// #ifndef DEBUG
	freopen("mod.in", "r", stdin);
	freopen("mod.out", "w", stdout);
// #endif
	for(int i = 1; i <= 100000; i++) mod[i].init(i);
	read(n), read(Q);
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 1; i <= Q; i++) read(q[i].l), read(q[i].r), read(q[i].k), q[i].id = i;
	for(int i = 1; i <= n; i++) vct[1].emplace_back(i);
	std::sort(q + 1, q + Q + 1, [&](const Query &x, const Query &y) { return x.k < y.k; });
	for(int i = 1, j = 1; i <= 100000; i++) {
		auto &modi = mod[i];
		for(int x : vct[i]) {
			seg[block(x)].insert(Line(-(a[x] / modi), a[x]));
			if(a[x] / modi) vct[a[x] / (a[x] / modi) + 1].emplace_back(x);
		}
		std::vector<int>().swap(vct[i]);
		while(j <= Q && q[j].k == i) {
			int l = q[j].l, r = q[j].r;
			int ans = 0;
			if(block(l) == block(r)) {
				for(int k = l; k <= r; k++) ans = std::max(ans, a[k] % modi);
			} else {
				for(int k = l; k <= block(l) * D; k++) ans = std::max(ans, a[k] % modi);
				for(int k = block(l) + 1; k <= block(r) - 1; k++) ans = std::max(ans, seg[k].query(i));
				for(int k = (block(r) - 1) * D + 1; k <= r; k++) ans = std::max(ans, a[k] % modi);
			}
			// printf("query [%d, %d] k=%d: %d\n", l, r, q[j].k, ans);
			out[q[j].id] = ans;
			j++;
		}
	}
	for(int i = 1; i <= Q; i++) write(out[i], '\n');
	return 0;
} /*
10 10
4 9 1 2 6 9 8 10 9 3
8 10 8
3 4 9
6 9 1
5 7 1
8 8 10
1 4 4
5 7 6
2 8 5
5 8 9
6 9 10
*/