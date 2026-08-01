#include <bits/stdc++.h>

typedef long long LL;

const int N = 2.5e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, K;
int a[N], b[N];
LL sum[N];

// namespace Solve_Sub5_Q1 {
//     LL f[N];
//     int pl, pr;
//     LL val;
//     std::multiset<int> st0, st1;
//     void add(int i) {
//         int v = b[i];
//         st0.emplace(v), val += v;
//         if((int)st0.size() > K) {
//             val -= *st0.begin();
//             st1.emplace(*st0.begin());
//             st0.erase(st0.begin());
//         }
//     }
//     void del(int i) {
//         int v = b[i];
//         if(st0.find(v) != st0.end()) {
//             val -= v, st0.erase(st0.find(v));
//             if(!st1.empty()) {
//                 val += *st1.rbegin();
//                 st0.emplace(*st1.rbegin());
//                 st1.erase(--st1.end());
//             }
//         } else {
//             assert(st1.find(v) != st1.end());
//             st1.erase(st1.find(v));
//         }
//     }
//     void cdq(int l, int r, int cl, int cr) {
//         int mid = (l + r) >> 1;
//         cdq(l, mid, cl, cr);
//         int ll = cl, rr = std::min(cr, mid - 1);
//         while()
//     }
//     void main() {
//         pl = 1, pr = 0;

//     }
// }

LL *f[N], *g[N];
LL mx[N], val[N];

int main() {
    scanf("%d%d", &n, &K);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum[i] = sum[i - 1] + a[i];
    for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
    if((LL)n * K > 50000000) { /* Solve_Sub5_Q1::main(); */ return 0; }
    for(int i = 1; i <= n; i++) {
        f[i] = new LL[K + 1], g[i] = new LL[K + 1];
        memset(f[i], ~0x3f, sizeof(LL) * (K + 1));
        memset(g[i], ~0x3f, sizeof(LL) * (K + 1));
    }
    for(int i = 1; i <= n; i++) f[i][1] = sum[i - 1] + b[i], g[i][1] = -sum[i] + b[i];
    memset(mx, ~0x3f, sizeof(mx));
    for(int i = 1; i <= n; i++) {
        for(int j = 2; j <= K; j++) f[i][j] = mx[j - 1] + b[i];
        for(int j = 1; j <= K; j++) mx[j] = std::max(mx[j], f[i][j]);
    }
    memset(mx, ~0x3f, sizeof(mx));
    for(int i = n; i >= 1; i--) {
        for(int j = 2; j <= K; j++) g[i][j] = mx[j - 1] + b[i];
        for(int j = 1; j <= K; j++) mx[j] = std::max(mx[j], g[i][j]);
    }
    // for(int i = 1; i <= n; i++) for(int j = 1; j <= K; j++) printf("f[%d][%d] = %lld, g[%d][%d] = %lld\n", i, j, f[i][j], i, j, g[i][j]);
    for(int i = 1; i <= n; i++) {
        val[i] = -LLINF;
        for(int j = 1; j <= K; j++) val[i] = std::max(val[i], f[i][j] + g[i][K + 1 - j] - b[i]);
    }
    LL ans = *std::max_element(val + 1, val + n + 1);
    printf("%lld\n", ans);
    for(int i = 1; i <= n; i++) printf("%d", val[i] == ans);
    puts("");
    return 0;
}