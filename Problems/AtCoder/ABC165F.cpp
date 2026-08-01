#include <cstdio>
#include <vector>

const int N = 2e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) {
	static int k = 1;
	edge[k] = (Edge){v, head[u]};
	head[u] = k++;
}
int a[N];
int n;

struct Undo { int val, pos; };
std::vector<int> h;
std::vector<Undo> unh;

int ans[N];

void dfs(int u, int fa) {
	if(h.empty() || h.back() < a[u]) {
		h.push_back(a[u]);
		unh.push_back({-1, -1});
	} else {
		int pos = std::lower_bound(h.begin(), h.end(), a[u]) - h.begin();
		unh.push_back({h[pos], pos});
		h[pos] = a[u];
	}
	ans[u] = (int)h.size();
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa) {
			int v = edge[i].to;
			dfs(v, u);
		}
	if(unh.back().pos == -1) h.pop_back();
	else h[unh.back().pos] = unh.back().val;
	unh.pop_back();
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs(1, 0);
	for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}