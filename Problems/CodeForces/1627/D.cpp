#include <cstdio>
#include <algorithm>

const int N = 1e6 + 5;

int a[N];
int n;

struct Edge { int to, nxt; } edge[N];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

bool exist[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), exist[a[i]] = true;
	int maxn = 1e6, ans = 0;
	for(int i = 1; i <= maxn; i++) {
		int g = 0;
		for(int j = i + i; j <= maxn; j += i)
			if(exist[j]) g = gcd(g, j / i);
		if(g == 1 && !exist[i]) ans++;
	}
	printf("%d\n", ans);
	return 0;
}