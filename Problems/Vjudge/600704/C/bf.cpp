#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
struct Node
{
    long long u, v, w;
    bool operator < (const Node &tp) const
    {
        return w < tp.w;
    }
}Edge[400040];
long long T, n, m, k, Time, q, c[400040], a[400040], fa[400040][20], dep[400040], dfn[400040], siz[400040], sta[400040], top, tree[400040], val[400040];
bool vis1, vis2;
vector<long long> h[400040], to[400040], G[400040];
long long Find(long long x)
{
    return fa[x][0] == x ? x : fa[x][0] = Find(fa[x][0]);
}
void init(long long x, long long Fa)
{
    dep[x] = dep[Fa] + 1;
    fa[x][0] = Fa;
    siz[x] = 1;
    dfn[x] = ++Time;
    for(long long i = 1; (1 << i) < dep[x]; ++i)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for(long long v : to[x])
    {
        init(v, x);
        siz[x] += siz[v];
    }
} 
long long LCA(long long x, long long y)//LCA板子
{
    if(dep[x] < dep[y])
        swap(x, y);
    for(long long i = 18; i >= 0; --i)
        if(dep[fa[x][i]] >= dep[y])
            x = fa[x][i];
    if(x == y)
        return x;
    for(long long i = 18; i >= 0; --i)
        if(fa[x][i] != fa[y][i])
        {
            x = fa[x][i];
            y = fa[y][i];
        }
    return fa[x][0];
}
bool cmp(long long u, long long v)
{
    return dfn[u] < dfn[v];
}
void add(long long x, long long y)
{
    for(; x; x ^= x & -x)
        tree[x] += y;
}
long long query(long long x)
{
    long long res = 0;
    for(; x <= k; x += x & -x)
        res += tree[x];
    return res;
}
long long dfs(long long x)
{
    if(val[x])
    {
        add(dfn[x], vis1 ? -val[x] : val[x]);
        return val[x];
    }
    long long maxn = 0, px = 0, w;
    for(long long y : G[x])
    {
        w = dfs(y);
        if(w > maxn)
        {
            px = maxn;
            maxn = w;
        }
        else px = w;
    }
    add(dfn[x], vis1 ? px : -px);
    if(!vis2)
        G[x].clear();
    return maxn;
}
void PUSH(long long col)
{
    if(!h[col].size())
        return;
    top = 0;
    for(long long u : h[col])
    {
        if(!top)
        {
            sta[++top] = u;
            continue;
        }
        long long lca = LCA(sta[top], u);
        while(top > 1 && dep[sta[top - 1]] >= dep[lca])
        {
            G[sta[top - 1]].push_back(sta[top]);
            top--;
        }
        if(sta[top] != lca)
        {
            G[lca].push_back(sta[top]);
            sta[top] = lca;
        }
        sta[++top] = u;
    }
    for(long long i = 1; i < top; ++i)
        G[sta[i]].push_back(sta[i + 1]);
}
long long jump(long long u, long long w)
{
    for(long long i = 18; i >= 0; --i)
        if(a[fa[u][i]] <= w)
            u = fa[u][i];
    return u;
}
int main()
{
    scanf("%lld", &T);
    while(T--)
    {
        scanf("%lld %lld %lld", &n, &m, &q);
        Time = 0;
        k = n;
        memset(tree, 0, sizeof(tree));
        for(long long i = 1; i <= (n << 1); ++i)
        {
            h[i].clear();
            to[i].clear();
            memset(fa[i], 0, sizeof(fa[i]));
        }
        for(long long i = 1; i <= n; ++i)
        {
            scanf("%lld", &c[i]);
            h[c[i]].push_back(i);
        }
        for(long long i = 1; i <= n; ++i)
        {
            scanf("%lld", &val[i]);
            fa[i][0] = i;
        }
        for(long long i = 1; i <= m; ++i)
            scanf("%lld %lld %lld", &Edge[i].u, &Edge[i].v, &Edge[i].w);
        sort(Edge + 1, Edge + 1 + m);
        for(long long i = 1, u, v; i <= m; ++i)
        {
            u = Find(Edge[i].u);
            v = Find(Edge[i].v);
            if(u == v)
                continue;
            a[++k] = Edge[i].w;
            fa[u][0] = fa[v][0] = fa[k][0] = k;
            to[k].push_back(u);
            to[k].push_back(v);
        }
        init(k, 0);
        a[0] = 2e9;
        for(long long i = 1; i <= n; ++i)
            if(h[i].size())
            {
                sort(h[i].begin(), h[i].end(), cmp);
                PUSH(i);
                vis1 = vis2 = false;
                dfs(sta[1]);
            }
        for(long long i = 1, opt, u, w; i <= q; ++i)
        {
            scanf("%lld %lld %lld", &opt, &u, &w);
            if(opt & 1)
            {
                u = jump(u, w);
                printf("%lld\n", query(dfn[u]) - query(dfn[u] + siz[u]));
            }
            else
            {
                PUSH(c[u]);
                vis2 = vis1 = true;
                dfs(sta[1]);
                val[u] += w;
                vis2 = vis1 = false;
                dfs(sta[1]);
            }
        }
    }
    return 0;
}