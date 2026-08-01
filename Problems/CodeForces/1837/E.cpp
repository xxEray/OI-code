#include <bits/stdc++.h>

typedef long long LL;

const int N = (1 << 19) + 5;
const LL MOD = 998244353;

int n, m;
int a[N], b[N];

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
	scanf("%d", &m);
	n = (1 << m);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
		if(b[i] != -1) a[b[i]] = i;
		else b[i] = 0;
	}
	get_factorial(n);
	LL ans = 1;
	for(int i = 1; i <= m; i++) {
		int l = (1 << (m - i)) + 1, r = (1 << (m - i + 1));
		int cnt = 0;
		for(int j = l; j <= r; j++) cnt += (a[j] == 0);
		for(int j = 1; j <= n; j += (1 << i)) {
			int flag = 0;
			int tot = 0;
			for(int k = 0; k < (1 << i); k++) tot += (b[j + k] == 0), flag += !(b[j + k] < l || b[j + k] > r);
			if(!flag) {
				(ans *= tot) %= MOD;
				for(int k  = 0; k < (1 << i); k++) if(b[j + k] == 0) { b[j + k] = l; break; }
			} else if(flag > 1) ans = 0;
		}
		(ans *= fac[cnt]) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
}