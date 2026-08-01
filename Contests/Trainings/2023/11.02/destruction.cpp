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
using FIO::wrtc;
using FIO::write;
using FIO::read;

const int N = 2e6 + 5;

int main() {
#ifndef DEBUG
	freopen("destruction.in", "r", stdin);
	freopen("destruction.out", "w", stdout);
#endif
	int T; read(T);
	while(T--) {
		int n;
		read(n);
		if(n % 4 >= 2) { wrtc('-'), wrtc('1'), wrtc('\n'); continue; }
		if(n == 1) { wrtc('1'), wrtc('\n'); continue; }
		bool flag = (n % 4 == 1);
		std::vector<int> vct;
		int K = n / 4;
		for(int i = 4 * K; i >= 3 * K + 1; i--) vct.push_back(i);
		for(int i = 3 * K - 1; i >= 2 * K; i--) vct.push_back(i);
		vct.push_back(flag ? n : 1);
		for(int i = 2 * K - 1; i >= K + 1; i--) vct.push_back(i);
		vct.push_back(3 * K);
		for(int i = K; i >= 2; i--) vct.push_back(i);
		if(flag) vct.push_back(1);
		for(int x : vct) write(x, ' ');
		wrtc('\n');
	}
	return 0;
}