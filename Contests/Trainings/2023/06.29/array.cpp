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

typedef __int128_t LL;

const int N = 300 + 5;
const LL LLINF = 1e25;

int n;
LL a[N][N];
std::vector<std::pair<LL, LL>> b[N];

LL suma[N][N];
LL f[N][N], g[N][N][N];

int main() {
	// freopen("data.txt", "r", stdin);
	read(n);
	for(int i = 1; i <= n; i++) for(int j = i; j <= n; j++) read(a[i][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) suma[i][j] = suma[i - 1][j] + suma[i][j - 1] - suma[i - 1][j - 1] + a[i][j];
	for(int i = 1; i <= n; i++) {
		int c; LL x, y;
		read(c);
		while(c--) read(x), read(y), b[i].push_back({-x, -y});
	}
	for(int k = 1; k <= n; k++) {
		std::sort(b[k].begin(), b[k].end());
		std::vector<std::pair<LL, LL>> q;
		for(auto &p : b[k]) {
			while((!q.empty() && q.back().first == p.first && q.back().second <= p.second) ||
				(q.size() >= 2 && q.back().first != p.first &&
			 	(LL)(p.second - q.back().second) * (q.back().first - q.end()[-2].first) >= (LL)(q.back().second - q.end()[-2].second) * (p.first - q.back().first)))
				q.pop_back();
			q.push_back(p);
		}
		for(int i = 1; i <= k; i++) {
			int now = (int)q.size() - 1;
			for(int j = k; j <= n; j++) {
				LL sum = suma[k][j] - suma[i - 1][j] - suma[k][k - 1] + suma[i - 1][k - 1];
				while(now >= 1 && sum * (q[now].first - q[now - 1].first) >= (q[now].second - q[now - 1].second)) now--;
				g[i][j][k] = q[now].second - sum * q[now].first;
			}
		}
	}
	for(int i = 0; i <= n + 1; i++) for(int j = 0; j <= n + 1; j++) f[i][j] = -LLINF;
	for(int i = 1; i <= n + 1; i++) f[i][i - 1] = 0;
	for(int len = 1; len <= n; len++) for(int i = 1; i + len - 1 <= n; i++) {
		int j = i + len - 1;
		for(int k = i; k <= j; k++) f[i][j] = std::max(f[i][j], f[i][k - 1] + f[k + 1][j] + g[i][j][k]);
	}
	write(f[1][n], '\n');
	return 0;
} /*


*/