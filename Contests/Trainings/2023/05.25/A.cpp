#include <bits/stdc++.h>

namespace FIO {
	const int D = (1 << 23) + 5;
	char in[D], *I = in, *Iend = in, out[D], *O = out;
	inline char rdc() { return I == Iend ? (Iend = in + fread(I = in, 1, D, stdin), (Iend == in ? EOF : *I++)) : *I++; }
	inline void wrtc(const char &c) { O == out + D ? (fwrite(O = out, 1, D, stdout), *O++ = c) : *O++ = c; }
	template<typename T> void read(T &x) {
		char ch = rdc();
		while(ch < '0' || ch > '9') ch = rdc();
		for(x = 0; '0' <= ch && ch <= '9'; ch = rdc()) x = x * 10 + (ch - '0');
	}
	template<typename T> void write(T x, const char &c = 0) {
		static int stk[100];
		int top = 0;
		if(!x) stk[top++] = '0';
		for(; x; x /= 10) stk[top++] = x % 10 + '0';
		for(top--; top >= 0; top--) wrtc(stk[top]);
		if(c) wrtc(c);
	}
	inline void flush() { fwrite(out, O - out, 1, stdout); }
}

typedef long long LL;

const int N = 1e7 + 5;
const LL MOD = 1e9 + 7;

int n, Q;
char s[N];

int nxt[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

int main() {
#ifndef DEBUG
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
	FIO::read(n), FIO::read(Q);
	char ch = FIO::rdc(); while(ch < 'a' || ch > 'z') ch = FIO::rdc(); s[1] = ch;
	for(int i = 2; i <= n; i++) s[i] = FIO::rdc();
	for(int i = 2, j = 0; i <= n; i++) {
		while(j && s[j + 1] != s[i]) j = nxt[j];
		if(s[j + 1] == s[i]) j++;
		nxt[i] = j;
	}
//	for(int i = 1; i <= n; i++) printf("nxt[%d] = %d\n", i, nxt[i]);
	int cycle = nxt[n];
	if(!cycle) {
		while(Q--) FIO::write(n, '\n');
		FIO::flush();
		return 0;
	}
	for(int i =	nxt[nxt[n]]; i; i = nxt[i]) if(nxt[n] % (nxt[n] - i) == 0) { cycle = nxt[n] - i; break; }
	int total = nxt[n] / cycle;
	for(int i = nxt[n]; i + cycle <= n; i += cycle)
		if(!strncmp(s + 1, s + i + 1, cycle)) total++;
		else break;
	if(cycle * total == n) {
		while(Q--) {
			int c;
			FIO::read(c);
			FIO::write((total * qpow(2, c) % MOD + MOD - qpow(2, c) + 1) % MOD * cycle % MOD, '\n');
		}
		FIO::flush();
		return 0;
	}
//	printf("cycle = %d, now = %d, total = %d\n", cycle, nxt[n] / cycle, total);
	while(Q--) {
		int c;
		FIO::read(c);
		int now = nxt[n] / cycle;
		LL ans = n;
		while(c && now < total) (ans += (LL)now * cycle % MOD) %= MOD, now = std::min(now * 2, total), c--;
		assert(ans >= 0 && 1);
		assert(c >= 0);
		assert(c <= MOD);
		(ans += (LL)c * total % MOD * cycle % MOD) %= MOD;
		assert(ans >= 0 && 2);
		FIO::write(ans, '\n');
	}
	FIO::flush();
	return 0;
} /*
5 1
aaaba
3
*/