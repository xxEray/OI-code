#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <bits/stdc++.h>

#define SZ(x) ((int)(x).size())

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

const int N = 1e5 + 5;
const int B = 200;
const int R = 250;

int n, Q;
int a[N];

int out[N];

int cnt[N], nxt[N], len[N], pos[N];
int calc(int K) {
	if(out[K]) return out[K];
	__builtin_memset(cnt, 0, sizeof(cnt));
	int j = 1;
	for(int i = 1; i <= n; i++) {
		while(cnt[a[j]] < K) cnt[a[j]]++, j = (j == n ? 1 : j + 1);
		nxt[i] = j, cnt[a[i]]--;
	}
	for(int i = n; i >= 1; i--) {
		if(nxt[i] < i) len[i] = 1, pos[i] = nxt[i];
		else len[i] = len[nxt[i]] + 1, pos[i] = pos[nxt[i]];
	}
	int ret = n + 1;
	for(int i = 1; i <= nxt[1]; i++)
		if(pos[i] >= i) ret = std::min(ret, len[i]);
		else ret = std::min(ret, len[i] + 1);
	return out[K] = ret;
}

int main() {
#ifndef DEBUG
	freopen("follow.in", "r", stdin);
	freopen("follow.out", "w", stdout);
#endif
	read(n), read(Q);
	for(int i = 1; i <= n; i++) read(a[i]), cnt[a[i]]++;
	int mx = *std::max_element(cnt + 1, cnt + n + 1);
	__builtin_memset(cnt, 0, sizeof(cnt));
	for(int i = 1; i <= std::min(mx - 1, B); i++) out[i] = calc(i);
	for(int i = mx; i <= n; i++) out[i] = 1;
	int bd = mx - 1;
	for(int i = 2; i <= std::min(n / B, R); i++) {
		if(calc(bd) != i) continue;
		int l = B + 1, r = bd;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(calc(mid) == i) r = mid;
			else l = mid + 1;
		}
		for(int j = l; j <= bd; j++) out[j] = i;
		bd = l - 1;
	}
	while(Q--) { int x; read(x); write(out[x], '\n'); }
	return 0;
}