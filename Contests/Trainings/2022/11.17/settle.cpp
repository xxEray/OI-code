#include <bits/stdc++.h>

typedef long long LL;

const int N = 100 + 5;
const int MAXS = (1 << 12) + 1;
const LL MOD = 1e9 + 7;

int n, m;
LL color;
int K, U;

struct Edge { int v; LL w[2]; }; // 0 - diff, 1 - same
std::vector<Edge> to[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

namespace Solve_n12 {
	LL ans;
	LL A[20], fix[MAXS], prod_all;
	void dfs(int msk, int id, int cnt, LL ret) {
		if(msk == U) { (ans += ret * A[cnt] % MOD * prod_all % MOD) %= MOD; return; }
		if(msk >> (id - 1) & 1) { dfs(msk, id + 1, cnt, ret); return; }
		int all = ~(msk | (1 << (id - 1))) & U;
		for(int s = all; ; s = (s - 1) & all) {
			int t = s | (1 << (id - 1));
			dfs(msk | t, id + 1, cnt + 1, ret * fix[t] % MOD);
			if(!s) break;
		}
	}
	void init() {}
	void main() {
		K = n, U = (1 << K) - 1;
		A[0] = 1;
		for(int i = 1; i <= K; i++) A[i] = A[i - 1] * (color - i + 1) % MOD;
		prod_all = 1;
		for(int u = 1; u <= n; u++) for(auto &p : to[u]) if(u < p.v) (prod_all *= p.w[0]) %= MOD;
		for(int s = 0; s <= U; s++) {
			fix[s] = 1;
			for(int u = 1; u <= n; u++) if(s >> (u - 1) & 1)
				for(auto &p : to[u]) if(u < p.v && (s >> (p.v - 1) & 1))
					(fix[s] *= inv(p.w[0]) * p.w[1] % MOD) %= MOD;
		}
		ans = 0;
		dfs(0, 1, 0, 1);
		printf("%lld\n", ans);
	}
}

namespace Solve_extra9 {
	std::vector<std::array<int, 13>> bell;
	std::array<int, 13> arr;
	void get_bell(std::array<int, 13> v, int msk, int id) {
		if(msk == U) { bell.push_back(v); return; }
		if(msk >> (id - 1) & 1) { get_bell(v, msk, id + 1); return; }
		int all = ~(msk | (1 << (id - 1))) & U;
		for(int s = all; ; s = (s - 1) & all) {
			for(int i = 1; i <= K; i++) if(i == id || (s >> (i - 1) & 1)) v[i] = id;
			get_bell(v, msk | s | (1 << (id - 1)), id + 1);
			if(!s) break;
		}
	}
	int vis[N], id[N];
	std::vector<Edge> back[N];
	void dfs(int u, int fa) {
		vis[u] = 1;
		for(auto &e : to[u])
			if(vis[e.v] == 1) { if(!id[e.v]) id[e.v] = ++K; back[u].push_back({e.v, e.w[0], e.w[1]}); }
			else if(vis[e.v] == 0) {
				for(int i = 0; ; i++) if(to[e.v][i].w[0] == e.w[0] && to[e.v][i].w[1] == e.w[1]) {
					to[e.v].erase(to[e.v].begin() + i);
					break;
				}
				dfs(e.v, u);
			}
		vis[u] = 2;
	}
	LL f[N][20];
	int cnt[N];
	void dp(int u, int fa) {
		vis[u] = 1;
		for(int i = 0; i <= K; i++) f[u][i] = 1;
		for(auto &e : to[u]) if(!vis[e.v]) {
			dp(e.v, u);
			for(int i = 1; i <= K; i++) for(int j = 0; j <= K; j++) (f[u][i] += f[e.v][j] * e.w[i == j] % MOD) %= MOD;
			for(int j = 1; j <= K; j++) (f[u][0] *= f[e.v][j] * e.w[0] % MOD % MOD) %= MOD;
			(f[u][0] *= f[e.v][0] * e.w[1] % MOD + f[e.v][0] * e.w[0] % MOD * (color - K - 1) % MOD) %= MOD;
			for(int i = 0; i <= K; i++) for(auto &ef : back[u]) (f[u][i] *= ef.w[arr[ef.v] == i]) %= MOD;
		}
		if(id[u]) for(int i = 0; i <= K; i++) if(i != arr[id[u]]) f[u][i] = 0;
	}
	void init() {}
	void main() {
		for(int i = 1; i <= n; i++) vis[i] = id[i] = 0, back[i].clear();
		dfs(1, 0);
		printf("K = %d\n", K);
		U = (1 << K) - 1;
		bell.clear();
		get_bell(std::array<int, 13>(), 0, 1);
		LL ans = 0;
		for(auto it = bell.begin(); it != bell.end(); it++) {
			arr = *it;
			for(int i = 1; i <= n; i++) vis[i] = 0;
			dp(1, 0);
			for(int i = 1; i <= K; i++) (ans += f[1][i]) %= MOD;
		}
		printf("%lld\n", ans);
	}
}

int main() {
	Solve_n12::init(), Solve_extra9::init();
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%lld", &n, &m, &color);
		for(int i = 1; i <= n; i++) to[i].clear();
		for(int i = 1; i <= m; i++) {
			int u, v; LL w0, w1;
			scanf("%d%d%lld%lld", &u, &v, &w0, &w1);
			assert(u != v);
			to[u].push_back({v, w0, w1}), to[v].push_back({u, w0, w1});
		}
		/* if(n <= 12) Solve_n12::main();
		else  */Solve_extra9::main();
	}
	return 0;
} /*
1
2 2 3
2 1 1 1
2 1 2 2
*/