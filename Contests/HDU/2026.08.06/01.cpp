// auto input
#include <bits/stdc++.h>
#include <cassert>
#ifndef DEBUG
#define assert(...) ((void)0)
#endif

const int N = 5e5 + 5;

int n;
std::vector<std::pair<int, int>> to[N];

int fa[N];

bool f[N][2];
void dfs(int u) {
	bool flag = true;
	for(auto [id, v] : to[u]) if(v != fa[u]) {
		fa[v] = u, dfs(v);
		flag &= (f[v][0] || f[v][1]);
	}
	if(to[u].size() == 1) {
		if(u == 1) {
			int v = to[u][0].second;
			f[u][0] = f[v][0];
			// f[u][1] is unimportant
		} else {
			f[u][0] = false, f[u][1] = true;
		}
		return;
	}
	if(!flag) { f[u][0] = f[u][1] = false; return; }
	int last1 = to[u].rbegin()->second, last2 = std::next(to[u].rbegin())->second;
	if(last1 == fa[u]) {
		f[u][1] = true, f[u][0] = f[last2][1];
	} else if(last2 == fa[u]) {
		if(f[last1][0]) f[u][0] = f[u][1] = true;
		else f[u][0] = true, f[u][1] = false;
	} else {
		f[u][0] = f[u][1] = (f[last1][0] || (f[last1][1] && f[last2][1]));
	}
	// printf("f[%d] = {%d, %d}\n", u, (int)f[u][0], (int)f[u][1]);
}

int ans[N];

void dfs_mex1(int u, bool fl, int uid) {
	if(to[u].size() == 1) {
		if(u == 1) {
			auto [vid, v] = to[u][0];
			dfs_mex1(v, 0, vid);
		} else {
			assert(fl);
			ans[uid] = fa[u];
		}
		return;
	}
	auto [lid1, last1] = *to[u].rbegin();
	auto [lid2, last2] = *std::next(to[u].rbegin());
	for(auto [id, v] : to[u]) if(v != fa[u] && v != last1 && v != last2) {
		assert(f[v][0] || f[v][1]);
		if(f[v][0]) dfs_mex1(v, 0, id);
		else dfs_mex1(v, 1, id);
	}
	if(last1 == fa[u]) {
		if(fl) ans[uid] = fa[u], dfs_mex1(last2, (f[last2][0] ? 0 : 1), lid2);
		else ans[uid] = u, dfs_mex1(last2, 1, lid2);
	} else if(last2 == fa[u]) {
		if(f[last1][0]) {
			if(fl) ans[uid] = fa[u];
			else ans[uid] = u;
			dfs_mex1(last1, 0, lid1);
		} else {
			assert(!fl);
			ans[uid] = u, dfs_mex1(last1, 1, lid1);
		}
	} else {
		if(fl) ans[uid] = fa[u];
		else ans[uid] = u;
		if(f[last1][0]) dfs_mex1(last1, 0, lid1), dfs_mex1(last2, (f[last2][0] ? 0 : 1), lid2);
		else dfs_mex1(last1, 1, lid1), dfs_mex1(last2, 1, lid2);
	}
}

void dfs_mex2(int u) {
	for(auto [id, v] : to[u]) if(v != fa[u]) {
		ans[id] = v;
		dfs_mex2(v);
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) to[i].clear();
		for(int i = 1; i < n; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			to[u].emplace_back(i, v), to[v].emplace_back(i, u);
		}
		for(int i = 1; i <= n; i++) std::sort(to[i].begin(), to[i].end());
		fa[1] = 0;
		dfs(1);
		if(f[1][0]) {
			puts("1");
			dfs_mex1(1, 0, 0);
			for(int i = 1; i < n; i++) printf("%d ", ans[i]);
			puts("");
		} else {
			puts("2");
			dfs_mex2(1);
			for(int i = 1; i < n; i++) printf("%d ", ans[i]);
			puts("");
		}
	}
	return 0;
} /*
3
2
1 2
6
4 3
2 1
3 1
5 3
6 1
8
4 7
2 5
1 3
6 2
3 6
8 3
2 4
*/