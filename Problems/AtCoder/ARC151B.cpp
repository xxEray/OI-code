#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int n;
LL m;
int p[N];

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

int main() {
	scanf("%d%lld", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &p[i]);
	for(int i = 1; i <= n; i++) fa[i] = i;
	LL ans = 0;
	int cnt = n;
	for(int i = 1; i <= n; i++)
		if(find(i) != find(p[i])) {
			(ans += (m * (m - 1) / 2) % MOD * qpow(m, cnt - 2) % MOD) %= MOD;
			merge(i, p[i]), cnt--;
		}
	printf("%lld\n", ans);
	return 0;
}