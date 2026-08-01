#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;
const int MOD = 998244353;

int a[N], b[N];
int n;

int fa[N], size[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? (fa[x] = y, size[y] += size[x], size[x] = 0) : 0; }

int f[N], g[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++) fa[i] = i, size[i] = 1;
	for(int i = 1; i <= n; i++) merge(a[i], b[i]);
	f[1] = 2, f[2] = 3;
	for(int i = 3; i <= n; i++) f[i] = (f[i - 1] + f[i - 2]) % MOD;
	g[1] = 1, g[2] = 3, g[3] = 4;
	for(int i = 4; i <= n; i++) g[i] = (f[i - 1] + f[i - 3]) % MOD;
	long long ans = 1;
	for(int i = 1; i <= n; i++) if(find(i) == i) (ans *= g[size[i]]) %= MOD;
	printf("%lld\n", ans);
	return 0;
}