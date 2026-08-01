#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLIM = 314000000;
const LL UNDEF = -10;

struct Rule { LL diamond; std::vector<int> monsters; Rule() : diamond(0) {} };
std::vector<Rule> split[N];
int n, m;

LL mini[N], maxi[N];

void trim(LL &x) { if(x > LLIM) x = LLIM; }

int instk[N];
LL dfs_min(int u) {
	if(mini[u] != UNDEF) return mini[u];
	if(instk[u] >= 2) return -1;
	LL res = UNDEF;
	instk[u]++;
	for(auto ii : split[u]) {
		LL ret = 0;
		for(int v : ii.monsters) {
			LL val = dfs_min(v);
			if(val == -1) ret = -1;
			if(ret != -1) trim(ret += val);
		}
		if(ret != -1) trim(ret += ii.diamond);
		if(res == UNDEF || res == -1) res = ret;
		else if(ret != -1) res = std::min(res, ret);
	}
	instk[u]--;
	return mini[u] = res;
}
LL dfs_max(int u) {
	if(maxi[u] != UNDEF) return maxi[u];
	if(instk[u] >= 2) return mini[u] == -1 ? -1 : -2;
	LL res = UNDEF;
	instk[u]++;
	for(auto ii : split[u]) {
		LL ret = 0;
		for(int v : ii.monsters) {
			LL val = dfs_max(v);
			if(val == -1) ret = -1;
			else if(val == -2) ret = (ret == -1 ? -1 : -2);
			else { if(ret != -1 && ret != -2) trim(ret += val); }
		}
		if(ret != -1 && ret != -2) trim(ret += ii.diamond);
		if(res == UNDEF || res == -1) res = ret;
		else if(ret == -2) res = -2;
		else if(res != -2 && ret != -1) res = std::max(res, ret);
	}
	instk[u]--;
	return maxi[u] = res;
}

int main() {
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= m; i++) {
		int x, y, z; scanf("%d%d", &x, &y);
		split[x].push_back(Rule());
		while(y--) {
			scanf("%d", &z);
			if(z == -1) trim(++split[x].back().diamond);
			else split[x].back().monsters.push_back(z);
		}
	}
	for(int i = 1; i <= n; i++) mini[i] = maxi[i] = UNDEF;
	for(int i = 1; i <= n; i++) if(mini[i] == UNDEF) dfs_min(i);
	for(int i = 1; i <= n; i++) if(maxi[i] == UNDEF) dfs_max(i);
	for(int i = 1; i <= n; i++) printf("%lld %lld\n", mini[i], maxi[i]);
	return 0;
} /*
6 4
1 2 3 -1
1 2 1 -1
2 2 1 -1
2 2 3 -1
3 1 -1
4 2 2 -1
*/