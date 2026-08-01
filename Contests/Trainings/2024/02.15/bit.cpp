#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

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

const int N = (1 << 16) + 5;
const int U = (1 << 16) - 1;

int n, Q;
int a[N][19];

int f[2][N][19][19];

int main() {
#ifndef DEBUG
	freopen("bit.in", "r", stdin);
	freopen("bit.out", "w", stdout);
#endif
	read(n), read(Q);
	for(int i = 1; i <= n; i++) { int x; read(x); f[0][x][0][0]++; }
	for(int i = 0; i < 16; i++) {
		memset(f[~i & 1], 0, sizeof(f[~i & 1]));
		for(int s = 0; s <= U; s++)
			for(int j = 0; j <= i + 1; j++)
				for(int k = 0; k <= i + 1 - j; k++)
					if(s >> i & 1) {
						f[~i & 1][s][j][k + 1] += f[i & 1][s][j][k];
						f[~i & 1][s][j][k] += f[i & 1][s ^ (1 << i)][j][k];
					} else {
						f[~i & 1][s][j][k] += f[i & 1][s][j][k];
						f[~i & 1][s][j + 1][k] += f[i & 1][s | (1 << i)][j][k];
					}
	}
	while(Q--) {
		LL A, B, C;
		int k, x;
		read(A), read(B), read(C), read(k), read(x);
		std::vector<std::pair<LL, int>> vct;
		int sz = __builtin_popcount(x);
		for(int i = 0; i <= 16; i++) for(int j = 0; j <= 16 - i; j++) if(f[0][x][i][j])
			// printf("(%d,%d): %d\n", i, j, cnt[x][i][j]),
			vct.emplace_back(A * j + B * (i + sz) + C * (i + sz - j), f[0][x][i][j]);
		std::sort(vct.begin(), vct.end());
		for(auto [v, c] : vct) {
			if(k > c) k -= c;
			else { write(v, '\n'); break; }
		}
	}
	return 0;
} /*
5 4
1 2 3 4 5
1 0 0 1 3
1 0 1 5 3
2 7 6 4 7
3 1 9 2 6
*/