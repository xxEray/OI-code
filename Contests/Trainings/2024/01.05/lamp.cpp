#include <bits/stdc++.h>

#ifndef DEBUG
	#undef assert
	#define assert(...) ((void)0)
#endif

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
int a[N];

int last[N], tin[N];

std::set<std::pair<int, int>> st;
std::vector<std::array<int, 3>> vct[N];

LL pref[N];

int main() {
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 1; i <= n; i++) last[i] = tin[a[i]], tin[a[i]] = i;
	for(int i = 0; i <= n; i++) tin[i] = 0;
	for(int i = n, mex = 0; i >= 1; i--) {
		tin[a[i]]++;
		if(tin[mex]) {
			while(tin[mex]) mex++;
			st.emplace(i, mex);
		} else if(i == n) st.emplace(n, mex);
	}
	// printf("st: "); for(auto [r, v] : st) printf("(%d, %d) ", r, v); puts("");
	for(int i = n; i >= 1; i--) {
		int j = last[i] + 1;
		if(last[i]) {
			auto it = st.lower_bound({last[i], 0});
			assert(it != st.end());
			if(it->first > last[i]) st.emplace(last[i], it->second);
		}
		while(true) {
			auto it = st.lower_bound({j, 0});
			assert(it != st.end());
			if(it->second <= a[i]) break;
			int r = it->first, v = it->second;
			auto it2 = st.erase(it);
			vct[i].push_back({j, r, v - a[i]});
			if(it2 == st.end() || it2->second < a[i]) st.emplace(r, a[i]);
			// if(last[i] && j == last[i] + 1) {
			// 	auto it3 = st.lower_bound({last[i], 0});
			// 	assert(it3 != st.end());
			// 	if(it3->first > last[i]) st.emplace(last[i], v);
			// }
			j = r + 1;
		}
		// printf("st(i=%d): ", i); for(auto [r, v] : st) printf("(%d, %d) ", r, v); puts("");
	}
	// for(int i = 1; i <= n; i++) {
	// 	printf("vct[%d]: ", i);
	// 	for(auto [l, r, v] : vct[i]) printf("([%d, %d], %d) ", l, r, v);
	// 	puts("");
	// }
	LL sum = 0;
	pref[0] = 1;
	for(int i = 1; i <= n; i++) {
		for(auto [l, r, v] : vct[i]) (sum += (pref[r - 1] - (l == 1 ? 0LL : pref[l - 2]) + MOD) % MOD * v % MOD) %= MOD;
		// printf("f[%d] = %lld\n", i, sum);
		pref[i] = (pref[i - 1] + sum) % MOD;
	}
	write(sum, '\n');
	return 0;
} /*
10
1 0 2 0 3 1 0 2 3 4
*/