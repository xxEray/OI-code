#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 25;
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

const int N = 1000 + 5;
const int MAXQ = 2e6 + 5;
const int MOD = 147744151;

typedef unsigned long long ull;
typedef __uint128_t u128;
struct Barrete {
	ull d;
	u128 m;
	Barrete(ull _d): d(_d), m(((u128)1 << 64) / _d) {}
	Barrete(): d(), m() {}
	ull operator()(ull x) {
		ull w = (ull)((m * x) >> 64);
		w = x - w * d;
		if(w >= d) w -= d;
		return w;
	}
} modulo;

int mod;
// ax + by = 1
int exgcd(int a, int b, int &x, int &y) {
	if(b == 0) {
		x = 1, y = 0;
		return a;
	}
	int g = exgcd(b, a % b, x, y);
	int tmp = x;
	x = y;
	y = tmp - a / b * y;
	return g;
}
int inv(int val) {
	int x, y;
	exgcd(val, mod, x, y);
	// printf("inv(%d) = %d\n", val, (x % mod + mod) % mod);
	return modulo(x % mod + mod);
}

int n, m, Q;
int a[N][N];

int factor[12], cfactor;
int power[N * N];
int prod[N][N], invprod[N][N];
int cnt[N][N];
int qxl[MAXQ], qyl[MAXQ], qxr[MAXQ], qyr[MAXQ], out[MAXQ];
void solve() {
	int vv = mod;
	for(int i = 2; i * i <= vv; i++) if(vv % i == 0) {
		factor[++cfactor] = i;
		while(vv % i == 0) vv /= i;
	}
	if(vv > 1) factor[++cfactor] = vv;
	for(int i = 1; i <= Q; i++) out[i] = 1;
	for(int k = 1; k <= cfactor; k++) {
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++) {
				cnt[i][j] = cnt[i][j - 1] + cnt[i - 1][j] - cnt[i - 1][j - 1];
				while(a[i][j] % factor[k] == 0) cnt[i][j]++, a[i][j] /= factor[k];
			}
		power[0] = 1;
		for(int i = 1; i <= cnt[n][m]; i++) power[i] = modulo((LL)power[i - 1] * factor[k]);
		for(int i = 1; i <= Q; i++) {
			int xl = qxl[i], xr = qxr[i], yl = qyl[i], yr = qyr[i];
			out[i] = modulo((LL)out[i] * power[cnt[xr][yr] - cnt[xl - 1][yr] - cnt[xr][yl - 1] + cnt[xl - 1][yl - 1]]);
		}
	}
	// fprintf(stderr, "solve done half, time = %d\n", (int)clock());
	prod[0][0] = 1, invprod[0][0] = 1;
	for(int i = 1; i <= n; i++) prod[i][0] = 1, invprod[i][0] = 1;
	for(int i = 1; i <= m; i++) prod[0][i] = 1, invprod[0][i] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			prod[i][j] = modulo(modulo(modulo((LL)prod[i - 1][j] * prod[i][j - 1]) * invprod[i - 1][j - 1]) * a[i][j]);
			invprod[i][j] = inv(prod[i][j]);
		}
	for(int i = 1; i <= Q; i++) {
		int xl = qxl[i], xr = qxr[i], yl = qyl[i], yr = qyr[i];
		out[i] = modulo(out[i] * modulo(modulo(modulo((LL)prod[xr][yr] * invprod[xl - 1][yr]) * invprod[xr][yl - 1]) * prod[xl - 1][yl - 1]));
	}
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) printf("[%d][%d]: a=%d, prod=%d, cnt[1]=%d, cnt[2]=%d\n", i, j, a[i][j], prod[i][j], cnt[1][i][j], cnt[2][i][j]);
}

int main() {
// #ifndef DEBUG
	freopen("tsuki.in", "r", stdin);
	freopen("tsuki.out", "w", stdout);
// #endif
	read(n), read(m), read(mod);
	modulo = Barrete(mod);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) read(a[i][j]);
	read(Q);
	for(int i = 1; i <= Q; i++) read(qxl[i]), read(qyl[i]), read(qxr[i]), read(qyr[i]);
	solve();
	int ans = 0;
	for(int i = 1; i <= Q; i++) (ans += i ^ out[i]) %= MOD;
	printf("%d\n", ans);
	return 0;
} /*
5 5 14
1 11 5 11 1
3 9 11 2 2
13 1 9 7 13
5 3 5 3 11
5 9 9 13 2
5
1 3 5 4
5 4 5 4
5 1 5 5
1 2 3 4
3 1 3 4
*/