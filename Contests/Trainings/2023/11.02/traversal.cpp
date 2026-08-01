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

const int N = 2e6 + 5;
const LL MOD = 998244353;

LL f[N][2], pref[N][2], g[N], h[N], g2[N], h2[N];

void preprocess(int mx) {
	LL sum[2] = {0, 0};
	f[0][0] = 1, sum[0] = 1;
	for(int i = 1; i <= mx; i++) {
		for(int j : {0, 1}) f[i][j] = sum[!j];
		for(int j : {0, 1}) (sum[j] += f[i][j]) %= MOD;
	}
	pref[0][0] = f[0][0], pref[0][1] = f[0][1];
	for(int i = 1; i <= mx; i++) pref[i][0] = (pref[i - 1][0] + f[i][0]) % MOD, pref[i][1] = (pref[i - 1][1] + f[i][1]) % MOD;
	g[1] = 1;
	for(int i = 3; i <= mx; i += 2) g[i] = g[i - 2] * 2 % MOD;
	h[2] = 1;
	for(int i = 4; i <= mx; i += 2) h[i] = h[i - 2] * 2 % MOD;
	g2[2] = 1;
	for(int i = 4; i <= mx; i += 2) g2[i] = g[i - 1];
	h2[1] = 1;
	for(int i = 3; i <= mx; i += 2) h2[i] = g[i - 2];
}

int main() {
#ifndef DEBUG
	freopen("traversal.in", "r", stdin);
	freopen("traversal.out", "w", stdout);
#endif
	preprocess(2e6);
	int T; read(T);
	LL out = 0;
	while(T--) {
		int n, x, y;
		read(n), read(x), read(y);
		if((n & 1) ^ ((x ^ y) & 1) ^ 1) continue;
		LL ret = 0;
		if(x == 1) {
			if(y > 1) (ret += pref[y - 2][1] * h2[n - y + 1]) %= MOD;
			(ret += f[y - 1][1] * g[n - y + 1]) %= MOD;
		} else if(x == 2) {
			if(y > 1) (ret += (pref[y - 2][0] + pref[y - 2][1]) * g2[n - y + 1]) %= MOD;
			(ret += (f[y - 1][0] + f[y - 1][1]) * h[n - y + 1]) %= MOD;
		} else {
			if(y > 1) (ret += pref[y - 2][0] * h2[n - y + 1]) %= MOD;
			(ret += f[y - 1][0] * g[n - y + 1]) %= MOD;
		}
		// printf("%lld\n", ret);
		out ^= ret;
	}
	write(out, '\n');
	return 0;
}