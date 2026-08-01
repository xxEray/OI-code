#pragma GCC optimize("Ofast")

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

const int N = 5e5 + 5;

int n, K;
int a[N];

std::bitset<N> allbs, bs[40];

int calc(int val) {
	std::bitset<N> ret = allbs;
	for(int i = 0; i < 30; i++) if(!(val >> i & 1)) ret &= bs[i];
	return ret.count();
}

std::vector<int> st;
std::unordered_set<int> inq;
std::priority_queue<LL> q;
void insert(int val) {
	if(inq.count(val)) return;
	inq.insert(val);
	q.push((LL)calc(val) << 32 | val);
}

int main() {
#ifndef DEBUG
	freopen("afo.in", "r", stdin);
	freopen("afo.out", "w", stdout);
#endif
	read(n), read(K);
	for(int i = 1; i <= n; i++) allbs[i] = 1;
	for(int i = 1; i <= n; i++) {
		read(a[i]);
		for(int j = 0; j < 30; j++) bs[j][i] = !(a[i] >> j & 1);
	}
	int U = (1 << 30) - 1;
	insert(U);
	while((int)st.size() < K) {
		int u = q.top() & U;
		q.pop();
		st.push_back(u);
		for(int i = 0; i < 30; i++) if(u >> i & 1) insert(u & ~(1 << i));
	}
	for(int x : st) write(x, ' ');
	return 0;
}