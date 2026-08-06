// auto input
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

const int N = 2e5 + 5;

typedef long long LL;

int n;
LL a[N];
int fa[N];

int f[N];

int getf(int i) {
	if(f[i] == -1) return f[i] = getf(fa[i]) + (fa[i] < i);
	return f[i];
}

int main() {
	int T; read(T);
	while(T--) {
		read(n);
		for(int i = 1; i <= n; i++) read(a[i]);
		for(int i = 2; i <= n; i++) read(fa[i]);
		LL sum = std::accumulate(a + 2, a + n + 1, 0LL);
		if(sum != 0) { write(sum > 0 ? 1 : -1, '\n'); continue; }
		for(int i = 2; i <= n; i++) f[i] = -1;
		for(int i = 1; i <= n; i++) getf(i);
		// for(int i = 1; i <= n; i++) printf("f[%d] = %d\n", i, f[i]);
		__int128_t sum2 = 0;
		for(int i = 2; i <= n; i++) sum2 += a[i] * -f[i];
		if(sum2 < 0) write(-1, '\n');
		else if(sum2 > 0) write(1, '\n');
		else write(0, '\n');
	}
	return 0;
} /*
3
5
-5 -1 -1 -2 -7
1 1 5 3
5
5 5 5 9 8
1 1 5 3
5
-1 -2 3 -5 4
1 1 5 3
*/