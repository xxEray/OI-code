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
typedef __int128_t i128;

LL n;

i128 sum(LL l, LL r) { return l > r ? (i128)0 : (i128)(l + r) * (r - l + 1) / 2; }

int main() {
#ifndef DEBUG
	freopen("square.in", "r", stdin);
	freopen("square.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld", &n);
		int l = 1, r = 1e9 + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if((LL)mid * mid - 1 <= n) l = mid + 1;
			else r = mid;
		}
		int val = l - 1;
		i128 ans = sum(1, n);
		LL mx = 0;
		for(; (LL)val * val / 2 <= n; val++) {
			ans -= sum(std::max(mx + 1, (LL)val * val - n), ((LL)val * val - 1) / 2);
			mx = ((LL)val * val - 1) / 2;
		}
		write(ans, '\n');
	}
	return 0;
} /*
1
7
*/