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
using FIO::wrtc;
using FIO::write;
using FIO::read;

const int N = 20 + 3;
const int MAXS = (1 << 20) + 5;

int n, Q;

bool f[N][MAXS];

int main() {
	read(n);
	int U = (1 << n) - 1;
	for(int s = 0; s <= U; s++) f[0][s] = rdc() - '0';
	for(int i = 0; i < n; i++)
		for(int s = 0; s <= U; s++)
			f[i + 1][s] = ((s >> i & 1) ? (f[i][s & ~(1 << i)] | f[i][s | (1 << i)]) : (f[i][s & ~(1 << i)] & f[i][s | (1 << i)]));
	// for(int i = 0; i <= n; i++) for(int s = 0; s <= U; s++) printf("f[%d][%d] = %d\n", i, s, f[i][s]);
	read(Q);
	while(Q--) {
		int s;
		read(s);
		wrtc(f[n][s] + '0');
	}
	return 0;
} /*
3
11000011
*/