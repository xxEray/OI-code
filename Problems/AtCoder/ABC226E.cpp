#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int e[N][2];

int fa[N], size[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? (fa[x] = y, size[y] += size[x], size[x] = 0) : 0; }

LL qpow(LL a, LL b) { LL ret = 1; while(true) { if(b & 1) ret = ret * a % MOD; if(!(b >>= 1)) return ret; a = a * a % MOD; } }

int cnt[N];

int main() {
  	int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) fa[i] = i, size[i] = 1;
  	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); merge(u, v); e[i][0] = u, e[i][1] = v; }
	for(int i = 1; i <= m; i++) cnt[find(e[i][0])]++;
	int tot = 0;
	for(int i = 1; i <= n; i++) if(fa[i] == i && size[i] != cnt[i]) { puts("0"); return 0; }
	for(int i = 1; i <= n; i++) tot += (fa[i] == i);
    printf("%lld\n", qpow(2, tot));
    return 0;
}