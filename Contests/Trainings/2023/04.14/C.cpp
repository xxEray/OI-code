#include <cstdio>
#include <algorithm>
#include <vector>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D, out[D], *O = out;
	// char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	char rdc() { return getchar(); }
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
using FIO::wrtc;
using FIO::write;
using FIO::read;

const int SQRTN = 2304 + 5;
const int INF = 0x3f3f3f3f;

int n, m, C;

std::vector<int> factors;

int f[SQRTN][SQRTN], last[SQRTN][SQRTN];
int mul[SQRTN][SQRTN], dv[SQRTN][SQRTN];

std::vector<int> ansv;

void print(int i, int j) {
	if(i == 0) return;
	if(last[i][j] == -1) { print(i - 1, j); return; }
	print(i, dv[j][last[i][j]]);
	ansv.push_back(factors[last[i][j]]);
}

int main() {
	// freopen("C.in", "r", stdin);
	// freopen("C.out", "w", stdout);
	int T; read(T);
	while(T--) {
		factors.clear();
		read(n), read(C);
		for(int i = 1; i * i <= C; i++)
			if(C % i == 0) {
				factors.push_back(i);
				if(i != C / i) factors.push_back(C / i);
			}
		m = factors.size();
		std::sort(factors.begin(), factors.end());
		// printf("factors: "); for(int i : factors) printf("%d ", i); puts("");
		for(int oi = 0; oi < m; oi++) {
			for(int oj = 0, ok = 0; oj < m && (long long)factors[oi] * factors[oj] <= C; oj++) {
				while(ok < m && factors[ok] < factors[oi] * factors[oj]) ok++;
				if(factors[oi] * factors[oj] != factors[ok]) { mul[oi][oj] = -1; continue; }
				mul[oi][oj] = ok, dv[ok][oi] = oj, dv[ok][oj] = oi;
			}
		}
		for(int oi = 0; oi < m; oi++) for(int oj = 0; oj < m; oj++) f[oi][oj] = INF;
		f[0][0] = 0;
		for(int oi = 0; oi < m; oi++) {
			for(int oj = 0; oj < m; oj++) oi ? f[oi][oj] = f[oi - 1][oj] : 0, last[oi][oj] = -1;
			for(int oj = 0; oj < m; oj++)
				if((long long)factors[oj] * factors[oi] <= C && mul[oi][oj] >= 0) {
					if(f[oi][oj] + 1 < f[oi][mul[oi][oj]])
						f[oi][mul[oi][oj]] = f[oi][oj] + 1, last[oi][mul[oi][oj]] = oi;
				}
			// printf("f[%d]: ", factors[oi]);
			// for(int oj = 0; oj < m; oj++) printf("[%d]=%d ", factors[oj], f[oi][oj]);
			// puts("");
		}
		int ans = INF, ansidx, ansidy, ansidz;
		int last = factors.front(), mn = factors.front();
		for(int oi = 0; oi < m; oi++) {
			int i = factors[oi];
			if(last == i - 1) last = i;
			else mn = last = i;
			int x = m - 1;
			for(int j = 0; j <= std::min(i - mn, n - 1); j++) {
				if(factors[x] % (i - j) == 0) x = dv[x][oi - j];
				else break;
				if(f[oi][x] <= n - j - 1 && ans > i + n - j - 1)
					ans = i + n - j - 1, ansidx = oi, ansidy = j, ansidz = x;
				// printf("i=%d, j=%d, ans=%d\n", i, j, ans);
			}
		}
		// printf("ans = %d\n", ans);
		// printf("ansid = %d, %d, %d\n", ansidx, ansidy, ansidz);
		ansv.clear();
		print(ansidx, ansidz);
		while((int)ansv.size() < n - ansidy - 1) ansv.push_back(1);
		std::sort(ansv.begin(), ansv.end());
		for(int i = 0; i <= ansidy; i++) ansv.push_back(factors[ansidx] - i);
		// for(int x : ansv) printf("%d ", x);
		// puts("");
		for(int i = 0; i < n; i++) ansv[i] += i;
		for(int i = 0; i < n; i++) write(ansv[i], ' ');
		wrtc('\n');
	}
	return 0;
}