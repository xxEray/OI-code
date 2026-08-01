#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 1e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) {
	static int k = 1;
	edge[k] = (Edge){v, head[u]};
	head[u] = k++;
}

int a[N];
int n;

int f[N];
int sz[N];

void dfs(int u, int fa) {
	int sum = 0;
	std::vector<int> seq;
	sz[u] = f[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa) {
			int v = edge[i].to;
			dfs(v, u);
			sz[u] += sz[v];
			if(sz[v] & 1) {
				// Type 3
				// the same as Type 2
				seq.push_back(-f[v]);
			} else {
				if(f[v] < 0) {
					// Type 1
					// f[u] -> #1 - #2
					// f[v] -> #2 - #1 => -f[v] = #1 - #2
					f[u] -= -f[v];
				} else {
					// Type 2
					// the same as Type 1
					sum += -f[v];
				}
			}
		}
	std::sort(seq.begin(), seq.end(), [](int a, int b) { return a > b; });
	seq.push_back(sum);
	for(int i = 0; i < (int)seq.size(); i++)
		if(i % 2) f[u] += seq[i];
		else f[u] -= seq[i];
}

int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) {
		int u;
		scanf("%d", &u);
		add_edge(u, i);
		add_edge(i, u);
	}
	dfs(1, 0);
	printf("%d\n", (n + f[1]) / 2);
	return 0;
}