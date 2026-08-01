#include <cstdio>
#include <algorithm>
#include <iostream>
#include <streambuf>
inline char rdc() {
	const int D = 1 << 23;
	static char buf[D], *p1, *p2;
	static std::streambuf *in = std::cin.rdbuf();
	return (p1 == p2 && (p2 = (p1 = buf) + in->sgetn(buf, D), p1 == p2) ? -1 : *p1++);
}
template<typename T> void read(T &x) {
	char c = rdc(), fl = 0;
	while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
	for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
    if(fl) x = -x;
}
inline void wrtc(char c) {
	static std::streambuf *out = std::cout.rdbuf();
	out->sputc(c);
}
template<typename T> void write(T x, char ch = 0) {
	static char c[60]; int top = 0;
    if(x < 0) wrtc('-'), x = -x;
	do c[++top] = x % 10, x /= 10; while(x);
	while(top) wrtc(c[top--] + '0');
	if(ch) wrtc(ch);
}

typedef long long LL;

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

int f[N][21][21];

inline LL calc(LL x, int p) { return p < 0 ? x >> -p : x << p; }

int main() {
	int T, id; read(T), read(id);
	while(T--) {
		read(n);
		for(int i = 1; i <= n; i++) read(a[i]);
		for(int i = 0; i <= n; i++) for(int j = -19; j <= 127; j++) f[i][j + 19] = INF;
		f[0][0 + 19] = 0;
		for(int i = 1; i <= n; i++) {
			int p = -19, mn = INF;
			for(int j = -19; j <= 127; j++) {
				while(p <= 127 && calc(a[i - 1], p) <= calc(a[i], j)) mn = std::min(mn, f[i - 1][p + 19]), p++;
				f[i][j + 19] = mn + std::abs(j);
			}
		}
		int ans = INF;
		for(int j = -19; j <= 127; j++) ans = std::min(ans, f[n][j + 19]);
		printf("%d\n", ans);
	}
	return 0;
}
