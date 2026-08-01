#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = (1 << 16) + 5;

struct Node { int v; LL w; } a[N];
int n;

bool vis[N];

int main() {
	scanf("%d", &n);
	n = (1 << n) - 1;
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i].w), a[i].v = i;
	std::sort(a + 1, a + n + 1, [](Node x, Node y) { return x.w < y.w; });
	int cnt = 0;
	LL ans = 0;
	vis[0] = true;
	for(int i = 1; i <= n && cnt < n; i++) {
		if(vis[a[i].v]) continue;
		vis[a[i].v] = true, cnt++;
		ans += a[i].w;
		for(int j = 1; j <= n; j++) if(vis[j] && !vis[a[i].v ^ j]) vis[a[i].v ^ j] = true, cnt++;
	}
	printf("%lld\n", ans);
	return 0;
}