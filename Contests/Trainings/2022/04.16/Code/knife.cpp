#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 1e5 + 10;
const int M = 1e5 + 10;
const LL MOD = 1e9 + 7;

struct Edge { int to, nxt; } edge[M << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int n, m, K, R;

bool vis[N];
int fa[N];
void get_fa(int u) {
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		fa[v] = u;
		get_fa(v);
	}
}

bool special[N];
int hash[N];
std::vector<int> specials;
int color[N];
LL f[N][10], weight[10];
LL fac[N], invfac[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL A(LL x, LL y) { return fac[x] * invfac[x - y] % MOD; }

int coe(int k1, int k2) { return k1 == k2 ? (weight[k2] - 1) * inv(weight[k2]) % MOD : weight[k1] * weight[k2] % MOD; }
void dfs(int u) {
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		dfs(v);
		for(int k1 = 0; k1 <= R; k1++) if(!special[u] || color[u] == k1) {
			LL sum = 0;
			for(int k2 = 0; k2 <= R; k2++) if(!special[v] || color[v] == k2) {
				(sum += f[v][k2] * (k1 != k2)) %= MOD;
			}
			(f[u][k1] *= sum) %= MOD;
		}
	}
}

bool ok[10][10];
LL ans = 0;
void solve(int addition) {
	bool flag = true;
	for(int i = 1; i <= n; i++) if(special[i])
		for(int j = head[i]; j; j = edge[j].nxt) if(special[edge[j].to])
			flag &= (color[i] != color[edge[j].to]);
	for(int k = 0; k <= R; k++) f[0][k] = weight[k];
	if(flag) {
		for(int i = 1; i <= n; i++) vis[i] = false;
		for(int i = 1; i <= n; i++) for(int k = 0; k <= R; k++) if(!special[i] || color[i] == k) f[i][k] = weight[k];
		dfs(1);
		LL ret = 0;
		for(int k = 0; k <= R; k++) (ret += f[1][k]) %= MOD;
		(ans += ret * A(K, addition)) %= MOD;
	}
}
void get_color(int now, int types) {
	if(now == R + 1) { solve(types); return; }
	bool tmp[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	for(int j = 1; j < now; j++) if(ok[j][now]) tmp[color[specials[j - 1]]] = false;
	for(int k = 1; k <= types + 1; k++) if(tmp[k]) {
		color[specials[now - 1]] = k, get_color(now + 1, std::max(k, types));
	}
}

int main() {
// #ifndef DEBUG
	freopen("knife.in", "r", stdin);
	freopen("knife.out", "w", stdout);
// #endif
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	get_fa(1);
	for(int i = 1; i <= n; i++) for(int j = head[i]; j; j = edge[j].nxt)
		if(fa[i] != edge[j].to && fa[edge[j].to] != i) special[i] = special[edge[j].to] = true;
	for(int i = 1; i <= n; i++) R += special[i];
	for(int i = 1; i <= n; i++) if(special[i]) specials.push_back(i), hash[i] = specials.size();
	for(int i = 1; i <= n; i++) for(int j = head[i]; j; j = edge[j].nxt)
		if(special[i] && special[edge[j].to]) ok[hash[i]][hash[edge[j].to]] = ok[hash[edge[j].to]][hash[i]] = true;
	weight[0] = K - R;
	for(int i = 1; i <= R; i++) weight[i] = 1;
	fac[0] = 1;
	for(int i = 1; i <= K; i++) fac[i] = (fac[i - 1] * i) % MOD;
	invfac[K] = inv(fac[K]);
	for(int i = K; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
	get_color(1, 0);
	printf("%lld\n", ans);
	return 0;
} /*
3 3 4
1 2
2 3
1 3
*/