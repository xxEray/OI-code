// #pragma GCC optimize("Ofast", "inline", "-ffast-math")
// #pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <bits/stdc++.h>

#define SZ(x) ((int)(x).size())

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
	void read(char *s) {
		char ch = rdc();
		int c = 0;
		while(ch < '0' || ch > '9') ch = rdc();
		for(; '0' <= ch && ch <= '9'; ch = rdc()) s[c++] = ch;
		s[c] = 0;
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

const int N = 3e5 + 5;
const LL MOD = 1e9 + 7;

std::vector<std::pair<LL, int>> factor;
LL K2;
int Q;
std::vector<LL> q;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL qpow2(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % (MOD - 1); if(!(y >>= 1)) return ret; x = x * x % (MOD - 1); } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL fac[N], invfac[N];
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

namespace Solve {
	int m;
	LL f[N], g[N];
	LL zip(const std::vector<int> &vct) {
		for(int i = 0; i < SZ(factor); i++) assert(vct[i] <= factor[i].second);
		LL h = 0;
		for(int i = SZ(factor) - 1; i >= 0; i--) h = h * (factor[i].second + 1) + vct[i];
		return h;
	}
	std::vector<int> unzip(LL h) {
		assert(h < m);
		std::vector<int> vct(SZ(factor));
		for(int i = 0; i < SZ(factor); i++) vct[i] = h % (factor[i].second + 1), h /= factor[i].second + 1;
		return vct;
	}
	int power[20];
	LL phi[N], power2[20][N], power3[20][N], invv[20];
	void solve() {
		for(int i = 0; i < m; i++) g[i] = f[i] * phi[i] % MOD;
		for(int j = 0; j < SZ(factor); j++)
			for(int i = m - 1; i >= 0; i--)
				if(i / power[j] % (factor[j].second + 1) < factor[j].second)
					(g[i] += g[i + power[j]]) %= MOD;
		for(int i = 0; i < m; i++) {
			auto vct = unzip(i);
			for(int j = 0; j < SZ(factor); j++) (g[i] *= power2[j][vct[j]]) %= MOD;
		}
		for(int i = 0; i < m; i++) {
			auto vct = unzip(i);
			for(int j = 0; j < SZ(factor); j++) vct[j] = factor[j].second - vct[j];
			int i_ = zip(vct);
			if(i < i_) std::swap(g[i], g[i_]);
		}
		for(int j = 0; j < SZ(factor); j++)
			for(int i = 0; i < m; i++)
				if(i / power[j] % (factor[j].second + 1) < factor[j].second)
					(g[i] += MOD - g[i + power[j]]) %= MOD;
		for(int i = 0; i < m; i++) (g[i] *= inv(phi[i])) %= MOD;
		for(int i = 0; i < m; i++) f[i] = g[i];
	}
	void main() {
		m = 1;
		for(auto [p, c] : factor) m *= c + 1;
		for(int i = 0; i < SZ(factor); i++) invv[i] = inv(factor[i].first);
		for(int i = 0; i < SZ(factor); i++) {
			power2[i][0] = 1, power3[i][0] = 1;
			for(int j = 1; j <= factor[i].second; j++) {
				power2[i][j] = power2[i][j - 1] * factor[i].first % MOD;
				power3[i][j] = power3[i][j - 1] * factor[i].first % (MOD - 1);
			}
		}
		power[0] = 1;
		for(int i = 0; i < SZ(factor); i++) power[i + 1] = power[i] * (factor[i].second + 1);
		for(int i = 0; i < m; i++) {
			auto vct = unzip(i);
			phi[i] = 1;
			f[i] = 1;
			for(int j = 0; j < SZ(factor); j++) {
				(f[i] *= power2[j][vct[j]]) %= MOD;
				(phi[i] *= power2[j][factor[j].second - vct[j]]) %= MOD;
				if(factor[j].second - vct[j]) (phi[i] *= invv[j] * (factor[j].first - 1) % MOD) %= MOD;
			}
			(f[i] *= phi[i]) %= MOD;
		}
		for(int j = 0; j < SZ(factor); j++)
			for(int i = 0; i < m; i++)
				if(i / power[j] % (factor[j].second + 1))
					(f[i] += f[i - power[j]]) %= MOD;
		solve();
		for(int i = 0; i < m; i++) f[i] = qpow(f[i], K2);
		solve();
		LL n = 1, n2 = 1;
		for(auto [p, c] : factor) {
			(n *= qpow(p, c)) %= MOD;
			(n2 *= qpow2(p, c)) %= MOD - 1;
		}
		for(int i = 0; i < m; i++) (f[i] *= inv(n)) %= MOD;
		write(qpow(n, 2 * K2 % (MOD - 1)), '\n');
		for(int i = 0; i < m; i++) g[i] = f[i];
		for(int j = 0; j < SZ(factor); j++)
			for(int i = m - 1; i >= 0; i--)
				if(i / power[j] % (factor[j].second + 1))
					(g[i] += MOD - g[i - power[j]]) %= MOD;
		LL ans = 0;
		for(int i = 0; i < m; i++) {
			auto vct = unzip(i);
			LL t = 1, t2 = 1;
			for(int j = 0; j < SZ(factor); j++) {
				(t *= power2[j][vct[j]]) %= MOD;
				(t2 *= power3[j][vct[j]]) %= MOD - 1;
			}
			if(qpow(3, t2) == 1) (ans += g[i] * n % MOD * inv(t)) %= MOD;
			else (ans += g[i] * (qpow(3, n2) - 1) % MOD * inv(qpow(3, t2) - 1) % MOD + MOD) %= MOD;
		}
		write(ans, '\n');
		for(auto x : q) {
			std::vector<int> vct(SZ(factor));
			for(int j = 0; j < SZ(factor); j++) while(x % factor[j].first == 0 && vct[j] < factor[j].second) x /= factor[j].first, vct[j]++;
			int i = zip(vct);
			write(f[i], '\n');
		}
	}
}

char str[N];

int main() {
#ifndef DEBUG
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	get_factorial(3e5);
	int cnt;
	read(cnt);
	for(int i = 1; i <= cnt; i++) { LL p; int c; read(p), read(c); factor.emplace_back(p, c); }
	read(str + 1);
	int len = strlen(str + 1);
	for(int i = 1; i <= len; i++) K2 = (K2 * 10 + str[i] - '0') % (MOD - 1);
	read(Q);
	for(int i = 1; i <= Q; i++) { LL x; read(x); q.emplace_back(x); }
	Solve::main();
	return 0;
} /*
2
2 2
3 1
2
5
0
1
2
3
4
*/