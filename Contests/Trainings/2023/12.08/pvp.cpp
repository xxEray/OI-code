#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D, *Iend = in + D;
	char rdc() { return (I == in + D ? Iend = in + fread(I = in, 1, D, stdin) : 0), (I == Iend ? EOF : *I++); }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
}
using FIO::read;

const int N = 5e4 + 5;

int n, K;
std::vector<int> to[N];
int d[N];

bool exist[N];

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;

int ans;
std::vector<int> vct;
std::vector<int> now;
void dfs(int id) {
	ans = std::max(ans, (int)now.size());
	if(id == (int)vct.size()) return;
	if(ans == K + 1) return;
	if((int)now.size() + (int)vct.size() - id <= ans) return;
	dfs(id + 1);
	const auto &u = vct[id];
	for(auto v : now) {
		auto it = std::lower_bound(to[u].begin(), to[u].end(), v);
		if(it == to[u].end() || *it != v) return;
	}
	now.emplace_back(u);
	dfs(id + 1);
	now.pop_back();
}

int main() {
#ifndef DEBUG
	freopen("pvp.in", "r", stdin);
	freopen("pvp.out", "w", stdout);
#endif
	read(n), read(K);
	for(int i = 1; i <= n; i++) {
		exist[i] = true;
		int c, x;
		read(c);
		while(c--) read(x), to[i].emplace_back(x + 1);
		std::sort(to[i].begin(), to[i].end());
		d[i] = to[i].size();
		q.emplace(d[i], i);
	}
	while(!q.empty()) {
		auto u = q.top().second;
		q.pop();
		if(!exist[u]) continue;
		exist[u] = false;
		vct.clear();
		for(auto v : to[u]) if(exist[v]) vct.emplace_back(v);
		dfs(0);
		for(auto v : vct) d[v]--, q.emplace(d[v], v);
	}
	printf("%d\n", ans + 1);
	return 0;
} /*
8 2
1 2
3 7 3 5
2 7 0
1 1
1 7
1 1
1 7
4 6 4 1 2
*/