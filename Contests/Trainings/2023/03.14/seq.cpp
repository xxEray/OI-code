#include <cstdio>
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
using FIO::rdc;
using FIO::write;
using FIO::read;

typedef long long LL;

const int N = 1e7 + 5;
const LL MOD = 99824435;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int m, L, R, X;
int a[N];

LL n;

LL f(LL k, LL d) { return (k + 2 * d - 1) * k / 2; }
LL ff(LL k) { return k * (k + 1) / 2; }

int main() {
#ifndef DEBUG
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
#endif
	read(m), read(L), read(R), read(X);
	for(int i = 0; i < m; i++) a[i] = rdc() - '0', a[i] += X, n += a[i];
	LL ans = 0, pow233 = 1;
	if(L == 0) (ans += (LL)n * (n - 1) / 2 + n) %= MOD, L++;
	int suma = 0;
	for(int i = 0; i < L; i++) suma += a[i];
	for(int i = 1; i < L; i++) (pow233 *= 233) %= MOD;
	for(int d = L; d <= R; d++) {
		(pow233 *= 233) %= MOD;
		LL cnt = suma / d - 1;
		LL ret = -LLINF;
		for(int i = 0; i <= n - suma; i++) {
			LL ms = n - suma - i;
			LL v = ff(i / 2) + ff((i + 1) / 2);
			LL v2 = (ms % cnt) * f(ms / cnt + 1, d);
			LL v3 = (cnt - ms % cnt) * f(ms / cnt, d);
//			printf("i=%d, v=%lld, v2=%lld, v3=%lld\n", i, v, v2, v3);
			ret = std::max(ret, (n - d + 2) * (n - d + 1) / 2 - v - v2 - v3);
		}
		ans ^= pow233 * (ret % MOD) % MOD;
//		printf("d = %d, ans = %lld\n", d, ret);
		suma += a[d];
	}
	write(ans, '\n');
	return 0;
}
