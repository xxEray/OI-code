#include <cstdio>
#include <algorithm>

const int N = 1e4 + 5;
const int M = 2e4 + 5;

int n, K, m;

struct Edge { int u, v, w1, w2; } edge[M];
bool operator<(Edge x, Edge y) { return x.w}

int main() {
	scanf("%d%d%d", &n, &K, &m);
	for(int i = 1; i <= m; i++) scanf("%d%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w1, &edge[i].w2);
	
	return 0;
}