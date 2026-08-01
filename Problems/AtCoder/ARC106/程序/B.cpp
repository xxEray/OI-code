#include <cstdio>

const int N = 2e5 + 5;
const int M = 2e5 + 5;

struct Edge { int to, nxt; } edge[M << 1];
int head[N], bef[N], now[N];
void add_edge(int u, int v) {
	static int k = 1;
	edge[k] = (Edge){v, head[u]};
	head[u] = k++;
}

int n, m;

int main() {

	return 0;
}