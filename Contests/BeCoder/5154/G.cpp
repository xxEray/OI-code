#include <bits/stdc++.h>

#define msg(...) fprintf(stderr, __VA_ARGS__)

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

const int N = 5e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, Q;
struct Line {
	int k, b;
	LL at(int x) const { return k * x + b; }
} a[N];

int b[N];
struct Query { int t, l, r, x, id; } q[N];
LL out[N];

struct SegmentTree {
	std::vector<Line> t[N << 2];
	int mx;
	void build() {
		for(mx = 1; mx <= n; mx <<= 1);
	}
	void clear(int x) {
		for(x += mx; x; x >>= 1) t[x].clear();
	}
	void insert(int x, const Line &v) {
		for(x += mx; x; x >>= 1) {
			while(t[x].size() >= 2 && (LL)(t[x].back().b - v.b) * (t[x].back().k - t[x].end()[-2].k) <= (LL)(t[x].end()[-2].b - t[x].back().b) * (v.k - t[x].back().k)) {
				static int cnt = 0;
				cnt++;
				assert(cnt <= 3400000000);
				t[x].pop_back();
			}
			t[x].emplace_back(v);
		}
	}
	LL query(int l, int r, int qx) {
		l += mx, r += mx;
		LL ret = -LLINF;
		auto calc = [&](int x) {
			if(t[x].empty()) return;
			while(t[x].size() >= 2 && t[x].back().at(qx) <= t[x].end()[-2].at(qx)) t[x].pop_back();
			ret = std::max(ret, t[x].back().at(qx));
		};
		for(l--, r++; l ^ r ^ 1; l >>= 1, r >>= 1) {
			if(~l & 1) calc(l ^ 1);
			if(r & 1) calc(r ^ 1);
		}
		return ret;
	}
} seg;
std::vector<std::pair<int, Line>> vins[N << 2];
std::vector<std::array<int, 4>> vqry[N << 2];
int mx;
void build(int bd) {
	for(mx = 1; mx <= bd; mx <<= 1);
}
void insert(int l, int r, int qind, const Line &qv) {
	// printf("insert [%d..%d] [%d] %lldx%+lld\n", l, r, qind, qv.k, qv.b);
	l += mx, r += mx;
	for(l--, r++; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if(~l & 1) vins[l ^ 1].emplace_back(qind, qv); // , printf("    [%d] insert [%d] %lldx%+lld\n", l ^ 1, qind, qv.k, qv.b);
		if(r & 1) vins[r ^ 1].emplace_back(qind, qv); // , printf("    [%d] insert [%d] %lldx%+lld\n", r ^ 1, qind, qv.k, qv.b);
	}
}
void query(int x, int ql, int qr, int qx, int qid) {
	// printf("query [%d] [%d..%d] x=%lld\n", x, ql, qr, qx);
	for(x += mx; x; x >>= 1) vqry[x].push_back({ql, qr, qx, qid}); // , printf("    [%d] query [%d..%d] x=%lld\n", x, ql, qr, qx);
}
void solve_all() {
	msg("clock = %d\n", (int)clock());
	seg.build();
	for(int i = 1; i <= (mx << 1); i++) {
		for(auto [x, v] : vins[i]) seg.insert(x, v);
		for(auto [ql, qr, qx, qid] : vqry[i]) out[qid] = std::max(out[qid], seg.query(ql, qr, qx));
		for(auto [x, _] : vins[i]) seg.clear(x);
		// msg("i = %d\n", i);
	}
	msg("clock = %d\n", (int)clock());
}

struct NodeIIIL { int l, r, x; Line v; };
std::vector<NodeIIIL> vinsall;

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	read(n), read(Q);
	for(int i = 1; i <= n; i++) read(a[i].k), read(a[i].b), b[i] = 1;
	int cm = 1, cq = 0;
	for(int i = 1; i <= Q; i++) {
		int t;
		read(t);
		if(t == 1) {
			int k; Line v;
			read(k), read(v.k), read(v.b);
			vinsall.push_back({b[k], cm, k, a[k]});
			cm++, a[k] = v, b[k] = cm;
		} else {
			int x, l, r;
			read(x), read(l), read(r);
			cq++, q[cq].t = cm, q[cq].l = l, q[cq].r = r, q[cq].x = x, q[cq].id = cq;
		}
	}
	for(int i = 1; i <= n; i++) vinsall.push_back({b[i], cm, i, a[i]});
	std::sort(vinsall.begin(), vinsall.end(), [&](const NodeIIIL &x, const NodeIIIL &y) { return x.v.k < y.v.k; });
	build(cm);
	for(auto [l, r, x, v] : vinsall) insert(l, r, x, v);
	std::sort(q + 1, q + cq + 1, [&](const Query &x, const Query &y) { return x.x > y.x; });
	for(int i = 1; i <= cq; i++) query(q[i].t, q[i].l, q[i].r, q[i].x, q[i].id);
	solve_all();
	for(int i = 1; i <= cq; i++) write(out[i], '\n');
	return 0;
}