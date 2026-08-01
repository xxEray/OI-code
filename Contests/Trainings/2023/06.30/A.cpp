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

const int N = 1.5e6 + 5;

int n, Q;
int a[N], b[N];

int main() {
	read(n), read(Q);
	for(int i = 1; i <= n; i++) read(a[i]);
	while(Q--) {
		int l, r;
		read(l), read(r);
		if(r - l + 1 >= 50) puts("YES");
		else {
			for(int i = l; i <= r; i++) b[i] = a[i];
			std::sort(b + l, b + r + 1);
			bool flag = false;
			for(int i = l; i <= r - 2; i++) flag |= (b[i] + b[i + 1] > b[i + 2]);
			puts(flag ? "YES" : "NO");
		}
	}
	return 0;
}