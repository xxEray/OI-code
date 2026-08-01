#include <cstdio>
#include <algorithm>
#include <cstring>

int rd(){char s=getchar();int v=0;while(s<'0'||s>'9')s=getchar();while(s>='0'&&s<='9')v=v*10+s-'0',s=getchar();return v;}

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 998244353;

int n;
int a[N];

LL mod(const LL &x) { return x >= MOD ? x - MOD : x; }

struct BIT {
	LL t[N];
	void add(int x, LL v) { while(x <= n) t[x] = mod(t[x] + v), x += x & -x; }
	LL query(int r) { LL ret = 0; while(r) ret = mod(ret + t[r]), r -= r & -r; return ret; }
	LL query(int l, int r) { return l > r ? 0 : mod(query(r) - (l > 1 ? query(l - 1) : 0) + MOD); }
	void clear() { memset(t, 0, sizeof(t)); }
} bit;

LL f[N], g[N];

int main() {
#ifndef DEBUG
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	int T = rd();
	while(T--) {
		memset(f, 0, sizeof(f)), memset(g, 0, sizeof(g));
		n = rd();
		for(int i = 1; i <= n; i++) a[rd()] = i;
		bit.clear();
		for(int i = 1; i <= n; i++) f[i] = mod(bit.query(a[i] + 1, n) + 1), bit.add(a[i], f[i]);
		bit.clear();
		for(int i = n; i >= 1; i--) g[i] = mod(bit.query(a[i] + 1, n) + 1), bit.add(a[i], g[i]);
		LL ans = 0;
		for(int i = 1; i <= n; i++) ans = mod(ans + f[i] * g[i] % MOD);
		printf("%lld\n", ans);
	}
	return 0;
}