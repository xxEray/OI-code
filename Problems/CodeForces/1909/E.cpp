#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m;
struct Edge { int to, nxt; } edge[N];
int head[N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }

int low[N], dfn[N], stk[N], vis[N], top, time_stamp;
int scc, bl[N];
void tarjan(int u) {
	dfn[u] = low[u] = ++time_stamp;
	vis[u] = 1, stk[++top] = u;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(vis[v] == 0) tarjan(v), low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
	}
	if(low[u] == dfn[u]) {
		scc++;
		do {
			bl[stk[top]] = scc;
			vis[stk[top]] = 2;
		} while(top && stk[top--] != u);
	}
}

std::vector<int> vct[N];
void trim(std::vector<int> &vec) {
	std::sort(vec.begin(), vec.end());
	std::vector<int> tmp;
	for(int x : vec)
		if(tmp.empty() || x != tmp.back()) tmp.emplace_back(x);
		else tmp.pop_back();
	vec.swap(tmp);
}

std::set<int> st[N];
std::vector<int> to[N];
std::vector<int> seq;
int ans;
void dfs(int u) {
	if(vis[u]) return;
	vis[u] = true;
	if(ans) return;
	for(int v : to[u]) {
		dfs(v);
		if(ans) return;
		if(st[v].size() > st[u].size()) st[u].swap(st[v]);
		for(int x : st[v])
			if(st[u].count(x)) st[u].erase(x);
			else st[u].emplace(x);
	}
	// printf("st[%d]: ", u); for(int x : st[u]) printf("%d ", x); puts("");
	if((int)st[u].size() <= n / 5) { ans = u; return; }
	else if(seq.size() < 6 && to[u].empty()) {
		seq.emplace_back(u);
		vct[u].clear();
		for(int x : st[u]) vct[u].emplace_back(x);
	}
}

bool occ[N];
void settag(int u) {
	occ[u] = true;
	for(int v : to[u]) if(!occ[v]) settag(v);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1;
		scanf("%d%d", &n, &m);
		// n = rand() % 8 + 1, m = rand() % 10, printf("n = %d, m = %d\n", n, m);
		for(int i = 1; i <= n; i++) head[i] = 0;
		for(int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			// u = rand() % n + 1, v = rand() % n + 1, printf("%d %d\n", u, v);
			add_edge(u, v);
		}
		time_stamp = scc = top = 0;
		for(int i = 1; i <= n; i++) vis[i] = 0;
		for(int i = 1; i <= n; i++) if(!vis[i]) tarjan(i);
		printf("bl: "); for(int i = 1; i <= n; i++) printf("%d ", bl[i]); puts("");
		for(int i = 1; i <= n; i++) vct[i].clear(), st[i].clear();
		for(int i = 1; i <= n; i++)
			for(int j = i; j <= n; j += i)
				vct[bl[i]].emplace_back(j);
		for(int i = 1; i <= scc; i++) {
			trim(vct[i]);
			for(int x : vct[i]) st[i].emplace(x);
			// printf("vct[%d]: ", i); for(int x : vct[i]) printf("%d ", x); puts("");
		}
		for(int i = 1; i <= n; i++) to[i].clear();
		for(int u = 1; u <= n; u++) for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(bl[u] != bl[v]) to[bl[u]].emplace_back(bl[v]);
		}
		for(int i = 1; i <= scc; i++) {
			std::sort(to[i].begin(), to[i].end());
			to[i].erase(std::unique(to[i].begin(), to[i].end()), to[i].end());
			// for(int j : to[i]) printf("%d -> %d\n", i, j);
		}
		for(int i = 1; i <= n; i++) vis[i] = 0;
		seq.clear();
		ans = 0;
		for(int i = 1; i <= scc; i++) dfs(i);
		printf("ans = %d\n", ans);
		std::vector<int> ans_seq;
		if(ans) ans_seq.emplace_back(ans);
		else {
			int U = (1 << (int)seq.size());
			int ansset = -1;
			for(int s = 0; s <= U; s++) {
				std::vector<int> tmp;
				for(int i = 0; i < (int)seq.size(); i++) if(s >> i & 1)
					tmp.insert(tmp.end(), vct[seq[i]].begin(), vct[seq[i]].end());
				trim(tmp);
				if((int)tmp.size() <= n / 5) { ansset = s; break; }
			}
			if(ansset != -1)
				for(int i = 0; i < (int)seq.size(); i++) if(ansset >> i & 1) ans_seq.emplace_back(seq[i]);
		}
		if(ans_seq.empty()) puts("-1");
		else {
			std::vector<int> out;
			for(int i = 1; i <= n; i++) occ[i] = false;
			for(int x : ans_seq) settag(x);
			for(int i = 1; i <= n; i++) if(occ[bl[i]]) out.emplace_back(i);
			// for(int i = 1; i <= n; i++) occ[i] = false;
			// for(int i : out) for(int j = i; j <= n; j += i) occ[j] ^= 1;
			// int cnt = 0;
			// for(int i = 1; i <= n; i++) cnt += occ[i];
			// assert(cnt <= n / 5);
			printf("%d\n", (int)out.size());
			for(int x : out) printf("%d ", x);
			puts("");
		}
	}
	return 0;
} /*
1
6 7
5 2
3 1
6 1
6 3
3 3
4 6
2 1
*/