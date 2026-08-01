#include <cstdio>
#include <algorithm>

const int N = 1000 + 5;

int n;

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
std::vector<std::pair<int, std::pair<int, int>>> edges;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			edges.push_back({gcd(i, j), {i, j}});
	std::sort(edges.begin(), edges.end());
	for(int i = 1; i <= n; i++) fa[i] = i;
	int weight = 0, cnt = 0;
	for(auto it = edges.rbegin(); it != edges.rend() && cnt < n - 1; it++) {
		int u = it->second.first, v = it->second.second, w = it->first;
		if(find(u) != find(v)) {
			merge(u, v);
			weight += w;
			cnt++;
		}
	}
	printf("%d ", weight);
	for(int i = 1; i <= n; i++) fa[i] = i;
	weight = 0, cnt = 0;
	for(auto it = edges.begin(); it != edges.end() && cnt < n - 1; it++) {
		int u = it->second.first, v = it->second.second, w = it->first;
		if(find(u) != find(v)) {
			merge(u, v);
			weight += w;
			cnt++;
		}
	}
	printf("%d\n", weight);
	return 0;
}