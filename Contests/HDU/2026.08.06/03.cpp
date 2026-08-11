// auto input
#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in, *Iend = in, out[D], *O = out;
	char rdc() { return (I == Iend ? Iend = in + fread(I = in, 1, D, stdin) : 0), (I == Iend ? EOF : *I++); }
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
const int MAXV = 1e7;
const int B = 1000;

int n;

bool isprm[MAXV + 5];
std::vector<int> prime;
int phi[MAXV + 5];
void sieve(int ans) {
	for(int i = 2; i <= ans; i++) isprm[i] = true;
	phi[1] = 1;
	for(int i = 2; i <= ans; i++) {
		if(isprm[i]) prime.push_back(i), phi[i] = i - 1;
		for(int p : prime) {
			if((LL)p * i > ans) break;
			isprm[i * p] = false;
			if(i % p == 0) {
				phi[i * p] = phi[i] * p;
				break;
			} else phi[i * p] = phi[i] * phi[p];
		}
	}
}

LL ans[MAXV + 5], out[B + 5];

int main() {
#ifdef DEBUG
	freopen("out.txt", "w", stdout);
#endif
	sieve(1e7);
	int T; read(T);
	while(T--) {
		memset(out, 0, sizeof(out));
		memset(ans, 0, sizeof(ans));
		read(n);
		for(int i = 1; i <= n; i++) {
			int x;
			read(x), ans[x] = phi[x];
		}
		for(int p : prime)
			for(int j = MAXV / p; j >= 1; j--)
				ans[j] = std::max(ans[j], ans[j * p]);
		for(int i = 1; i <= MAXV; i++) ans[i] = ans[i] / phi[i] * i;
		for(int p : prime)
			for(int j = 1; (LL)j * p <= MAXV; j++)
				ans[j * p] = std::max(ans[j * p], ans[j]);
		for(int i = 1; i <= MAXV; i++) out[i % B] ^= ((i + B - 1) / B) * ans[i] * phi[i];
		for(int i = 0; i < B; i++) write(out[i], '\n');
	}
	return 0;
} /*
1
8
13 7 10 20 4 9 19 16
*/