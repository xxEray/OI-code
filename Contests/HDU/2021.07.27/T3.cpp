#include <cstdio>
#include <algorithm>

const int N = 1e3 + 5;

struct Graph {
	struct Edge { int to, nxt; } edge[N << 1];
	int head[N], k;
	void add_edge(int u, int v) { edge[k] = (Edge){v, head[u]}; head[u] = k++; }
} G, DAG;
int n, stA, stB, ed;
int d[N];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
	}
	return 0;
}