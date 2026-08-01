#include <bits/stdc++.h>

const int N = 50 + 5;

int table[300];
bool exist[6];

int n, m;
int b[N][N];

std::vector<int> a[N];
bool vis[N][N];
const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int cnt;
std::vector<std::pair<int, int>> vct;
void dfs(int x, int y) {
	if(vis[x][y]) return;
	vis[x][y] = true;
	vct.push_back({x, y});
	cnt++;
	for(int d = 0; d < 4; d++) {
		int tx = x + dir[d][0], ty = y + dir[d][1];
		if(1 <= ty && ty <= m && 0 <= tx && tx <= (int)a[ty].size() - 1 && a[y][x] == a[ty][tx]) dfs(tx, ty);
	}
}

void solve(char prompt) {
	int major = table[prompt];
	// printf("solve %c=%d\n", prompt, major);
	int om = m;
	for(int j = 1; j <= m; j++) {
		a[j].resize(n);
		for(int i = 0; i < n; i++) a[j][i] = b[n - i][j];
	}
	// for(int i = 1; i <= m; i++) {
	// 	printf("%d: ", i);
	// 	for(int r : a[i]) printf("%d", r);
	// 	puts("");
	// }
	// puts("");
	int ans = 0;
	while(true) {
		int x = 0, y = 0, x2 = 0, y2 = 0;
		for(int j = 1; j <= m; j++) for(int i = 0; i < (int)a[j].size(); i++) vis[i][j] = false;
		int now = 0, now2 = 0;
		for(int i = 0; i < n; i++) for(int j = 1; j <= m; j++) if(i <= (int)a[j].size() - 1 && !vis[i][j]) {
			vct.clear();
			cnt = 0;
			dfs(i, j);
			// if(i == 1 && j == 5) printf("(1, 5): cnt = %d\n", cnt);
			if(cnt <= 1) continue;
			if(a[j][i] != major) {
				if(cnt > now) now = cnt, x = i, y = j;
			} else {
				if(cnt > now2) now2 = cnt, x2 = i, y2 = j;
			}
		}
		if(x == 0 && y == 0) {
			if(x2 == 0 && y2 == 0) break;
			x = x2, y = y2;
		}
		vct.clear();
		cnt = 0;
		for(int j = 1; j <= m; j++) for(int i = 0; i < (int)a[j].size(); i++) vis[i][j] = false;
		dfs(x, y);
		for(auto &p : vct) a[p.second][p.first] = 0;
		for(int j = 1; j <= m; j++) {
			int p = 0;
			for(int i = 0; i < (int)a[j].size(); i++) if(a[j][i]) a[j][p++] = a[j][i];
			a[j].erase(a[j].begin() + p, a[j].end());
		}
		int p = 0;
		for(int i = 1; i <= m; i++) if(!a[i].empty()) a[++p] = a[i];
		m = p;
		ans += cnt * (cnt - 1);
		// printf("x = %d, y = %d\n", x, y);
		// for(int i = 1; i <= m; i++) {
		// 	printf("%d: ", i);
		// 	for(int r : a[i]) printf("%d", r);
		// 	puts("");
		// }
		// puts("");
	}
	m = om;
	printf("%c: %d\n", prompt, ans);
}

int main() {
	table['B'] = 1, table['G'] = 2, table['R'] = 3, table['W'] = 4, table['Y'] = 5;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		char s[55];
		scanf("%s", s + 1);
		for(int j = 1; j <= m; j++) b[i][j] = table[s[j]];
	}
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) exist[b[i][j]] = true;
	for(char c : {'B', 'G', 'R', 'W', 'Y'}) if(exist[table[c]]) solve(c);
	return 0;
}