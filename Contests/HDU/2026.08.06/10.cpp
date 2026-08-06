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
using FIO::write;
using FIO::read;

typedef long long LL;

LL calc(LL sum, LL cnt) {
	LL lw = sum / cnt, up = sum / cnt + 1;
	LL cntup = sum % cnt;
	LL ret = sum * sum;
	ret -= lw * lw * (cnt - cntup);
	ret -= up * up * cntup;
	// printf("calc %lld %lld = %lld\n", sum, cnt, ret / 2);
	return ret / 2;
}

int main() {
	int T; read(T);
	while(T--) {
		LL x, y;
		read(x), read(y);
		LL ans = 0;
		if(y) ans = std::max(ans, calc(x + y, y));
		if(x) ans = std::max(ans, calc(x + y, y + 1));
		write(ans, '\n');
	}
	return 0;
} /*
3
2 2
3 4
1 6
*/