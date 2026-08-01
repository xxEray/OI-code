#include <bits/stdc++.h>

typedef long long LL;

const int N = 200 + 5;
const LL MOD = 998244353;

int n;
char s[N];

int f[N / 2][N / 2][N][3][2], g[N / 2][N / 2][N][3][2];

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

constexpr inline int hsh(const char &c) { return c == 'r' ? 2 : (c == 'p' ? 0 : 1); }
constexpr inline bool can(const char &c, const char &c2) { return c == c2 || c == '?'; }
inline void mod(int &x) { (x >= MOD) && (x -= MOD); }

int main() {
#ifndef DEBUG
	freopen("rps.in", "r", stdin);
	freopen("rps.out", "w", stdout);
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	get_factorial(n);
	f[0][0][1][hsh('r')][0] = 1;
	int lastr = 0;
	for(int i = 1; i < n; i++) {
		for(int j = 0; j <= (i - lastr + 1) / 2; j++) for(int k = 0; k <= (i + 1) / 2; k++) for(int p = 0; p <= i; p++)
			for(int q = 0; q <= 2; q++) for(int r = 0; r <= 1; r++) g[j][k][p][q][r] = f[j][k][p][q][r], f[j][k][p][q][r] = 0;
		for(int curp = 0; curp <= (i - lastr + 1) / 2; curp++)
			for(int tots = 0; tots <= (i + 1) / 2; tots++)
				for(int extra = 1; extra <= i; extra++) {
					for(int afterr = 0; afterr <= 2; afterr++) {
						if(can(s[i + 1], 's')) mod(f[curp][tots + 1][extra][hsh('s')][afterr] += g[curp][tots][extra][hsh('p')][afterr]); // p -> s
						if(can(s[i + 1], 'p')) mod(f[curp + 1][tots][extra][hsh('p')][afterr] += g[curp][tots][extra][hsh('s')][afterr]); // s -> p
					}
					if(curp == 0) {
						if(can(s[i + 1], 's')) mod(f[0][tots + 1][extra][hsh('s')][hsh('s')] += g[0][tots][extra][hsh('r')][0]); // r -> s
						if(can(s[i + 1], 'p')) mod(f[1][tots][extra][hsh('p')][hsh('p')] += g[0][tots][extra][hsh('r')][0]); // r -> p
					}
					if(can(s[i + 1], 'r'))
						for(int last = 0; last <= 1; last++) for(int afterr = 0; afterr <= 1; afterr++) {
							int curs = curp - 1 + (afterr == hsh('s')) + (last == hsh('s'));
							int pres = tots - curs;
							LL coe = fac[tots - (last == hsh('s'))] * invfac[pres + 1 + (afterr == hsh('s'))] % MOD;
							(f[curp][tots][extra + curs])
						}
				}
		if(s[i] == 'r') lastr = i;
	}
	return 0;
}