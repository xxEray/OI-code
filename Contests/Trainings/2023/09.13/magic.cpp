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

const int N = 1e5 + 5;
const int LOGN = 20;
const int M = 1e6 + 5;

int n, Q;

bool used[N];

std::vector<int> t[N << 2];
int m;
void link(int l, int r, int v) {
	l += m, r += m;
	l--, r++;
	for(; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if(~l & 1) t[l ^ 1].push_back(v);
		if(r & 1) t[r ^ 1].push_back(v);
	}
}
bool vis[N * LOGN];
struct Node { int k, ith; } a[N * LOGN];
std::vector<int> vct[N];
int p[N];

struct BIT {
	LL t[N];
	void add(int x, LL v) { while(x <= n) t[x] += v, x += x & -x; }
	LL query(int r) { LL ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	LL query(int l, int r) { return query(r) - query(l - 1); }
	void set(int x, LL v) { add(x, v - query(x, x)); }
} bit;

int main() {
#ifndef DEBUG
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
#endif
	read(n), read(Q);
	for(m = 1; m <= n; m <<= 1);
	int cnt = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j += i) {
			cnt++;
			link(j, std::min(j + i - 1, n), cnt);
			a[cnt].k = i, a[cnt].ith = (j - 1) / i;
			vct[i].push_back(0);
		}
	for(int i = 1; i <= n; i++) bit.set(i, 1);
	while(Q--) {
		int type;
		read(type);
		if(type == 1) {
			int x;
			read(x);
			if(used[x]) continue;
			used[x] = true;
			x += m;
			for(; x; x >>= 1) {
				for(int id : t[x]) {
					if(vis[id]) continue;
					vis[id] = true;
					int k = a[id].k, ith = a[id].ith;
					vct[k][ith] = 1;
					while(p[k] < (int)vct[k].size() && vct[k][p[k]]) p[k]++;
					bit.set(k, p[k] + 1);
				}
				t[x].clear();
			}
		} else {
			int l, r;
			read(l), read(r);
			write(bit.query(l, r), '\n');
		}
	}
	return 0;
}