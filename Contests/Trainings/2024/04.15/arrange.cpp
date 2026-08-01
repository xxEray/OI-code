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
using FIO::rdc;
using FIO::wrtc;
using FIO::write;
using FIO::read;

typedef long long LL;

const int N = 1e6 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
int p[N], q[N], ip[2 * N], iq[2 * N];
LL a[N], b[N];

struct Node { int l, r, type; LL val; };

struct SegmentTree {
    LL t[N << 2];
	int m;
    void build() {
		for(m = 1; m <= n; m <<= 1);
		for(int i = 0; i <= (m << 1); i++) t[i] = -LLINF;
    }
    void modify(int x, LL v) {
		t[m + x] = std::max(t[m + x], v);
		for(int i = (m + x) >> 1; i; i >>= 1) t[x] = std::max(t[x << 1], t[x << 1 | 1]);
    }
    LL query(int l, int r) {
		l--, r++, l += m, r += m;
		LL ret = -LLINF;
		for(; l ^ r ^ 1; l >>= 1, r >>= 1) {
			if(~l & 1) ret = std::max(ret, t[l ^ 1]);
			if(r & 1) ret = std::max(ret, t[r ^ 1]);
		}
		return ret;
    }
} seg[2][2];

bool tin[N];
int prv[N], nxt[N];

int main() {
#ifndef DEBUG
	freopen("arrange.in", "r", stdin);
	freopen("arrange.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) read(p[i]), ip[p[i]] = i;
	for(int i = 1; i <= n; i++) read(a[i]), a[i] += a[i - 1];
	for(int i = 1; i <= n; i++) read(q[i]), iq[q[i]] = i;
	for(int i = 1; i <= n; i++) read(b[i]), b[i] += b[i - 1];
	LL ans = std::max(a[n], b[n]);
	auto solve = [&]() {
		int mid = 0;
		for(int i = 1; i <= n; i++) if(a[i - 1] <= a[n] / 2 && a[n] - a[i] <= a[n] / 2) mid = i;
		// printf("mid = %d\n", mid);
		assert(mid);
		std::set<int> st;
		std::vector<Node> vct;
		for(int i = mid; i >= 1; i--) {
			if(i < mid && iq[p[i]]) {
				auto it = st.lower_bound(iq[p[i]]);
				vct.push_back({it == st.begin() ? 1 : *std::prev(it), it == st.end() ? n : *it, 0, a[i]});
			}
			if(iq[p[i]]) st.emplace(iq[p[i]]);
		}
		st.clear();
		for(int i = mid; i <= n; i++) {
			if(i > mid && iq[p[i]]) {
				auto it = st.lower_bound(iq[p[i]]);
				vct.push_back({it == st.begin() ? 1 : *std::prev(it), it == st.end() ? n : *it, 1, a[i - 1]});
			}
			if(iq[p[i]]) st.emplace(iq[p[i]]);
		}
		std::sort(vct.begin(), vct.end(), [&](Node x, Node y) { return x.l < y.l; });
		seg[0][0].build(), seg[0][1].build(), seg[1][0].build(), seg[1][1].build();
		for(auto nd : vct)
			if(nd.type == 0) {
				ans = std::max(ans, seg[1][0].query(nd.r + 1, n) - nd.val + b[nd.r - 1] - b[nd.l]);
				ans = std::max(ans, seg[1][1].query(1, nd.r) - nd.val - b[nd.l]);
				seg[0][0].modify(nd.r, -nd.val);
				seg[0][1].modify(nd.r, -nd.val + b[nd.r - 1]);
			} else {
				ans = std::max(ans, seg[0][0].query(nd.r + 1, n) + nd.val + b[nd.r - 1] - b[nd.l]);
				ans = std::max(ans, seg[0][1].query(1, nd.r) + nd.val - b[nd.l]);
				seg[1][0].modify(nd.r, nd.val);
				seg[1][1].modify(nd.r, nd.val + b[nd.r - 1]);
			}
	};
	solve();
	for(int i = 1; i <= n; i++) std::swap(p[i], q[i]), std::swap(a[i], b[i]);
	for(int i = 1; i <= 2 * n; i++) std::swap(ip[i], iq[i]);
	solve();
	auto solve2 = [&]() {
		for(int i = 0; i <= n + 1; i++) prv[i] = 0, nxt[i] = n + 1, tin[i] = false;
		for(int i = 1; i <= n; i++) if(iq[p[i]]) tin[iq[p[i]]] = true;
		for(int i = 1, j = 0; i <= n + 1; i++) if(tin[i] || i == n + 1) nxt[j] = i, prv[i] = j, j = i;
		LL mx = 0;
		for(int i = 0; i != n + 1; i = nxt[i]) mx = std::max(mx, b[nxt[i] - 1] - b[i]);
		ans = std::max(ans, a[n] + mx);
		for(int i = n; i >= 1; i--) {
			if(!iq[p[i]]) continue;
			int it = iq[p[i]];
			mx = std::max(mx, b[nxt[it] - 1] - b[prv[it]]);
			ans = std::max(ans, a[i - 1] + mx);
			nxt[prv[it]] = nxt[it], prv[nxt[it]] = prv[it];
		}
		for(int i = 0; i <= n + 1; i++) prv[i] = 0, nxt[i] = n + 1, tin[i] = false;
		for(int i = 1; i <= n; i++) if(iq[p[i]]) tin[iq[p[i]]] = true;
		for(int i = 1, j = 0; i <= n + 1; i++) if(tin[i] || i == n + 1) nxt[j] = i, prv[i] = j, j = i;
		mx = 0;
		for(int i = 0; i != n + 1; i = nxt[i]) mx = std::max(mx, b[nxt[i] - 1] - b[i]);
		ans = std::max(ans, a[n] + mx);
		for(int i = 1; i <= n; i++) {
			if(!iq[p[i]]) continue;
			int it = iq[p[i]];
			mx = std::max(mx, b[nxt[it] - 1] - b[prv[it]]);
			ans = std::max(ans, a[n] - a[i] + mx);
			nxt[prv[it]] = nxt[it], prv[nxt[it]] = prv[it];
		}
	};
	solve2();
	for(int i = 1; i <= n; i++) std::swap(p[i], q[i]), std::swap(a[i], b[i]);
	for(int i = 1; i <= 2 * n; i++) std::swap(ip[i], iq[i]);
	solve2();
	printf("%lld\n", ans);
	return 0;
} /*
10
1 13 7 12 16 14 2 4 18 9
863188151 578895948 745326321 879803922 33340187 773018775 1611961 328481539 836778643 42132740
15 12 9 10 13 6 7 16 5 14
490111184 44160605 178712634 153844762 469335595 59339337 678804831 156639755 813410172 285569928
*/