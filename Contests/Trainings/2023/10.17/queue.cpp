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

const int N = 1e6 + 5;
const LL MOD = 998244353;

int n;
int tp[N], a[N];

int mx, cnt;
LL sum;
std::vector<int> fr[N];
LL out[N], prob[N];

LL inv[N];

int main() {
#ifndef DEBUG
	freopen("queue.in", "r", stdin);
	freopen("queue.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i <= n; i++) {
		read(tp[i]);
		if(tp[i] == 0) read(a[i]);
	}
	inv[1] = 1;
	for(int i = 2; i <= n; i++) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
	for(int i = 1; i <= n; i++)
		if(tp[i] == 0) {
			if(!mx) mx = i;
			else if(a[mx] < a[i]) {
				fr[i].push_back(mx);
				(sum += a[mx]) %= MOD;
				mx = i;
				cnt++;
			} else {
				fr[i].push_back(i);
				(sum += a[i]) %= MOD;
				cnt++;
			}
		} else {
			if(!mx) out[i] = 0;
			else if(!cnt) out[i] = a[mx], prob[i] = 1, fr[i].push_back(mx), mx = 0;
			else {
				prob[i] = inv[cnt];
				out[i] = sum * inv[cnt] % MOD;
				(sum *= (cnt - 1) * inv[cnt] % MOD) %= MOD;
				cnt--;
			}
		}
	LL ret = 0;
	for(int i = n; i >= 1; i--) {
		if(tp[i] == 1) ret = (ret * (1 - prob[i] + MOD) % MOD + prob[i] * i % MOD) % MOD;
		for(int j : fr[i]) out[j] = ret;
	}
	for(int i = 1; i <= n; i++) write(out[i], ' ');
	FIO::wrtc('\n');
	return 0;
} /*
10
0 300036489
0 49528961
1
0 450735376
0 8021539
1
1
1
0 727178284
1
*/
