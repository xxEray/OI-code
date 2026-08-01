#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
struct Edge { int u, v; LL r, p; } edge[N];
struct EdgeTo { int id, v; LL r, p; };
std::vector<EdgeTo> to[N];

bool exist[N];
int d[N];
LL f[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d%d%lld%lld", &edge[i].v, &edge[i].u, &edge[i].r, &edge[i].p), d[edge[i].v]++;
	std::sort(edge + 1, edge + m + 1, [&](const Edge &x, const Edge &y) { return x.r > y.r; });
	for(int i = 1; i <= m; i++) to[edge[i].u].push_back({i, edge[i].v, edge[i].r, edge[i].p}), exist[i] = true;
	for(int i = 1; i <= n; i++) std::reverse(to[i].begin(), to[i].end());
	std::vector<int> q;
	int cnt = n;
	for(int i = 1; i <= n; i++) f[i] = LLINF;
	for(int i = 1; i <= n; i++) if(!d[i]) f[i] = LLINF, q.push_back(i), cnt--;
	int pos = 1;
	while(cnt || !q.empty()) {
		if(q.empty()) {
			while(pos <= m && !exist[pos]) pos++;
			assert(pos <= m);
			// printf("edge[%d].u = %d\n", pos, edge[pos].u);
			assert(!to[edge[pos].u].empty());
			assert(to[edge[pos].u].back().id == pos);
			exist[pos] = false;
			to[edge[pos].u].pop_back();
			d[edge[pos].v]--;
			if(!d[edge[pos].v]) f[edge[pos].v] = std::min(f[edge[pos].v], edge[pos].r), q.push_back(edge[pos].v), cnt--;
			continue;
		}
		int u = q.back();
		// printf("u = %d\n", u);
		q.pop_back();
		for(auto [id, v, r, p] : to[u]) {
			assert(exist[id]);
			exist[id] = false;
			f[v] = std::min(f[v], std::max(f[u] - p, r));
			d[v]--;
			if(!d[v]) q.push_back(v), cnt--;
		}
		to[u].clear();
	}
	for(int i = 1; i <= n; i++) printf("%lld ", f[i] >= LLINF / 2 ? -1LL : f[i]);
	return 0;
}