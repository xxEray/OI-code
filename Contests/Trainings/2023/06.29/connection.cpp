#include <bits/stdc++.h>
#include "D.h"

const int N = 1000 + 5;

int n;
std::set<int> son[N];
int fa[N];

std::vector<int> leaf;
bool done[N];

bool vis[N];
void dfs(int u) {
	vis[u] = true;
	for(int v : son[u]) if(!vis[v]) dfs(v);
}
int dep[N], bl[N];
void dfs2(int u) {
	for(int v : son[u]) if(!vis[v]) dep[v] = dep[u] + 1, dfs2(v);
}
int find(std::vector<int> st, int x) {
	int l = 0, r = (int)st.size() - 1;
	while(l < r) {
		int mid = (l + r) >> 1;
		std::vector<int> vct;
		for(int i = l; i <= mid; i++) vct.push_back(st[i]);
		vct.push_back(1);
		if(ask(vct, x)) r = mid;
		else l = mid + 1;
	}
	return st[l];
}

std::vector<std::pair<int, int>> work(int n_) {
	n = n_;
	done[1] = true;
	for(int i = 2; i <= n; i++) {
		std::vector<int> vct;
		for(int j = 1; j <= n; j++) if(j != i) vct.push_back(j);
		if(!ask(vct, i)) leaf.push_back(i), done[i] = true, fa[i] = 1, son[1].insert(i);
	}
	// printf("leaf: "); for(int x : leaf) printf("%d ", x); puts("");
	std::vector<int> seq;
	for(int u = 1; u <= n; u++) if(!done[u]) seq.push_back(u);
	for(int u : seq) {
		int v = find(leaf, u);
		std::vector<int> line;
		int w = v;
		while(w != 1) line.push_back(w), w = fa[w];
		line.push_back(1);
		std::reverse(line.begin(), line.end());
		std::vector<int> vct;
		int l = 0, r = (int)line.size() - 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			vct.clear();
			for(int i = 0; i <= mid; i++) vct.push_back(line[i]);
			if(ask(vct, u)) r = mid;
			else l = mid + 1;
		}
		w = line[l];
		son[fa[w]].erase(w);
		fa[u] = fa[w], son[fa[w]].insert(u);
		fa[w] = u, son[u].insert(w);
	}
	dfs2(1);
	for(int u : leaf) {
		int v = fa[u];
		while(v != 1) bl[v] = u, v = fa[v];
	}
	std::sort(seq.begin(), seq.end(), [&](int x, int y) { return bl[x] == bl[y] ? dep[x] > dep[y] : bl[x] > bl[y]; });
	for(int u : seq) {
		for(int i = 1; i <= n; i++) vis[i] = false;
		dfs(u);
		while(true) {
			std::vector<int> vct;
			for(int x : leaf) if(!vis[x]) vct.push_back(x);
			vct.push_back(1);
			if(!ask(vct, u)) break;
			vct.pop_back();
			int v = find(vct, u);
			std::vector<int> line;
			int w = v;
			while(w != 1) line.push_back(w), w = fa[w];
			line.push_back(1);
			std::reverse(line.begin(), line.end());
			int l = 0, r = (int)line.size() - 1;
			while(l < r) {
				int mid = (l + r) >> 1;
				vct.clear();
				for(int i = 0; i <= mid; i++) vct.push_back(line[i]);
				if(ask(vct, u)) r = mid;
				else l = mid + 1;
			}
			w = line[l];
			// printf("insert %d into [%d, %d]\n", u, w, fa[w]);
			son[fa[w]].erase(w);
			fa[w] = u, son[u].insert(w);
			dfs(w);
		}
	}
	std::vector<std::pair<int, int>> edges;
	for(int i = 2; i <= n; i++) edges.push_back({fa[i], i});
	return edges;
}