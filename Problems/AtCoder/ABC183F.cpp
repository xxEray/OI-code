#include <cstdio>
#include <map>

const int N = 2e5 + 5;

int c[N];
int n, m;

int fa[N];
std::map<int, int> mp[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main() {
	std::scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) std::scanf("%d", &c[i]);
	for(int i = 1; i <= n; i++) fa[i] = i, mp[i][c[i]] = 1;
	for(int i = 1; i <= m; i++) {
		int t, x, y;
		std::scanf("%d%d%d", &t, &x, &y);
		if(t == 1) {
			x = find(x), y = find(y);
			if(x == y) continue;
			if(mp[x].size() > mp[y].size()) std::swap(x, y);
			for(std::pair<int, int> t : mp[x]) mp[y][t.first] += t.second;
			mp[x].clear();
			fa[x] = y;
		} else if(t == 2) {
			std::printf("%d\n", mp[find(x)][y]);
		}
	}
	return 0;
}