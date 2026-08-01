#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 1e5 + 5;

int a[N], pos[N];
int n;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? (pos[x] > pos[y] ? fa[y] = x : fa[x] = y) : 0; }
std::vector<int> q;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), pos[a[i]] = i, fa[i] = i;
		q.clear();
		for(int i = 1; i <= n; i++) {
			while(!q.empty() && pos[q.back()] > pos[i]) merge(i, q.back()), q.pop_back();
			q.push_back(find(i));
		}
		int cnt = 0;
		for(int i = 1; i <= n; i++) cnt += (find(i) == i);
		printf("%d\n", cnt);
	}
	return 0;
}