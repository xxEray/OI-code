#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 100 + 5;
const LL MOD = 1e9 + 7;
const LL INF = 0x3f3f3f3f;

LL a[N];
struct DP { LL f, g; };
int n;

LL qpow(LL a, LL b) { LL ret = 1; for(; b; b >>= 1) { if(b & 1) ret = ret * a % MOD; a = a * a % MOD; } return ret; }

DP dfs(int l, int r) {
	// if(l > r) return {0, 0};
	LL h = INF, w = 0;
	// w is wrong! is vec.size()
	for(int i = l; i <= r; i++) h = std::min(h, a[i]);
	for(int i = l; i <= r; i++) a[i] -= h, w += (a[i] == 0);
	// printf("dfs %d %d, h = %lld, w = %lld\n", l, r, h, w);
	LL f = qpow(2, h), g1 = qpow(2, w), g2 = (qpow(2, h) + MOD - 2) % MOD;
	for(int i = l, last = l; i <= r + 1; i++)
		if(a[i] == 0 || i == r + 1) {
			if(last > i - 1) { last = i + 1; continue; }
			DP ret = dfs(last, i - 1);
			(f *= ret.f) %= MOD;
			(g1 *= (ret.g + ret.f) % MOD) %= MOD;
			(g2 *= ret.f) %= MOD;
			last = i + 1;
		}
	// printf("dfs %d %d, h = %lld, w = %lld, ans = (%lld, %lld, %lld)\n", l, r, h, w, f, g1, g2);
	return {f, (g1 + g2) % MOD};
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	printf("%lld\n", dfs(1, n).g);
	return 0;
}