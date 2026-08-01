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

typedef long long LL;

const int N = 5e4 + 5;
const int MAXK = 20 + 1;
const LL MOD = 1e9 + 7;
const LL inv2 = (MOD + 1) / 2;

int n, K, Q;
int a[N];

inline void mod(int &x) { if(x >= MOD) x -= MOD; }

struct Matrix { int a[MAXK][MAXK]; };
Matrix pre[N], ipre[N];
int sumpre[N][MAXK];

int main() {
	freopen("nondec.in", "r", stdin);
	freopen("nondec.out", "w", stdout);
	read(n), read(K);
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 0; i <= K; i++) pre[0].a[i][i] = ipre[0].a[i][i] = 1;
	for(int i = 1; i <= n; i++) {
		pre[i] = pre[i - 1];
		for(int j = 0; j <= K; j++) for(int k = 0; k <= a[i]; k++) mod(pre[i].a[j][a[i]] += pre[i - 1].a[j][k]);
		ipre[i] = ipre[i - 1];
		for(int j = 0; j <= a[i]; j++) for(int k = 0; k <= K; k++) mod(ipre[i].a[j][k] += ipre[i - 1].a[a[i]][k] * (MOD - inv2) % MOD);
		for(int j = 0; j <= K; j++) for(int k = 0; k <= K; k++) mod(sumpre[i][j] += pre[i].a[j][k]);
	}
	read(Q);
	while(Q--) {
		int l, r;
		read(l), read(r);
		LL ans = 0;
		for(int i = 0; i <= K; i++) (ans += (LL)ipre[l - 1].a[0][i] * sumpre[r][i]) %= MOD;
		write(ans, '\n');
	}
	return 0;
}