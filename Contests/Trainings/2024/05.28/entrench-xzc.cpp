#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5;
int n, q, tp, fa[N], l, r, b[N], ch[N][2], rt, op, x, y, ans;
bool get(int x) {return x == ch[fa[x]][1];}
struct LCT 
{
    #define ls ch[x][0]
    #define rs ch[x][1]
    int ch[N][2], fa[N], s[N][2];
    bool chk(int x) {return x == ch[fa[x]][1];}
    bool isroot(int x) {return x != ch[fa[x]][0] && x != ch[fa[x]][1];}
    void push_up(int x) 
    {
        s[x][0] = s[ls][0] + s[rs][0] + (get(x) == 0);
        s[x][1] = s[ls][1] + s[rs][1] + (get(x) == 1);
    }
    void rotate(int x) 
    {
        int y = fa[x], z = fa[y], c = chk(x), k = ch[x][!c];
        ch[y][c] = k; ch[x][!c] = y;
        if(k) fa[k] = y;
        if(!isroot(y)) ch[z][chk(y)] = x;
        fa[y] = x, fa[x] = z, push_up(y), push_up(x);
    }
    void splay(int x) 
    {
        for(int y = fa[x]; y = fa[x], !isroot(x); rotate(x))
            if(!isroot(y)) rotate(chk(x) == chk(y) ? y : x); 
    }
    int access(int x) 
    {
        int y = 0;
        for(; x; y = x, x = fa[x])
        {
            splay(x); ch[x][1] = y;
            push_up(x);
        }
        return y;
    }
    void link(int x, int y) {splay(x); push_up(x); fa[x] = y;}
    void cut(int x, int y) 
    {
        access(x); splay(y); assert(ch[y][1] == x);
        fa[x] = ch[y][1] = 0, push_up(y);
    }   
    int ask(int l, int r) 
    {
        if(l == 1 && r == n) return 1;
        if(l == 1) return s[access(b[r + 1])][1];
        if(r == n) return s[access(b[l - 1])][0] - 1;
        int x = b[l - 1], y = b[r + 1], z = 0;
        z += s[access(x)][0]; z += s[x = access(y)][1]; z -= (s[ls][0] + s[ls][1] + 3);
        return z;
    }   
    #undef ls 
    #undef rs
}t;
void rotate(int x) 
{
    if(x == rt) return;
    int y = fa[x], z = fa[y], c = get(x), k = ch[x][!c];
    ch[y][c] = k; ch[x][!c] = y;
    if(k) t.cut(k, fa[k]), fa[k] = y, t.link(k, fa[k]);
    if(z) ch[z][get(y)] = x, t.cut(y, fa[y]);
    else rt = x;
    t.cut(x, fa[x]); fa[y] = x, t.link(y, fa[y]); 
    fa[x] = z; t.link(x, fa[x]); 
}
int main()
{
    scanf("%d%d%d", &n, &q, &tp);
    for(int i = 1; i < (n << 1); i++) 
    {
        scanf("%d%d%d%d", &l, &r, &ch[i][0], &ch[i][1]);
        if(ch[i][0]) fa[ch[i][0]] = i;
        if(ch[i][1]) fa[ch[i][1]] = i;
        if(l == r) b[l] = i;
    }
    for(int i = 1; i < (n << 1); i++) 
    {
        if(!fa[i]) rt = i;
        t.link(i, fa[i]); 
    }
    for(int i = 1; i <= q; i++)
    {
        scanf("%d%d", &op, &x);
        if(op == 1) 
        {
            x = (x + ans * tp) % (n - 1) + 1;
            rotate(x);
        }
        if(op == 2) 
        {
            scanf("%d", &y); x = (x + ans * tp) % n + 1, y = (y + ans * tp) % n + 1;
            if(x > y) swap(x, y);
            printf("%d\n", ans = t.ask(x, y));
        }
    }

    return 0;
}