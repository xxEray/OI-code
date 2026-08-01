#include <bits/stdc++.h>

using namespace std;

struct xorShift128Plus {
	unsigned long long k1, k2;
	unsigned long long gen() {
		unsigned long long k3 = k1, k4 = k2;
		k1 = k4;
		k3 ^= k3 << 23;
		k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
		return k2 + k4;
	}
	int gen(int w) {
		return gen() % w;
	}
} rnd;

const int N = 5e6 + 5;

int n, a[N];
int ans[N];

bool vis[N];
std::vector<std::pair<int, int>> to[N];
std::vector<int> out, stk;

int main() {
#ifndef DEBUG
	freopen("life.in","r",stdin);
	freopen("life.out","w",stdout);
#endif
	int t;
	scanf("%d%d",&n, &t);
	if(t == 0) for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	else {
		int ra;
		scanf("%d%llu%llu", &ra, &rnd.k1, &rnd.k2);
		for(int i = 1;i <= n; i++) a[i] = rnd.gen(ra) + 1;
	}
	int c = 0;
	for(int i = 1; i < n; i++) c++, to[a[i + 1]].push_back({a[i], c}), to[a[i]].push_back({a[i + 1], c});
	for(int i = 1; i <= n; i++) std::sort(to[i].begin(), to[i].end(), std::greater<>());
	stk.push_back(a[1]);
	while(!stk.empty()) {
		int u = stk.back();
		if(!to[u].empty()) {
			auto [v, id] = to[u].back();
			if(vis[id]) { to[u].pop_back(); continue; }
			vis[id] = true;
			to[u].pop_back();
			stk.push_back(v);
		} else {
			stk.pop_back();
			out.push_back(u);
		}
	}
	assert((int)out.size() == n);
	std::reverse(out.begin(), out.end());
	for(int i = 1; i <= n; i++) ans[i] = out[i - 1];
	if(t == 0) {
		for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
		printf("\n");
	} else {
		int bse = 1919839, p = 1000000007;
		int mul = 1, res = 0;
		for(int i = 1; i <= n; i++, mul = 1ll * mul * bse % p) res = (res + 1ll * ans[i] * mul % p) % p;
		printf("%d\n", res);
	}
	return 0;
}
