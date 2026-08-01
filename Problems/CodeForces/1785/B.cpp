#include <cstdio>
#include <algorithm>
#include <vector>
#include <array>
#include <cassert>
#include <set>

const int N = 1e5 + 5;

int n;
int a[N][3];

std::vector<int> g[3][3];
std::vector<std::array<int, 4>> ans;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		ans.clear();
		for(int j = 0; j <= 2; j++) for(int k = 0; k <= 2; k++) g[j][k].clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			a[i][0] = a[i][1] = a[i][2] = 0;
			char s[4];
			scanf("%s", s);
			for(int j = 0; j < 3; j++) a[i][s[j] == 'w' ? 0 : (s[j] == 'i' ? 1 : 2)]++;
		}
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j <= 2; j++) if(a[i][j] == 3)
				for(int k = 0; k <= 2; k++) if(k != j)
					g[j][k].push_back(i);
			for(int j = 0; j <= 2; j++) if(a[i][j] == 2)
				for(int k = 0; k <= 2; k++) if(a[i][k] == 0)
					g[j][k].push_back(i);
		}
		for(int j = 0; j <= 2; j++) for(int k = 0; k <= 2; k++) if(j != k) {
			while(!g[j][k].empty() && !g[k][j].empty())
				ans.push_back({g[j][k].back(), j, g[k][j].back(), k}), g[j][k].pop_back(), g[k][j].pop_back();
		}
		while(!g[0][1].empty()) {
			ans.push_back({g[0][1].back(), 0, g[2][0].back(), 1});
			ans.push_back({g[1][2].back(), 1, g[2][0].back(), 2});
			g[0][1].pop_back(), g[1][2].pop_back(), g[2][0].pop_back();
		}
		while(!g[1][0].empty()) {
			ans.push_back({g[1][0].back(), 1, g[2][1].back(), 0});
			ans.push_back({g[0][2].back(), 0, g[2][1].back(), 2});
			g[1][0].pop_back(), g[2][1].pop_back(), g[0][2].pop_back();
		}
		printf("%d\n", (int)ans.size());
		for(auto p : ans) printf("%d %c %d %c\n", p[0], "win"[p[1]], p[2], "win"[p[3]]);
	}
	return 0;
}