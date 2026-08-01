#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

const int N = 2000 + 5;

int n;
int a[N];

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

std::vector<int> to[N], to2[N];

int ind[N];
std::priority_queue<int> q;
std::vector<int> ans;

bool vis[N];
void dfs(int u) {
	if(vis[u]) return;
	vis[u] = true;
	for(int v : to[u]) if(!vis[v]) {
		to2[u].push_back(v), ind[v]++;
		dfs(v);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) if(gcd(a[i], a[j]) != 1) to[i].push_back(j), to[j].push_back(i);
	for(int i = 1; i <= n; i++) dfs(i);
	for(int i = 1; i <= n; i++) if(!ind[i]) q.push(i);
	while(!q.empty()) {
		int u = q.top();
		q.pop();
		ans.push_back(a[u]);
		for(int v : to2[u]) if(ind[v]) {
			ind[v]--;
			if(ind[v] == 0) q.push(v);
		}
	}
	for(int x : ans) printf("%d ", x);
	puts("");
	return 0;
}