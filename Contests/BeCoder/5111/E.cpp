#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 490019;

int n, m;
LL C;
LL a[N], b[N];

LL fac[MOD + 5], invfac[MOD + 5];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(LL x, LL y) {
	if(x < 0 || y < 0 || x < y) return 0;
	else if(x < MOD) return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD;
	else return C(x % MOD, y % MOD) * C(x / MOD, y / MOD);
}
void get_factorial() {
	fac[0] = 1;
	for(int i = 1; i < MOD; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[MOD - 1] = inv(fac[MOD - 1]);
	for(int i = MOD - 1; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}



int main() {
	get_factorial();

	return 0;
}