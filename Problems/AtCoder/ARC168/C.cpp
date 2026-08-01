#include <bits/stdc++.h>

typedef long long LL;

const int N = 2.5e5 + 5;
const LL MOD = 998244353;

int n, K;
char s[N];

int cntA, cntB, cntC;

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
	scanf("%d%d%s", &n, &K, s + 1);
	for(int i = 1; i <= n; i++) cntA += (s[i] == 'A'), cntB += (s[i] == 'B'), cntC += (s[i] == 'C');
	get_factorial(n);
	LL ans = 0;
	for(int ab = 0; ab <= K; ab++)
		for(int bc = 0; bc <= K - ab; bc++)
			for(int ac = 0; ac <= K - ab - bc; ac++) {
				int bd = std::min({cntA - ab - ac, cntB - ab - bc, cntC - ac - bc, (K - ab - ac - bc) >> 1});
				for(int abc = 0; abc <= bd; abc++) {
					LL ret = 1;
					(ret *= C(cntA, ac) * C(cntA - ac, ab + abc) % MOD) %= MOD;
					(ret *= C(cntB, ab) * C(cntB - ab, bc + abc) % MOD) %= MOD;
					(ret *= C(cntC, bc) * C(cntC - bc, ac + abc) % MOD) %= MOD;
					// printf("ab = %d, bc = %d, ac = %d, abc = %d, ret = %lld\n", ab, bc, ac, abc, ret);
					(ans += ret * (abc ? 2 : 1)) %= MOD;
				}
			}
	printf("%lld\n", ans);
	return 0;
} /*
4 5
AABC
*/