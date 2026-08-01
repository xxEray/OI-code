#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n;
int a[2 * N];

int another[2 * N];

struct DSU {
	int fa[2 * N];
	void init() { for(int i = 1; i <= 2 * n; i++) fa[i] = i; }
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }
} color, removed;

bool is_removed[2 * N];

int next_unremoved(int x) { return is_removed[x] ? removed.find(x) + 1 : x; }

std::vector<int> to[N];
int val[N];
bool flag;

void dfs(int u) {
	for(int v : to[u]) {
		if(val[v]) flag &= (val[v] == 3 - val[u]);
		else val[v] = 3 - val[u], dfs(v);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) { int x, y; scanf("%d%d", &x, &y); a[x] = i, a[y] = -i, another[x] = y, another[y] = x; }
	// printf("a: "); for(int i = 1; i <= 2 * n; i++) printf("%d ", a[i]); puts("");
	color.init(), removed.init();
	for(int i = 1; i <= 2 * n; i++) if(a[i] < 0) {
		int lastj = 0;
		for(int j = next_unremoved(another[i] + 1); j < i; j = next_unremoved(color.find(j) + 1)) {
			to[-a[i]].emplace_back(a[j]), to[a[j]].emplace_back(-a[i]); // , printf("%d <-> %d\n", -a[i], a[j]);
			if(lastj) color.merge(lastj, j);
			lastj = j;
		}
		int j = another[i];
		is_removed[j] = is_removed[i] = true;
		if(j > 1 && is_removed[j - 1]) removed.merge(j - 1, j);
		if(is_removed[j + 1]) removed.merge(j, j + 1);
		if(is_removed[i - 1]) removed.merge(i - 1, i);
	}
	flag = true;
	int cnt = 0;
	for(int i = 1; i <= n; i++) if(!val[i]) val[i] = 1, dfs(i), cnt++;
	if(!flag) puts("0");
	else {
		int ans = 1;
		while(cnt--) (ans *= 2) %= 1000000007;
		printf("%d\n", ans);
	}
	return 0;
}