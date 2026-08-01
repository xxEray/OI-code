#include <cstdio>
#include <algorithm>
#include <vector>

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

const int N = 2e5 + 5;
const int CL = 2e5;

int n, m;
std::vector<int> a[N];
int bk[N];
int order[N];

int tmp[N];
void discrete() {
	m = 0;
	for(int i = 1; i <= n; i++) for(int j : a[i]) tmp[++m] = j;
	std::sort(tmp + 1, tmp + m + 1);
	m = std::unique(tmp + 1, tmp + m + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) for(int &j : a[i]) j = std::lower_bound(tmp + 1, tmp + m + 1, j) - tmp;
}

int f[N];

int main() {
	int T; read(T);
	while(T--) {
		read(n);
		for(int i = 1; i <= n; i++) {
			int K, x;
			a[i].clear();
			read(K);
			while(K--) {
				read(x);
				if(a[i].empty() || x > a[i].back()) a[i].emplace_back(x);
			}
			bk[i] = a[i].back();
		}
		discrete();
		for(int i = 1; i <= n; i++) order[i] = i;
		std::sort(order + 1, order + n + 1, [&](int x, int y) { return bk[x] < bk[y]; });
		for(int i = 0; i <= m; i++) f[i] = 0;
		int k = 0, ans = 0;
		for(int o = 1; o <= n; o++) {
			auto &arr = a[order[o]];
			int ret = 0, sz = arr.size();
			for(int j = 0; j < sz; j++) {
				while(k < arr[j] - 1) k++, f[k] = std::max(f[k - 1], f[k]);
				ret = std::max(ret, f[arr[j] - 1] + sz - j);
			}
			f[arr.back()] = std::max(f[arr.back()], ret);
			ans = std::max(ans, ret);
		}
		write(ans, '\n');
	}
	return 0;
}