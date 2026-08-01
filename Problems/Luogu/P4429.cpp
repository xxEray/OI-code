#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

const int N = 1e4 + 5;
const int M = 2e4 + 5;

int n, m;
std::set<int> to[N];

int d[N];

int color[N];
bool flag;
void dfs(int u) {
	for(int v : to[u])
		if(!color[v]) color[v] = 3 - color[u], dfs(v);
		else if(color[v] == color[u]) { flag = false; return; }
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) to[i].clear(), color[i] = 0, d[i] = 0;
		for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[u].insert(v), to[v].insert(u); d[u]++, d[v]++; }
		std::vector<int> stk;
		for(int i = 1; i <= n; i++) if(d[i] == 1) stk.push_back(i);
		while(!stk.empty()) {
			int u = stk.back();
			stk.pop_back();
			for(int v : to[u]) {
				to[v].erase(u);
				d[u]--, d[v]--;
				if(d[v] == 1) stk.push_back(v);
			}
			to[u].clear();
		}
		flag = true;
		for(int i = 1; i <= n; i++) if(!color[i]) color[i] = 1, dfs(i);
		for(int i = 1; i <= n; i++) if(d[i] > 3) flag = false;
		if(!flag) { puts("NO"); continue; }
		std::vector<int> dots;
		for(int i = 1; i <= n; i++) if(d[i] == 3) dots.push_back(i);
		if(dots.size() == 0) { puts("YES"); continue; }
		else if(dots.size() != 2) { puts("NO"); continue; }
		int tot = 0;
		for(int u = 1; u <= n; u++) if(d[u] == 2) {
			bool ok1 = false, ok2 = false;
			for(int v : to[u])
				if(v == dots[0]) ok1 = true;
				else if(v == dots[1]) ok2 = true;
			if(ok1 && ok2) tot++;
		}
		puts(tot >= 2 ? "YES" : "NO");
	}
	return 0;
}