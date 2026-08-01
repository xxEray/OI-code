#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

const int N = 3e5 + 5;

std::set<std::pair<int, int> > points;
int n, m, k;

int r[N], c[N];

int main() {
	std::scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= k; i++) {
		int x, y;
		std::scanf("%d%d", &x, &y);
		points.insert({x, y});
		r[x]++, c[y]++;
	}
	int mxr = *std::max_element(r + 1, r + n + 1);
	int mxc = *std::max_element(c + 1, c + m + 1);
	std::vector<int> rs, cs;
	for(int i = 1; i <= n; i++) if(r[i] == mxr) rs.push_back(i);
	for(int i = 1; i <= m; i++) if(c[i] == mxc) cs.push_back(i);
	if((long long)rs.size() * (long long)cs.size() > k)
		{ std::printf("%d\n", mxr + mxc); return 0; }
	bool flag = true;
	for(int i : rs)
		for(int j : cs)
			if(points.find({i, j}) == points.end())
				{ flag = false; break; } 
	std::printf("%d\n", mxr + mxc - flag);
	return 0;
}