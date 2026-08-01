#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 998244353;

int n;
char s[N], t[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

LL f[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%s%s", &n, s + 1, t + 1);
		int cnt = 0;
		for(int i = 1; i <= n; i++) cnt += (s[i] != t[i]);
		f[n] = 1;
		for(int i = n - 1; i >= 1; i--) f[i] = (n * inv(i) % MOD + (n - i) * inv(i) % MOD * f[i + 1] % MOD) % MOD;
		LL ans = 0;
		for(int i = 1; i <= cnt; i++) (ans += f[i]) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
}