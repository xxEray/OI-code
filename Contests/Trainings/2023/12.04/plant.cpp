#include <bits/stdc++.h>

#ifndef DEBUG
	#define assert(...) ((void)0)
#endif

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

const int N = 5e4 + 5;
const int MAXK = 20 + 3;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const int INF = 0x3f3f3f3f;

int K, n, Q;
LL A, B, C;
int a[MAXK][N];
struct Query { int l, r, id; } q[N], q2[N];

LL out[N];

LL F(LL x) { return x ? (A ^ (B * x + C)) : 0; }

struct SegmentTree {
	LL mn[N << 2], sc[N << 2], cnt[N << 2], sum[N << 2], hsum[N << 2], tag1[N << 2], tag2[N << 2], tag3[N << 2];
	void pushtag1(int x, LL v) {
		mn[x] += v, tag1[x] += v;
	}
	void pushtag2(int x, LL v) {
		hsum[x] += F(mn[x]) * cnt[x] * v + sum[x] * v;
		tag2[x] += v, tag3[x] += (F(mn[x]) - F(mn[x] - tag1[x])) * v;
	}
	void pushtag3(int x, LL v) {
		hsum[x] += v * cnt[x];
		tag3[x] += v;
	}
	void pushdown(int x) {
		pushtag2(x << 1, tag2[x]), pushtag2(x << 1 | 1, tag2[x]), tag2[x] = 0;
		if(mn[x << 1] <= mn[x << 1 | 1]) pushtag3(x << 1, tag3[x]);
		if(mn[x << 1 | 1] <= mn[x << 1]) pushtag3(x << 1 | 1, tag3[x]);
		tag3[x] = 0;
		if(mn[x << 1] <= mn[x << 1 | 1]) pushtag1(x << 1, tag1[x]);
		if(mn[x << 1 | 1] <= mn[x << 1]) pushtag1(x << 1 | 1, tag1[x]);
		tag1[x] = 0;
	}
	void pushup(int x) {
		mn[x] = std::min(mn[x << 1], mn[x << 1 | 1]);
		cnt[x] = (mn[x] == mn[x << 1]) * cnt[x << 1] + (mn[x] == mn[x << 1 | 1]) * cnt[x << 1 | 1];
		sc[x] = std::min(mn[x] == mn[x << 1] ? sc[x << 1] : mn[x << 1], mn[x] == mn[x << 1 | 1] ? sc[x << 1 | 1] : mn[x << 1 | 1]);
		sum[x] = sum[x << 1] + sum[x << 1 | 1] + (mn[x << 1] >= sc[x]) * F(mn[x << 1]) * cnt[x << 1] + (mn[x << 1 | 1] >= sc[x]) * F(mn[x << 1 | 1]) * cnt[x << 1 | 1];
		hsum[x] = hsum[x << 1] + hsum[x << 1 | 1];
	}
	void build(int x = 1, int l = 1, int r = n) {
		mn[x] = 0, cnt[x] = r - l + 1, sc[x] = LLINF, sum[x] = 0, hsum[x] = 0, tag1[x] = tag2[x] = tag3[x] = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void copy(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { pushtag2(x, 1); return; }
		int mid = (l + r) >> 1;
		pushdown(x);
		if(ql <= mid) copy(ql, qr, x << 1, l, mid);
		if(qr > mid) copy(ql, qr, x << 1 | 1, mid + 1, r);
		pushup(x);
	}
	void modify(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		assert(1 <= ql && ql <= qr && qr <= n);
		if(mn[x] >= qv) return;
		if(ql <= l && r <= qr && sc[x] > qv) { pushtag1(x, qv - mn[x]); return; }
		int mid = (l + r) >> 1;
		pushdown(x);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		pushup(x);
	}
	LL query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		assert(1 <= ql && ql <= qr && qr <= n);
		if(ql <= l && r <= qr) return hsum[x];
		int mid = (l + r) >> 1;
		pushdown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return query(ql, qr, x << 1, l, mid) + query(ql, qr, x << 1 | 1, mid + 1, r);
	}
} seg;

struct SparseTable {
	int go[17][N];
	void init(int *arr) {
		// for(int j = 0; j < 17; j++) for(int i = 0; i <= n; i++) go[j][i] = INF;
		for(int i = 1; i <= n; i++) go[0][i] = arr[i];
		for(int j = 1; j < 17; j++)
			for(int i = n; i - (1 << j) + 1 >= 1; i--)
				go[j][i] = std::min(go[j - 1][i], go[j - 1][i - (1 << (j - 1))]);
	}
	int get(int r) {
		int v = go[0][r];
		for(int j = 16; j >= 0; j--) if(go[j][r] >= v) r -= (1 << j);
		return r + 1;
	}
} ST[MAXK];

int main() {
#ifndef DEBUG
	freopen("plant.in", "r", stdin);
	freopen("plant.out", "w", stdout);
#endif
	// printf("%.3f\n", sizeof(ST) / 1024. / 1024);
	read(K), read(n), read(Q);
	for(int j = 1; j <= K; j++) for(int i = 1; i <= n; i++) read(a[j][i]);
	read(A), read(B), read(C);
	for(int i = 1; i <= Q; i++) read(q[i].l), read(q[i].r), q[i].id = i, q2[i] = q[i];
	std::sort(q + 1, q + Q + 1, [&](const Query &x, const Query &y) { return x.r > y.r; });
	std::sort(q2 + 1, q2 + Q + 1, [&](const Query &x, const Query &y) { return x.l > y.l; });
	for(int j = 1; j <= K; j++) ST[j].init(a[j]);
	seg.build();
	for(int i = n, iq = 1, jq = 1; i >= 1; i--) {
		// printf("i = %d:\n", i);
		while(iq <= Q && q[iq].r == i) out[q[iq].id] -= seg.query(q[iq].l, i), iq++;
		for(int j = 1; j <= K; j++) {
			int p = i;
			while(p >= 1 && a[j][p] > a[j][i + 1]) {
				int t = ST[j].get(p);
				// printf("  %d: [%d, %d] max= %d\n", j, t, p, a[j][p]);
				seg.modify(t, p, a[j][p]);
				p = t - 1;
			}
		}
		seg.copy(1, i);
		while(jq <= Q && q2[jq].l == i) out[q2[jq].id] += seg.query(i, q2[jq].r), jq++;
	}
	for(int i = 1; i <= Q; i++) write(out[i], '\n');
	return 0;
} /*
3 4 10
5 8 3 6
7 2 4 1
9 5 2 7
3 2 1
1 1
1 2
1 3
1 4
2 2
2 3
2 4
3 3
3 4
4 4
*/