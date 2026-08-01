#include <bits/stdc++.h>

typedef long long LL;

const int N = 100 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, K;
int inp[N];

int cnt[N];
LL val[N];
int tmp[N];
int c;
void discrete() {
	for(int i = 1; i <= n; i++) tmp[++c] = inp[i];
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) {
		int v = std::lower_bound(tmp + 1, tmp + c + 1, inp[i]) - tmp;
		cnt[v]++, val[v] = inp[i];
	}
}

std::map<std::vector<int>, LL> f;
void dfs2(std::vector<std::pair<int, int>> &vp, std::vector<int> &nxt, int target, int sz, int id, const std::function<void()> &func, int cn) {
	if(id == (int)vp.size()) { if(cn == target) func(); return; }
	if(cn > target) return;
	dfs2(vp, nxt, target, sz + vp[id].second, id + 1, func, cn);
	for(int i = 0; i < vp[id].second; i++) {
		nxt[sz + i] = vp[id].first - 1;
		dfs2(vp, nxt, target, sz + vp[id].second, id + 1, func, cn + (i + 1));
	}
	for(int i = 0; i < vp[id].second; i++) nxt[sz + i] = vp[id].first;
}
LL dfs(int id, std::vector<int> vct) {
	if(id == 0 && vct.empty()) return 0;
	if(id == 0 || vct.empty()) return LLINF;
	if(f.count(vct)) return f[vct];
	// printf("dfs id=%d,vct=", id); for(int x : vct) printf("%d ", x); puts("");
	std::vector<std::pair<int, int>> vp;
	for(int x : vct)
		if(vp.empty() || vp.back().first != x) vp.emplace_back(x, 1);
		else vp.back().second++;
	// printf("    vp: "); for(auto [x, y] : vp) printf("(%d, %d) ", x, y); puts("");
	std::vector<int> nxt = vct;
	LL ret = LLINF;
	dfs2(vp, nxt, cnt[id], 0, 0, [&]() {
		int cc = 0;
		for(int x : vct) if(x == n / K) cc++;
		for(int x : nxt) if(x == n / K) cc--;
		int i = 0;
		while(i < (int)nxt.size() && nxt[i] == 0) i++;
		std::vector<int> vnxt(nxt.begin() + i, nxt.end());
		ret = std::min(ret, dfs(id - 1, vnxt) - i * val[id] + cc * val[id]);
	}, 0);
	// printf("> dfs id=%d,vct=", id); for(int x : vct) printf("%d ", x); printf("= %lld\n", ret);
	return f[vct] = ret;
}

int main() {
#ifndef DEBUG
	freopen("diyiti.in", "r", stdin);
	freopen("diyiti.out", "w", stdout);
#endif
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &inp[i]);
	discrete();
	// for(int i = 1; i <= c; i++) printf("%d: cnt=%d, val=%lld\n", i, cnt[i], val[i]);
	std::vector<int> vct;
	for(int i = 0; i < K; i++) vct.emplace_back(n / K);
	LL ans = dfs(c, vct);
	if(ans == LLINF) puts("-1");
	else printf("%lld\n", ans);
	return 0;
} /*
8 4
6 3 8 1 3 1 2 2 
*/