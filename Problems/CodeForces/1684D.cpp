#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int a[N], skip[N];
int n, m;

struct Node { int v, id; } b[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) skip[i] = false;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = (Node){a[i] + i, i};
		std::sort(b + 1, b + n + 1, [](Node x, Node y) { return x.v > y.v; });
		for(int i = 1; i <= m; i++) skip[b[i].id] = true;
		long long ans = 0, ex = 0;
		for(int i = 1; i <= n; i++)
			if(skip[i]) ex++;
			else ans += a[i] + ex;
		printf("\t\t\t%lld\n", ans);
	}
	return 0;
}