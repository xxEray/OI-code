#include <bits/stdc++.h>
#include <bits/extc++.h>

#ifndef DEBUG
	#undef assert
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

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, A, B;
int D;
LL a[N];

std::bitset<N> bs;
bool bs2[N];

std::unordered_map<LL, LL> mem;
LL f(int i, int j, int k) {
	assert(i >= j), assert(std::abs(k) <= 2 * D), assert(i - j <= B);
	if(j < 0 || i >= n || i - j > B) return -LLINF;
	if(i == 0 && j == 0) return k == 0 ? 0 : -LLINF;
	if(!bs2[i] || !bs2[j]) return -LLINF;
	LL h = ((LL)i << 32) | ((LL)j << 13) | (k + 2048);
	if(mem.find(h) != mem.end()) return mem[h];
	LL ret;
	if(i - A >= j) ret = f(i - A, j, k - 1) + A * (a[i] ^ a[i - A]);
	else ret = f(j, i - A, -k + 1) + (i - j) * (a[i] ^ a[j]);
	return mem[h] = std::max(ret, f(j, i - B, -k + 1) + (i - j) * (a[i] ^ a[j]));
}

int main() {
	read(n), read(A), read(B);
	D = (n + A - 1) / A;
	for(int i = n - 1; i >= 0; i--) read(a[i]);
	bs[0] = 1;
	for(int _  = 0; _ <= D; _++) bs |= bs << A;
	for(int _  = 0; _ <= D; _++) bs |= bs << B;
	for(int i = 0; i <= n + A; i++) bs2[i] = bs[i];
	LL ans = -LLINF;
	for(int i = 0; i <= A; i++) if(bs2[n + i]) ans = std::max({ans, f(n + i - A, n + i - A, 0), f(n + i - A, n + i - B, 0), f(n + i - B, n + i - B, 0)});
	write(ans, '\n');
	return 0;
} /*
11 4 6
812 264 1022 445 77 763 73 577 22 729 716
*/