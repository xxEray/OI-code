#include <cstdio>
#include <algorithm>
#include <vector>
#include <array>

const int N = 100 + 5;

int a[N][N];
int n, m;

std::vector<std::array<int, 4>> ans;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%1d", &a[i][j]);
		if(a[1][1]) { puts("-1"); continue; }
		ans.clear();
		for(int i = n; i >= 1; i--) for(int j = m; j >= 1; j--) {
			if(!a[i][j]) /* ans.push_back({i, j, i, j}) */;
			else if(j == 1) ans.push_back({i - 1, j, i, j});
			else ans.push_back({i, j - 1, i, j});
		}
		printf("%d\n", (int)ans.size());
		for(auto p : ans) printf("%d %d %d %d\n", p[0], p[1], p[2], p[3]);
	}
	return 0;
}