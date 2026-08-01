#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char out[D], *O = out;
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

typedef long long LL;
typedef __uint128_t u128;

LL m;

u128 C[130][130];

u128 calc(u128 n, int K, int high) {
	// printf("calc %lld %d %d\n", (LL)n, K, high);
	if(!n || K <= 0) return 0;
	int nxthigh = high - 1;
	while((~n >> nxthigh & 1) && nxthigh >= 0) nxthigh--;
	return C[high][K] + calc(n ^ ((u128)1 << high), K - 1, nxthigh);
}
bool check1(u128 n, int K) {
	// printf("check1 %llu-%llu %d\n", (unsigned long long)(n >> 32), (unsigned long long)n, K);
	int i;
	for(i = 0; i <= 126 && n >= ((u128)1 << (i + 1)); i++);
	return calc(n << 1, K, i + 1) - calc(n, K, i) >= (u128)m;
}
bool check2(u128 n, int K) {
	int i;
	for(i = 0; i <= 126 && n >= ((u128)1 << (i + 1)); i++);
	return calc(n << 1, K, i + 1) - calc(n, K, i) > (u128)m;
}

int main() {
#ifndef DEBUG
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
#endif
	for(int i = 0; i <= 128; i++) C[i][0] = 1;
	for(int i = 1; i <= 128; i++) for(int j = 1; j <= i; j++) C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	int T; scanf("%d", &T);
	while(T--) {
		int K;
		scanf("%lld%d", &m, &K);
		u128 l = 1, r = ((u128)1 << 127) - 1;
		while(l < r) {
			u128 mid = l + ((r - l) >> 1);
			if(check1(mid, K)) r = mid;
			else l = mid + 1;
		}
		u128 mn = l;
		l = 1, r = ((u128)1 << 127) - 1;
		while(l < r) {
			u128 mid = l + ((r - l) >> 1);
			if(check2(mid, K)) r = mid;
			else l = mid + 1;
		}
		u128 cnt = l - mn;
		write(mn, ' '), write(cnt, '\n');
	}
	return 0;
}