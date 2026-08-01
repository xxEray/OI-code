#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

const int N = 8 + 5;
const int INF = 0x3f3f3f3f;

int n;
char s[N][N];

inline int dist(const std::pair<int, int> &x, const std::pair<int, int> &y)
	{ return std::max(std::abs(x.first - y.first), std::abs(x.second - y.second)); }

std::map<std::vector<std::pair<int, int>>, int> mp;
int dfs(std::vector<std::pair<int, int>> a) {
	if(mp.count(a)) return mp[a];
	if(a.size() <= 1) return 0;
	int sz = a.size();
	int mxx = 0, mxy = 0, mnx = 0, mny = 0;
	for(int i = 0; i < sz; i++) {
		if(a[i].first > a[mxx].first) mxx = i;
		if(a[i].first < a[mnx].first) mnx = i;
		if(a[i].second > a[mxy].second) mxy = i;
		if(a[i].second < a[mny].second) mny = i;
	}
	int x, y, ans = INF;
	if(a[mxx].first - a[mnx].first < a[mxy].second - a[mny].second) x = mxy, y = mny;
	else x = mxx, y = mnx;
	std::vector<std::pair<int, int>> b = a;
	b.erase(b.begin() + x);
	ans = std::min(ans, dfs(b) + dist(a[x], a[y]));
	b = a;
	b.erase(b.begin() + y);
	ans = std::min(ans, dfs(b) + dist(a[x], a[y]));
	return mp[a] = ans;
}

int main() {
	for(int i = 1; i <= 8; i++) scanf("%s", s[i] + 1);
	std::vector<std::pair<int, int>> vct;
	for(int i = 1; i <= 8; i++)
		for(int j = 1; j <= 8; j++)
			if(s[i][j] == '#')
				vct.push_back({i + j, i - j});
	printf("%d\n", dfs(vct));
	return 0;
}