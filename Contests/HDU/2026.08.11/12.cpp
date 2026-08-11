// auto input
#include <bits/stdc++.h>
using std::cin;
using std::cout;

template<typename T> using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
typedef long long LL;

const int N = 1e6 + 5;

int n;
int fa[N];
std::vector<int> son[N];

int sz[N];
int dfs1(int u) {
	sz[u] = 1;
	min_heap<int> hp;
	for(int v : son[u]) hp.emplace(dfs1(v)), sz[u] += sz[v];
	while(hp.size() > 2) {
		hp.pop();
		int y = hp.top(); hp.pop();
		hp.emplace(y + 1);
	}
	// return max{hp} | 0 if empty
	if(hp.empty()) return 0;
	else if(hp.size() == 1) return hp.top() + 1;
	else {
		hp.pop();
		return hp.top() + 1;
	}
}

LL dfs2(int u) {
	LL ret = 0;
	min_heap<int> hp;
	for(int v : son[u]) ret += dfs2(v) + sz[v], hp.emplace(sz[v]);
	while(hp.size() > 2) {
		int x = hp.top(); hp.pop();
		int y = hp.top(); hp.pop();
		ret += x + y, hp.emplace(x + y);
	}
	return ret;
}

int main() {
	std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while(T--) {
		cin >> n;
		for(int i = 1; i <= n; i++) son[i].clear();
		for(int i = 2; i <= n; i++) cin >> fa[i], son[fa[i]].emplace_back(i);
		int ans1 = dfs1(1);
		LL ans2 = dfs2(1);
		printf("%d %lld\n", ans1, ans2);
	}
	return 0;
} /*
3
1
4
1 1 1
13
1 2 2 3 3 4 4 1 9 10 11 1
*/