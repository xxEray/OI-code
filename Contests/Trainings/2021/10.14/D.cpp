#include <cstdio>
#include <algorithm>

const int N = 50 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }



int main() {

	return 0;
}