#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 1e9 + 7;

int n, Q;
struct Edge { int to, nxt; LL w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

LL sz[N], f[N][2], g[N][2];
void dfs1(int u, int fa) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
        int v = edge[i].to;
        dfs1(v, u);
        sz[u] += sz[v];
        (f[u][0] += f[v][0] + sz[v]);
        (f[u][1] += f[v][1] + 2 * f[v][0] + edge[i].w * edge[i].w % MOD * sz[v] % MOD) %= MOD;
    }
}
void dfs2(int u, int fa) {
    g[u][0] = (g[fa][0] + f[fa][0] - f[u][0] - sz[u] + (n - sz[u]) + 2 * MOD) % MOD;
    g[u][1] = g[fa][1] +  + (f[fa][1] - f[u][1] - 2 * f[u][0] - sz[u]) + 2 * g[u][0];

}

int main() {
    scanf("%d", &n);
    for(int i = 1; i < n; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
    
    return 0;
}