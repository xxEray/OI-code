#include <cstdio>
#include <algorithm>

const int N = 16 + 5;

int a[N][N];
int n;

bool vis[N];

int ans = 0;
void dfs(int now, int ret) {
	if(now > n) { ans = std::max(ans, ret); return; }
	if(vis[now]) { dfs(now + 1, ret); return; }
	for(int i = now + 1; i <= n; i++) if(!vis[i]) {
		vis[i] = true;
		dfs(now + 1, ret ^ a[now][i]);
		vis[i] = false;
	}
}

int main() {
	scanf("%d", &n);
	n <<= 1;
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) scanf("%d", &a[i][j]), a[j][i] = a[i][j];
	dfs(1, 0);
	printf("%d\n", ans);
	return 0;
}