#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int n, m;
LL f[N];

LL triangle(LL x) { return x * (x + 1) / 2; }
void add(LL x) { for(LL i = x; i <= m; i++) (f[i] += f[i - x]) %= MOD; }
void del(LL x) { for(LL i = m; i >= x; i--) (f[i] += MOD - f[i - x]) %= MOD; }
LL query(LL x) { LL ret = 0; for(LL i = x; i >= 0; i -= n) (ret += f[i]) %= MOD; return ret; }

int main() {
	scanf("%d%d", &n, &m);
	f[0] = 1;
	for(int i = 1; i < n; i++) add(triangle(i));
	LL ans = 0;
	for(int i = 1; i <= n; i++) {
		(ans += query(m - triangle(i - 1))) %= MOD;
		del(triangle(n - i)), add(triangle(i));
	}
	printf("%lld\n", ans);
	return 0;
}