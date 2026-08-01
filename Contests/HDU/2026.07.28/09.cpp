#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

const LL MOD = 998244353;
const LL inv2 = (MOD + 1) / 2;

int n;
std::vector<int> to[N];

int d[N];

bool ontree[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) to[i].clear(), ontree[i] = true, d[i] = 0;
		int cnt = 0;
		for(int i = 1; i <= n; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			if(u == v) cnt++, ontree[u] = false;
			else to[u].emplace_back(v), to[v].emplace_back(u), d[u]++, d[v]++;
		}
		std::vector<int> stk;
		for(int i = 1; i <= n; i++) if(d[i] == 1) stk.emplace_back(i), ontree[i] = false;
		while(!stk.empty()) {
			cnt++;
			int u = stk.back();
			stk.pop_back();
			for(int v : to[u]) if(ontree[v]) {
				d[v]--;
				if(d[v] == 1) {
					ontree[v] = false;
					stk.emplace_back(v);
				}
			}
		}
		// printf("cnt = %d\n", cnt);
		printf("%lld\n", (cnt + (n - cnt) * inv2) % MOD);
	}
	return 0;
}