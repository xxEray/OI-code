#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 5e5 + 5;
const LL MOD = 998244353;

int n;
int a[N];

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

int main() {
	get_factorial(5e5);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i < n; i++) scanf("%d", &a[i]);
		for(int i = 1; i < n; i++) {
			LL ans = 0, sum = 0;
			for(int j = 1; j <= i; j++) 
		}
		puts("");
	}
	return 0;
}