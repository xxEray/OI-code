#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 998244353;

int n, m;

struct DSU {
    int fa[N];
    void init() { for(int i = 1; i <= n; i++) fa[i] = i; }
    int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }
    int count() {
        int ret = 0;
        for(int i = 1; i <= n; i++) ret += (find(i) == i);
        return ret;
    }
    int sz[N];
    void get_size() {
        for(int i = 1; i <= n; i++) sz[i] = 0;
        for(int i = 1; i <= n; i++) sz[find(i)]++;
    }
} dsu1, dsu2;

LL fac(int x) {
    LL ret = 1;
    for(int i = 1; i <= x; i++) (ret *= i) %= MOD;
    return ret;
}

int main() {
#ifndef DEBUG
    freopen("passageway.in", "r", stdin);
    freopen("passageway.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    dsu1.init(), dsu2.init();
    for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); dsu1.merge(u, v); }
    for(int i = 1; i <= n - m - 1; i++) { int u, v; scanf("%d%d", &u, &v); dsu2.merge(u, v); }
    dsu1.get_size(), dsu2.get_size();
    // printf("dsu1.sz: "); for(int i = 1; i <= n; i++) if(dsu1.sz[i]) printf("%d ", dsu1.sz[i]); puts("");
    // printf("dsu2.sz: "); for(int i = 1; i <= n; i++) if(dsu2.sz[i]) printf("%d ", dsu2.sz[i]); puts("");
    int sum1 = 0, sum2 = 0;
    for(int i = 1; i <= n; i++) if(dsu1.sz[i]) sum1 += dsu1.sz[i] - 1;
    for(int i = 1; i <= n; i++) if(dsu2.sz[i]) sum2 += dsu2.sz[i] - 1;
    // printf("sum1 = %d, sum2 = %d\n", sum1, sum2);
    LL ans = fac(sum1) * fac(sum2) % MOD;
    // printf("ans = %lld\n", ans);
    for(int i = 1; i <= n; i++) if(dsu1.sz[i]) (ans *= dsu1.sz[i]) %= MOD;
    for(int i = 1; i <= n; i++) if(dsu2.sz[i]) (ans *= dsu2.sz[i]) %= MOD;
    printf("%lld\n", ans);
    return 0;
}