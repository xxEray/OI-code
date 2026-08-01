#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#include <vector>

const int N = 2e5 + 5;

const int d[8][2] = {-1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1};

std::set<std::pair<int, int>> st;
std::map<std::pair<int, int>, int> id;
std::vector<std::pair<int, int>> g[N];
std::vector<int> row[N];
std::pair<int, int> a[N];
int n, m, K, idcnt;

int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &K);
		st.clear(), id.clear(), idcnt = 0;
		for(int i = 1; i <= n; i++) row[i].clear();
		for(int i = 1; i <= K + n; i++) g[i].clear();
		for(int i = 1; i <= K + n; i++) fa[i] = i;
		for(int i = 1; i <= K; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			st.insert({x, y});
			id[{x, y}] = ++idcnt;
			a[i] = {x, y};
		}
		for(int i = 2; i <= n; i++) id[{i, 0}] = ++idcnt, st.insert({i, 0}), a[i + K - 1] = {i, 0};
		for(auto &p : st) row[p.first].push_back(p.second);
		for(int i = 1; i <= K + n - 1; i++) {
			int x = a[i].first, y = a[i].second;
			std::pair<int, int> p = {x, y};
			if(st.find({x - 1, y - 1}) != st.end()) merge(id[p], id[{x - 1, y - 1}]);
			if(st.find({x - 1, y}) != st.end()) merge(id[p], id[{x - 1, y}]);
			if(st.find({x - 1, y + 1}) != st.end()) merge(id[p], id[{x - 1, y + 1}]);
			if(st.find({x, y - 1}) != st.end()) merge(id[p], id[{x, y - 1}]);
		}
		for(auto &p : st) g[find(id[p])].push_back(p);
		int ans = 0;
		for(int i = 1; i <= K + n - 1; i++) {
			if(g[i].empty()) continue;
			// printf("\nGroup %d: ", i);
			int mx = 0;
			for(int j = 0; j < (int)g[i].size(); j++) {
				int x = g[i][j].first, y = g[i][j].second;
				if(x == 1) mx = m;
				else mx = std::max(mx, y);
				// if(j && g[i][j].first == g[i][j - 1].first) continue;
				auto leastiter = std::upper_bound(row[x].begin(), row[x].end(), y);
				int least;
				if(leastiter == row[x].end()) least = m;
				else least = *leastiter - 1;
				// printf("(%d, %d)+%d ", x, y, std::max(0, std::min(mx, least) - y + 1));
				ans += std::max(0, std::min(mx, least) - y + 1);
			}
		}
		printf("%d\n", n * m - ans + (n - 1));
	}
	return 0;
} /*
1
5 5 7
2 2
2 4
3 2
3 4
4 2
4 4
5 3

....
**..
.*..
**..
....

*/