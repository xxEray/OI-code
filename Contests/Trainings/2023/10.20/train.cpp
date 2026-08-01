#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D, out[D], *O = out;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc();
		while(c < '0' || c > '9') c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
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

namespace Maker{
	unsigned int x0, seed;
	void init() { read(x0), read(seed); }
	inline unsigned int getnum() {
		x0 = (x0 << 3) ^ x0;
		x0 = ((x0 >> 5) + seed) ^ x0;
		return x0;
	}
}

const int B = 14;
const int MAXB = (1 << (32 - B)) + 5;
const int N = 1e5 + 5;
const int MAXQ = 2e7 + 5;

int n, m, typ;
unsigned ia[N], a[N];

int fa[N], sz[N], rmost[N];
void init() { for(int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1, rmost[i] = i - 1; }
int find(int x) {
	int t, y = x;
	while(fa[y] != y) y = fa[y];
	while(fa[x] != x) t = fa[x], fa[x] = y, x = t;
	return y;
}
void merge(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) return;
	if(sz[x] > sz[y]) std::swap(x, y);
	fa[x] = y, sz[y] += sz[x], rmost[y] = std::max(rmost[x], rmost[y]);
}

int cnt[MAXB];
struct Node { int l, r; unsigned v; } b[MAXQ], q[MAXQ];

int main(){
#ifndef DEBUG
	freopen("train.in", "r", stdin);
	freopen("train.out", "w", stdout);
#endif
//	printf("%.3f\n", (sizeof(ql) * 5) / 1024. / 1024);
	read(n), read(m), read(typ);
	init();
	for(int i = 1; i <= n; i++) read(ia[i]);
	// fprintf(stderr, "clock = %d\n", (int)clock());
	Maker::init();
	for(int i = 1; i <= m; ++i){
		int l = Maker::getnum() % n + 1, r = Maker::getnum() % n + 1;
		unsigned v = Maker::getnum();
		if(l > r) std::swap(l, r);
		if(typ == 1) l = 1;
		b[i] = {l, r, v}, cnt[v >> B]++;
		// printf("%d %d %u\n", l, r, v);
	}
	for(int i = 1; i <= (1 << (32 - B)); i++) cnt[i] += cnt[i - 1];
	for(int i = 1; i <= m; i++) q[cnt[b[i].v >> B]--] = b[i];
	Node tmp;
	for(int i = 0; i <= (1 << (32 - B)); i++)
		for(int j = cnt[i] + 1; j <= cnt[i + 1]; j++) {
			int k = j;
			tmp = q[k];
			while(k > cnt[i] + 1 && q[k].v < q[k - 1].v)
				q[k] = q[k - 1], k--;
			q[k] = tmp;
		}
	// fprintf(stderr, "clock = %d\n", (int)clock());
	// for(int i = 1; i <= m; i++) printf("%d %d %u\n", ql[i], qr[i], qv[i]);
	for(int o = m; o >= 1; o--) {
		const auto &[l, r, v] = q[o];
		if(find(1) == find(n)) break;
		for(int i = rmost[find(l)] + 1; i <= r;) {
			if(!a[i]) a[i] = v, rmost[i] = i, merge(i, l), i++;
			else merge(i, l), i = rmost[find(i)] + 1;
		}
		if(a[l - 1]) merge(l - 1, l);
		if(a[r + 1]) merge(l, r + 1);
	}
	// fprintf(stderr, "clock = %d\n", (int)clock());
	for(int i = 1; i <= n; i++) write(std::max(ia[i], a[i]), ' ');
	return 0;
} /*
5 4 0
1 2 3 4 5
233 666
*/