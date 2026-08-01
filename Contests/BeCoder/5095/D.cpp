#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int M = 4e5 + 5;
const LL MOD = 1e9 + 7;

int n, m;
struct Edge { int to, nxt; } edge[M << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int a[N];

int color[N];
bool bipartite, same;
int cnt[2][2];
void dfs(int u) {
	cnt[color[u]][a[u]]++;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(a[u] == a[v]) same = true;
		if(color[v] == -1) color[v] = color[u] ^ 1, dfs(v);
		else if(color[v] != (color[u] ^ 1)) bipartite = false;
	}
}

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int main() {
	scanf("%d%d", &n, &m);
	get_factorial(n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) color[i] = -1;
	LL ans = 1;
	bool has_same = false;
	for(int i = 1; i <= n; i++) if(color[i] == -1) {
		same = false, bipartite = true, cnt[0][0] = cnt[0][1] = cnt[1][0] = cnt[1][1] = 0;
		color[i] = 0, dfs(i);
		if(same) {
			if(bipartite) {
				LL sum = 0;
				for(int j = 0; j <= cnt[0][0] + cnt[0][1]; j++) {
					int k = j - cnt[0][0] + cnt[1][0];
					if(k < 0 || k > cnt[1][0] + cnt[1][1]) continue;
					(sum += C(cnt[0][0] + cnt[0][1], j) * C(cnt[1][0] + cnt[1][1], k)) %= MOD;
				}
				(ans *= sum) %= MOD;
			} else {
				LL sum = 0;
				for(int j = 0; j <= cnt[0][0] + cnt[0][1] + cnt[1][0] + cnt[1][1]; j++)
					if((j & 1) == ((cnt[0][0] + cnt[1][0]) & 1)) {
						(sum += C(cnt[0][0] + cnt[0][1] + cnt[1][0] + cnt[1][1], j)) %= MOD;
					}
				(ans *= sum) %= MOD;
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}