#include <cstdio>
#include <algorithm>
#include <vector>
#include <stdio.h>

typedef long long LL;

const int N = 1e5 + 5;

LL a[N], b[N];
LL n, m, p;

std::vector<LL> divisors; // divisors of p

LL qpow(LL x, LL y, LL mod) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }

LL step[N], f[N];

int main() {
	scanf("%lld%lld%lld", &n, &m, &p);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= m; i++) scanf("%lld", &b[i]);
	for(LL i = 1; i * i <= p - 1; i++) if((p - 1) % i == 0) divisors.push_back(i), divisors.push_back((p - 1) / i);
	// for(LL x : divisors) printf("%lld ", x);
	// puts("done");
	std::sort(divisors.begin(), divisors.end());
	LL t = p - 1;
	for(int i = 1; i <= m; i++) t = gcd(t, b[i]);
	for(int i = 1; i <= n; i++)
		for(LL j : divisors)
			if(qpow(a[i], j * t % (p - 1), p) == 1) { step[i] = (p - 1) / j; break; }
	// for(int i = 1; i <= n; i++) printf("%lld ", step[i]);
	// puts("done");
	std::sort(step + 1, step + n + 1);
	LL ans = 0;
	for(int i = n; i >= 1; i--) {
		f[i] = (p - 1) / step[i];
		for(int j = i + 1; j <= n; j++)
			if(step[j] % step[i] == 0) f[i] -= f[j];
		ans += f[i];
	}
	printf("%lld\n", ans);
	return 0;
} /*
5 3 97
90 71 77 92 6
23 34 19
*/