#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D, *Iend = in + D, out[D], *O = out;
	char rdc() { return (I == in + D ? Iend = in + fread(I = in, 1, D, stdin) : 0), (I == Iend ? EOF : *I++); }
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

const int N = 1e6 + 5;
const LL MOD = 998244353;

int n;
int p[N];
std::vector<int> vct[N];
LL X;
LL a[N], b[N], c[N];
LL r[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

int main() {
#ifndef DEBUG
	freopen("determinant.in", "r", stdin);
	freopen("determinant.out", "w", stdout);
#endif
	int T; read(T);
	while(T--) {
		read(n), read(X);
		for(int i = 1; i <= n; i++) read(c[i]), (c[i] += MOD - X) %= MOD;
		for(int i = 1; i <= n; i++) vct[i].clear();
		for(int i = 2; i <= n; i++) {
			read(p[i]), read(a[i]), read(b[i]);
			(a[i] += MOD - X) %= MOD, (b[i] += MOD - X) %= MOD;
			vct[p[i]].emplace_back(i);
		}
		for(int i = 1; i <= n; i++) r[i] = MOD - X;
		for(int i = n; i > 1; i--) {
			LL v = b[i] * inv(c[i]) % MOD;
			(c[p[i]] += MOD - a[i] * v % MOD) %= MOD;
			(r[p[i]] += MOD - r[i] * v % MOD) %= MOD;
		}
		// for(int i = 1; i <= n; i++) printf("%d: c=%lld, r=%lld\n", i, c[i], r[i]);
		LL ex = X;
		for(int i = 1; i <= n; i++) {
			LL v = r[i] * inv(c[i]) % MOD;
			(ex += MOD - X * v % MOD) %= MOD;
			for(int j : vct[i]) (r[j] += MOD - a[j] * v % MOD) %= MOD;
		}
		LL prod = (X ? ex : 1LL);
		for(int i = 1; i <= n; i++) (prod *= c[i]) %= MOD;
		if(X) (prod *= inv(X)) %= MOD;
		write(prod, '\n');
	}
	return 0;
} /*
3
3 1
2 3 4
1 4 5
2 6 7
3 0
2 3 4
1 4 5
2 6 7
3 1
2 3 4
1 4 5
2 6 7
*/