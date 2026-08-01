#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 300 + 5;

int n;
LL m, p;

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

LL qpow(LL x, LL y, LL mod) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }

int g[N][N];

int main() {
#ifndef DEBUG
	freopen("product.in", "r", stdin);
	freopen("product.out", "w", stdout);
#endif
	scanf("%d%lld%lld", &n, &m, &p);
	LL cnt = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) g[i][j] = gcd(i, j);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) for(int k = 1; k <= n; k++) (cnt += (g[i][j] % k == 0) * g[i][j]) %= p - 1;
	printf("%lld\n", qpow(m, cnt, p));
	return 0;
}
