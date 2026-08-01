#include <cstdio>
#include <algorithm>
#include <bitset>
#include <queue>
#include <cassert>

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

const int N = 4000 + 5;

int n;
struct Node { int l, r, v; } a[N * N];
bool operator<(Node x, Node y) { return x.v < y.v; }

bool f[N][N], b[N][N];
std::bitset<N> l[N], r[N];

void bfs(int stl, int str) {
	b[stl][str] = true;
	if(f[stl][str]) return;
	// printf("insert [%d, %d]\n", stl, str);
	if(!f[stl + 1][str - 1] && ((r[stl] << 1) & l[str]).none()) return;
	std::queue<std::pair<int, int>> q;
	f[stl][str] = true;
	r[stl][str] = 1, l[str][stl] = 1;
	q.push({stl, str});
	while(!q.empty()) {
		int nl = q.front().first, nr = q.front().second;
		// printf("add [%d, %d]\n", nl, nr);
		q.pop();
		if(b[nl - 1][nr + 1] && !f[nl - 1][nr + 1]) {
			f[nl - 1][nr + 1] = true;
			r[nl - 1][nr + 1] = 1, l[nr + 1][nl - 1] = 1;
			q.push({nl - 1, nr + 1});
		}
		auto s = ~r[nl] & r[nr + 1];
		for(int xr = s._Find_first(); xr < (int)s.size(); xr = s._Find_next(xr)) {
			f[nl][xr] = true;
			r[nl][xr] = 1, l[xr][nl] = 1;
			q.push({nl, xr});
		}
		s = ~l[nr] & l[nl - 1];
		for(int xl = s._Find_first(); xl < (int)s.size(); xl = s._Find_next(xl)) {
			f[xl][nr] = true;
			r[xl][nr] = 1, l[nr][xl] = 1;
			q.push({xl, nr});
		}
	}
}

int main() {
	read(n);
	int c = 0;
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j += 2) read(a[++c].v), a[c].l = i, a[c].r = j;
	assert(c == n * n / 4);
	std::sort(a + 1, a + n * n / 4 + 1);
	for(int i = 1; i <= n; i++) f[i][i - 1] = true;
	int ans = 0;
	for(int i = 1; i <= n * n / 4; i++) {
		ans = a[i].v;
		b[a[i].l][a[i].r] = true;
		// printf("i = %d\n", i);
		bfs(a[i].l, a[i].r);
		if(f[1][n]) break;
	}
	printf("%d\n", ans);
	return 0;
} /*
10
20 21 2 11 25 3 24 18 8 6 17 7 5 22 4 23 14 15 1 19 16 12 10 13 9
*/