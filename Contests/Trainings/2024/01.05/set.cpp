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

typedef unsigned long long ull;

const int N = 1e5 + 5;

int V, Q;

std::set<ull> st;
std::set<std::pair<ull, ull>> ans;

void insert(ull x, ull y) {
	std::vector<ull> vct{0llu};
	for(int i = 0; i < V; i++) vct.emplace_back((~x & ((1llu << i) - 1)) + 1);
	for(int i = 0; i < V; i++) vct.emplace_back((~y & ((1llu << i) - 1)) + 1);
	// for(int i = 0; i < V; i++) if((x >> i & 1) && (!i || (~x >> (i - 1) & 1)))
	// 	for(int j = i; j < V; j++) if(y >> j & 1) {
	// 		ull val = ~x & ((1llu << j) - 1) & ~((1llu << i) - 1);
	// 		val |= 1llu << i;
	// 		vct.emplace_back(val);
	// 	}
	// for(int i = 0; i < V; i++) if((y >> i & 1) && (!i || (~y >> (i - 1) & 1)))
	// 	for(int j = i; j < V; j++) if(x >> j & 1) {
	// 		ull val = ~y & ((1llu << j) - 1) & ~((1llu << i) - 1);
	// 		val |= 1llu << i;
	// 		vct.emplace_back(val);
	// 	}
	std::sort(vct.begin(), vct.end());
	vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
	ull mn = (1llu << V) + 1;
	// printf("insert %llu %llu\n", x, y);
	for(auto z : vct) {
		// printf("try %llu\n", z);
		if(((x + z) ^ (y + z)) < mn) {
			mn = ((x + z) ^ (y + z));
			auto it = ans.lower_bound({z, 0});
			while(true) {
				if(it == ans.end() || it->second < mn) break;
				it = ans.erase(it);
			}
			it = ans.upper_bound({z, (1llu << V) + 1});
			if(it == ans.begin() || (--it)->second > mn) /* printf("(%llu, %llu)\n", z, mn),  */ans.emplace(z, mn);
		}
	}
}

int main() {
#ifndef DEBUG
	freopen("set.in", "r", stdin);
	freopen("set.out", "w", stdout);
#endif
	read(V), read(Q);
	int cnt = 0;
	while(Q--) {
		int op;
		ull x;
		read(op), read(x);
		if(op == 1) {
			cnt++;
			auto [it, _] = st.emplace(x);
			if(it != st.begin()) insert(*std::prev(it), x);
			if(std::next(it) != st.end()) insert(x, *std::next(it));
		} else if(op == 2) {
			if(cnt < 2) { puts("oh"); continue; }
			auto it = ans.upper_bound({x, (1llu << V) + 1});
			assert(it != ans.begin());
			// for(auto [x, y] : ans) printf("%llu, %llu\n", x, y);
			write((--it)->second, '\n');
		}
	}
	return 0;
}