#include <cstdio>
#include <algorithm>
#include <cassert>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 998244353;
const int INF = 0x3f3f3f3f;

struct Monster { int a, b; } a[N];
struct Skill { int x, l, r; } b[N];
int n, m;

int mnl[N][21], mnr[N][21];
int lg[N];
void preprocess() {
    lg[0] = -1;
    for(int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    for(int i = 1; i <= n; i++) mnl[i][0] = a[i + 1].a - a[i].b;
    for(int i = 1; i <= n; i++) mnr[i][0] = a[i - 1].a - a[i].b;
    mnl[n][0] = mnr[1][0] = INF;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= 20; j++) mnl[i][j] = mnr[i][j] = INF;
    for(int j = 1; j <= 20; j++)
        for(int i = 1; i + (1 << j) - 1 <= n; i++) {
            mnl[i][j] = std::min(mnl[i][j - 1], mnl[i + (1 << (j - 1))][j - 1]);
            mnr[i][j] = std::min(mnr[i][j - 1], mnr[i + (1 << (j - 1))][j - 1]);
        }
}
int calc(int mn[N][21], int l, int r) {
    int k = lg[r - l + 1];
    // printf("calc(%c, %d, %d) = %d\n", mn == mnl ? 'L' : 'R', l, r, std::min(mn[l][k], mn[r - (1 << k) + 1][k]));
    return std::min(mn[l][k], mn[r - (1 << k) + 1][k]);
}

struct Node { int l, r; } c[N];
void get_segments() {
    for(int i = 1; i <= m; i++) {
        int x = b[i].x;
        if(x == 1) c[i].l = 1;
        else {
            int l = 1, r = x;
            while(l < r) {
                int mid = (l + r) >> 1;
                if(calc(mnl, mid, x - 1) >= b[i].l) r = mid;
                else l = mid + 1;
            }
            c[i].l = l;
        }
        if(x == n) c[i].r = n;
        else {
            int l = x + 1, r = n + 1;
            while(l < r) {
                int mid = (l + r) >> 1;
                if(calc(mnr, x + 1, mid) >= b[i].r) l = mid + 1;
                else r = mid;
            }
            c[i].r = l - 1;
        }
    }
    std::sort(c + 1, c + m + 1, [](Node x, Node y) { return x.l < y.l; });
    // for(int i = 1; i <= m; i++) printf("[%d, %d]\n", c[i].l, c[i].r);
}

struct SegmentTree {
    LL t[N << 2], lazy[N << 2];
    void set_lazy(int x, LL v) { (t[x] *= v) %= MOD, (lazy[x] *= v) %= MOD; }
    void lazy_down(int x) {
        assert(lazy[x]);
        set_lazy(x << 1, lazy[x]), set_lazy(x << 1 | 1, lazy[x]);
        lazy[x] = 1;
    }
    void build(int x = 1, int l = 0, int r = n) {
        if(l == r) { t[x] = 0, lazy[x] = 1; return; }
        int mid = (l + r) >> 1;
        build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
        t[x] = 0, lazy[x] = 1;
    }
    LL sum(int ql, int qr, int x = 1, int l = 0, int r = n) {
        // printf("sum(%d, %d, %d, %d, %d)\n", ql, qr, x, l, r);
        if(ql > qr) return 0;
        if(ql <= l && r <= qr) return t[x];
        int mid = (l + r) >> 1;
        lazy_down(x);
        if(qr <= mid) return sum(ql, qr, x << 1, l, mid);
        else if(ql > mid) return sum(ql, qr, x << 1 | 1, mid + 1, r);
        else return (sum(ql, qr, x << 1, l, mid) + sum(ql, qr, x << 1 | 1, mid + 1, r)) % MOD;
    }
    LL get(int qind) { return sum(qind, qind); }
    void plus(int qind, LL qv, int x = 1, int l = 0, int r = n) {
        // printf("plus(%d, %lld, %d, %d, %d)\n", qind, qv, x, l, r);
        if(l == r) { (t[x] += qv) %= MOD; return; }
        int mid = (l + r) >> 1;
        lazy_down(x);
        if(qind <= mid) plus(qind, qv, x << 1, l, mid);
        else plus(qind, qv, x << 1 | 1, mid + 1, r);
        t[x] = (t[x << 1] + t[x << 1 | 1]) % MOD;
    }
    void multiply(int ql, int qr, LL qv, int x = 1, int l = 0, int r = n) {
        // printf("multiply(%d, %d, %lld, %d, %d, %d)\n", ql, qr, qv, x, l, r);
        if(ql > qr) return;
        if(ql <= l && r <= qr) { set_lazy(x, qv); return; }
        int mid = (l + r) >> 1;
        lazy_down(x);
        if(ql <= mid) multiply(ql, qr, qv, x << 1, l, mid);
        if(qr > mid) multiply(ql, qr, qv, x << 1 | 1, mid + 1, r);
        t[x] = (t[x << 1] + t[x << 1 | 1]) % MOD;
    }
} seg;

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].a, &a[i].b);
        for(int i = 1; i <= m; i++) scanf("%d%d%d", &b[i].x, &b[i].l, &b[i].r);
        preprocess();
        get_segments();
        seg.build();
        seg.plus(0, 1);
        for(int i = 1; i <= m; i++) {
            seg.plus(c[i].r, seg.sum(c[i].l - 1, c[i].r));
            seg.multiply(c[i].r + 1, n, 2);
            // printf("%d: ", i);
            // for(int j = 1; j <= n; j++) printf("%lld ", seg.get(j));
            // puts("");
        }
        printf("%lld\n", seg.get(n));
    }
    return 0;
} /*
1
4 3
1 4
2 3
3 2
4 1
1 2 -2
2 2 1
3 1 1
*/