#include <bits/stdc++.h>

typedef long long LL;

const int N = 100 + 5;
const LL MOD = 1e9 + 7;

int n, m;
LL color;
int K, U;

struct Edge { int v; LL w[2]; }; // 0 - diff, 1 - same
std::vector<Edge> to[N];

std::vector<std::array<int, 13>> bell[15];

void get_bell(std::array<int, 13> v, int msk, int id) {
	if(msk == U) { bell[K].push_back(v); return; }
	if(msk >> (id - 1) & 1) { get_bell(v, msk, id + 1); return; }
	int all = ~(msk | (1 << (id - 1))) & U;
	for(int s = all; ; s = (s - 1) & all) {
		for(int i = 1; i <= K; i++) if(i == id || (s >> (i - 1) & 1)) v[i] = id;
		get_bell(v, msk | s | (1 << (id - 1)), id + 1);
		if(!s) break;
	}
}

int main() {
	int T; scanf("%d", &T);
	for(K = 0; K <= 12; K++) {
		U = (1 << K) - 1;
		get_bell(std::array<int, 13>(), 0, 1);
	}
	while(T--) {
		scanf("%d%d%lld", &n, &m, &color);
		for(int i = 1; i <= n; i++) to[i].clear();
		for(int i = 1; i <= m; i++) {
			int u, v; LL w0, w1;
			scanf("%d%d%lld%lld", &u, &v, &w0, &w1);
			to[u].push_back({v, w0, w1}), to[v].push_back({u, w0, w1});
		}
		if(n <= 12) {
			K = n;
			LL ans = 0;
			for(auto &c : bell[K]) {
				int cnt = 0;
				for(int i = 1; i <= n; i++) cnt += c[i] == i;
				LL ret = 1;
				for(LL i = color - cnt + 1; i <= color; i++) (ret *= i) %= MOD;
				for(int u = 1; u <= n; u++) for(auto &e : to[u]) if(u <= e.v) (ret *= e.w[c[u] == c[e.v]]) %= MOD;
				ans += ret;
			}
			printf("%lld\n", ans % MOD);
		} else {
			K = m - (n - 1);
		}
	}
	return 0;
}
