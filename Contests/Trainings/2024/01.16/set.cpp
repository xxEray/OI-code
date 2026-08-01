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

const int N = (1 << 11) + 5;

int n;
int a[N][N];

int w[N][N], nw[N][N];

int main() {
#ifndef DEBUG
	freopen("set.in", "r", stdin);
	freopen("set.out", "w", stdout);
#endif
	read(n);
	for(int i = 0; i < (1 << n); i++) for(int j = 0; j < (1 << n); j++) read(w[i][j]);
	for(int k = n - 1; k >= 0; k--) {
		for(int i = 0; i < (1 << n); i++) for(int j = 0; j < (1 << n); j++) nw[i][j] = 0;
		for(int i = 0; i < (1 << n); i++) for(int j = 0; j < (1 << n); j++) if(w[i][j]) {
			auto set = [&](int x, int y) { nw[x & ((1 << n) - 1)][y & ((1 << n) - 1)] ^= 1; };
			set(i, j), set(i - (1 << k), j), set(i + (1 << k), j), set(i, j - (1 << k)), set(i, j + (1 << k));
		}
		for(int i = 0; i < (1 << n); i++) for(int j = 0; j < (1 << n); j++) w[i][j] = nw[i][j];
	}
	// for(int i = 0; i < (1 << n); i++) for(int j = 0; j < (1 << n); j++) printf("%d%c", w[i][j], " \n"[j == (1 << n)]);
	std::vector<std::pair<int, int>> ans;
	for(int i = 0; i < (1 << n); i++) for(int j = 0; j < (1 << n); j++) if(w[i][j]) ans.emplace_back(i, j);
	write((int)ans.size(), '\n');
	for(auto [x, y] : ans) write(x, ' '), write(y, '\n');
	return 0;
}