#include <cstdio>
#include <algorithm>
#include <vector>

#define SZ(x) ((int)(x).size())

const int N = 1000 + 5;

std::vector<int> to[N];
int G[N][N];
int n, m;

int instk[N], vis[N];
std::vector<int> stk, ans, tmp;
void dfs(int u) {
	vis[u] = true;
	if(!ans.empty()) return;
	if(instk[u]) {
		for(int i = instk[u]; i <= SZ(stk); i++) ans.push_back(stk[i - 1]);
		return;
	}
	stk.push_back(u), instk[u] = stk.size();
	for(int v : to[u]) u == 144 && v == 184 && printf("uu"), dfs(v);
	stk.pop_back(), instk[u] = 0;
}

int ok[N];

int main() {
	// freopen("in.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v), G[u][v] = true; }
	for(int i = 1; i <= n; i++) if(!vis[i] && ans.empty()) dfs(i);
	if(ans.empty()) { puts("-1"); return 0; }
	for(int i = 1; i <= n; i++) ok[i] = -1;
	while(true) {
		// for(int x : ans) printf("%d ", x);
		// puts("");
		for(int i = 0; i < SZ(ans); i++) ok[ans[i]] = i;
		int st = -1, tv = -1;
		for(int i = 0; i < SZ(ans); i++) {
			int flag = 0;
			for(int v : to[ans[i]]) if(ok[v] != -1 && v != ans[(i + 1) % SZ(ans)]) { flag = 1, st = ok[v]; break; }
			if(flag) { tv = i; break; }
		}
		if(st == -1) break;
		// printf("st = %d, tv = %d\n", st, tv);
		for(int i = 1; i <= n; i++) ok[i] = -1;
		ok[ans[tv]] = tv;
		for(int i = st; ; (i += 1) %= SZ(ans)) {
			tmp.push_back(ans[i]);
			if(ok[ans[i]] != -1) break;
			ok[ans[i]] = 1;
		}
		ans = tmp;
		tmp.clear();
	}
	printf("%d\n", (int)ans.size());
	for(int x : ans) printf("%d\n", x);
	return 0;
}