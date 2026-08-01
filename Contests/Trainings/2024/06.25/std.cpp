#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128_t lll;
typedef double db;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
#define fir first
#define sec second
typedef vector <int> vi;
typedef vector <ll> vl;

#ifdef LCX
#define msg(args...) fprintf(stderr, args)
#else
#define msg(...) void()
#endif

namespace IO {
const int STACKSIZE = 100, BUFSIZE = 1 << 17;
char ibuf[BUFSIZE], *p1, *p2;
inline char getchar() {
    if (p1 == p2) p2 = (p1 = ibuf) + fread(ibuf, 1, BUFSIZE, stdin);
    return p1 == p2 ? EOF : *p1++;
}

char obuf[BUFSIZE], *pp = obuf;
void flush() { fwrite(obuf, 1, pp - obuf, stdout), pp = obuf; }
inline void putchar(char ch) {
    if (pp == obuf + BUFSIZE) flush();
    *pp++ = ch;
}
struct IO { ~IO () { flush(); } } io;

char stk[STACKSIZE]; int tp;
template <typename __Tp> void read(__Tp &x) {
    int f = 0; x = 0; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    if (f) x = -x;
}
void read(char s[]) {
    char ch = getchar();
    while (ch != EOF && isspace(ch)) ch = getchar();
    while (ch != EOF && !isspace(ch)) *s++ = ch, ch = getchar();
    *s = 0;
}
template <typename __Tp1, typename ...__Tp2>
void read(__Tp1 &x, __Tp2 &...y) { read(x), read(y...); }
void write(char ch) { putchar(ch); }
void write(char s[]) { while (*s) putchar(*s++); }
void write(const char s[]) { while (*s) putchar(*s++); }
template <typename __Tp> void write(__Tp x) {
    if (x < 0) putchar('-'), x = -x;
    stk[tp = 1] = x % 10 + 48;
    while (x > 9) x /= 10, stk[++tp] = x % 10 + 48;
    while (tp) putchar(stk[tp]), tp--;
}
template <typename __Tp1, typename ...__Tp2>
void write(__Tp1 x, __Tp2 ...y) { write(x), write(y...); }
}
using IO::read;
using IO::write;

const int maxn = 2e5 + 10, mod = 998244353;
#define check(x) assert(0 <= (x) && (x) < mod)
int& Dec(int &x, int y) { return x -= y, x < 0 ? x += mod : x; }
int& Inc(int &x, int y) { return Dec(x, mod - y); }
int Diff(int x, int y) { return Dec(x, y); }
int Sum(int x, int y) { return Inc(x, y); }
ll C2(int n) { return (ll) n * (n - 1) / 2; }
int n, m, q;
vi vec[maxn];
struct SegTree {
    int cnt[maxn << 2][2], rev[maxn << 2];
    #define ls (rt << 1)
    #define rs (rt << 1 | 1)
    #define mid ((l + r) >> 1)
    void push_up(int rt) {
        cnt[rt][0] = cnt[ls][0] + cnt[rs][0];
        cnt[rt][1] = cnt[ls][1] + cnt[rs][1];
    }
    void tag(int rt) { rev[rt] ^= 1, swap(cnt[rt][0], cnt[rt][1]); }
    void push_down(int rt) { if (rev[rt]) tag(ls), tag(rs), rev[rt] = 0; }
    void build(int rt, int l, int r) {
        rev[rt] = 0, cnt[rt][0] = r - l + 1, cnt[rt][1] = 0;
        if (l == r) return;
        build(ls, l, mid), build(rs, mid + 1, r);
    }
    void update(int rt, int l, int r, int L, int R) {
        if (L > r || R < l || L > R) return;
        if (L <= l && r <= R) return tag(rt);
        push_down(rt);
        update(ls, l, mid, L, R);
        update(rs, mid + 1, r, L, R);
        push_up(rt);
    }
    int query(int rt, int l, int r, int L, int R) {
        if (L > r || R < l || L > R) return 0;
        if (L <= l && r <= R) return cnt[rt][1];
        push_down(rt);
        return query(ls, l, mid, L, R) + query(rs, mid + 1, r, L, R);
    }
    #undef ls
    #undef rs
    #undef mid
} tr;

int bias;
struct SegTree2 {
    struct node {
        int c, h, a, b;
        friend node operator + (const node &p, const node &q) {
            node ret;
            ret.c = Sum(p.c, q.c);
            ret.h = Sum(p.h, q.h);
            ret.a = Sum(Sum(p.a, q.a), (ll) p.c * q.c % mod);
            ret.b = Sum(Sum(p.b, q.b), (ll) p.h * q.c % mod);
            return ret;
        }
    } t[maxn << 2];
    node get(int h, int c) {
        h = (h % mod + mod) % mod;
        node p;
        p.c = c;
        p.h = (ll) h * c % mod;
        int cnt = C2(c + 1) % mod;
        p.a = cnt;
        p.b = (ll) h * cnt % mod;
        return p;
    }
    #define ls (rt << 1)
    #define rs (rt << 1 | 1)
    #define mid ((l + r) >> 1)
    void push_up(int rt) { t[rt] = t[rs] + t[ls]; }
    void update(int rt, int l, int r, int pos, int val) {
        if (l == r) {
            int h = l - n, c = t[rt].c + val;
            t[rt] = get(h, c);
            return;
        }
        if (pos <= mid) update(ls, l, mid, pos, val);
        else update(rs, mid + 1, r, pos, val);
        push_up(rt);
    }
    void add(int h, int v) { update(1, 1, n, h + n, v); }
    int query() {
        node p = t[1] + get(0 - bias, m - t[1].c);
        return Sum((ll) p.a * bias % mod, p.b);
    }
    #undef ls
    #undef rs
    #undef mid
} tr2;

struct seg {
    int l, r, h;
    bool operator < (const seg &p) const {
        if (l != p.l) return l < p.l;
        return r < p.r;
    }
};
set <seg> s;
void update(int L, int R) {
    auto lt = prev(s.upper_bound({L, m + 1, 0}));
    auto rt = s.upper_bound({R, m + 1, 0});
    while (lt != rt) {
        auto it = lt++;
        seg p = *it; s.erase(it);
        int l = max(L, p.l), r = min(R, p.r);
        tr2.add(p.h, -tr.query(1, 1, m, l, r));
        if (p.l < L) s.insert({p.l, L - 1, p.h});
        if (p.r > R) s.insert({R + 1, p.r, p.h});
    }
    tr.update(1, 1, m, L, R);
    s.insert({L, R, 0 - bias});
    tr2.add(0 - bias, tr.query(1, 1, m, L, R));
}

void init() {
    tr.build(1, 1, m);
    s.insert({1, m, 0});
}

int main() {
    clock_t t1 = clock();
    // freopen("gothic.in", "r", stdin);
    // freopen("gothic.out", "w", stdout);
    read(n, m, q);
    for (int i = 1; i <= q; ++i) {
        int xl, xr, yl, yr;
        read(xl, xr, yl, yr);
        vec[xl].push_back(yl);
        vec[xl].push_back(yr + 1);
        vec[xr + 1].push_back(yl);
        vec[xr + 1].push_back(yr + 1);
    }
    init();
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        sort(begin(vec[i]), end(vec[i]));
        for (int j = 0; j < (int) vec[i].size(); j += 2) {
            int l = vec[i][j], r = vec[i][j + 1] - 1;
            if (l <= r) update(l, r);
        }
        bias++;
        ans = Sum(ans, tr2.query());
    }
    write(ans, '\n');
    clock_t t2 = clock();
    msg("%lfs\n", (db) (t2 - t1) / CLOCKS_PER_SEC);
    return 0;
}