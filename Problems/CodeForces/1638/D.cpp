#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>

const int N = 1000 + 5;

int a[N][N];
int n, m;

bool vis[N][N];
int color[N][N];

std::queue<std::pair<int, int>> q;
std::vector<std::array<int, 3>> ans;

int check(int x, int y) {
	if(x < 1 || x + 1 > n || y < 1 || y + 1 > m) return false;
	bool flag = true;
	int v = 0;
	for(int i = x; i <= x + 1; i++) for(int j = y; j <= y + 1; j++) flag &= (color[i][j] ? true : (v ? a[i][j] == v : (v = a[i][j], true)));
	return flag ? v : 0;
}
void setcolor(int x, int y) {
	int c = check(x, y);
	for(int i = x; i <= x + 1; i++) for(int j = y; j <= y + 1; j++) if(!color[i][j]) color[i][j] = c;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(check(i, j))
		q.push({i, j}), ans.push_back({i, j, check(i, j)}), vis[i][j] = true, setcolor(i, j);
	while(!q.empty()) {
		int x = q.front().first, y = q.front().second;
		q.pop();
		for(int i = x - 1; i <= x + 1; i++) for(int j = y - 1; j <= y + 1; j++) if(!vis[i][j] && check(i, j)) {
			q.push({i, j}), ans.push_back({i, j, check(i, j)}), vis[i][j] = true;
			setcolor(i, j);
		}
	}
	std::reverse(ans.begin(), ans.end());
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) printf("%d%c", color[i][j], " \n"[j == m]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(!color[i][j]) { puts("-1"); return 0; }
	printf("%d\n", (int)ans.size());
	for(auto &j : ans) printf("%d %d %d\n", j[0], j[1], j[2]);
	return 0;
}