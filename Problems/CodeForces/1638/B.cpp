#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 5;

struct Node { int val, id; };
bool operator<(Node x, Node y) { return x.val == y.val ? x.id < y.id : x.val < y.val; }
int n;
int pos[N];
bool isodd[N];
std::vector<Node> a, b[2];
std::vector<std::pair<int, int>> seg[2];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		a.clear(), b[0].clear(), b[1].clear(), seg[0].clear(), seg[1].clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); if(a.empty() || x != a.back().val) a.push_back((Node){x, 0}); }
		n = a.size();
		for(int i = 0; i < n; i++) isodd[i] = a[i].val & 1;
		for(int i = 0; i < n; i++) b[isodd[i]].push_back(a[i]);
		for(int i = 0; i < (int)b[0].size(); i++) b[0][i].id = i;
		for(int i = 0; i < (int)b[1].size(); i++) b[1][i].id = i;
		std::sort(b[0].begin(), b[0].end()), std::sort(b[1].begin(), b[1].end());
		for(int i = 0; i < (int)b[0].size(); i++) pos[b[0][i].id] = i;
		for(int i = 0; i < (int)b[0].size(); i++) seg[0].push_back(std::make_pair(std::min(i, pos[i]), std::max(i, pos[i])));
		for(int i = 0; i < (int)b[1].size(); i++) pos[b[1][i].id] = i;
		for(int i = 0; i < (int)b[1].size(); i++) seg[1].push_back(std::make_pair(std::min(i, pos[i]), std::max(i, pos[i])));
		std::sort(seg[0].begin(), seg[0].end()), std::sort(seg[1].begin(), seg[1].end());
		bool flag = true;
		for(int i = 1; i < (int)seg[0].size(); i++) flag &= seg[0][i].first >= seg[0][i - 1].second;
		for(int i = 1; i < (int)seg[1].size(); i++) flag &= seg[1][i].first >= seg[1][i - 1].second;
		puts(flag ? "Yes" : "No");
	}
	return 0;
} /*
7
6 3 6 3 6 3 6
*/