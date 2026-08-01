#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 1e6 + 5;

int a[N];
int n, m;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int belong[N];
std::vector<int> nums[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1; i <= m; i++) { int p, q; scanf("%d%d", &p, &q); merge(p, q); }
	for(int i = 1; i <= n; i++) nums[find(i)].push_back(a[i]);
	for(int i = 1; i <= n; i++) if(!nums[i].empty()) std::sort(nums[i].begin(), nums[i].end());
	for(int i = 1; i <= n; i++) printf("%d ", nums[find(i)].back()), nums[find(i)].pop_back();
	return 0;
}