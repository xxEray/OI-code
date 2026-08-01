#include <cstdio>
#include <algorithm>

const int N = 256;

int a, b, c;

bool f[N][N][N], vis[N * 3];

void sort(int &a, int &b, int &c) {
	if(a > b) std::swap(a, b);
	if(a > c) std::swap(a, c);
	if(b > c) std::swap(b, c);
}

void dfs(int x, int y, int z) {
	if(x < 0 || x > a) return;
	if(y < 0 || y > b) return;
	if(z < 0 || z > c) return;
	if(f[x][y][z]) return;
	f[x][y][z] = true;
	vis[x] = vis[y] = vis[z] = vis[x + y] = vis[x + z] = vis[y + z] = vis[x + y + z] = true;
	dfs(a, y, z), dfs(x, b, z), dfs(x, y, c);
	if(x + y > a) dfs(a, x + y - a, z); else dfs(x + y, 0, z);
	if(x + y > b) dfs(x + y - b, b, z); else dfs(0, x + y, z);
	if(y + z > b) dfs(x, b, y + z - b); else dfs(x, y + z, 0);
	if(y + z > c) dfs(x, y + z - c, c); else dfs(x, 0, y + z);
	if(x + z > a) dfs(a, y, x + z - a); else dfs(x + z, y, 0);
	if(x + z > c) dfs(x + z - c, y, c); else dfs(0, y, x + z);
}

int main() {
	scanf("%d%d%d", &a, &b, &c);
	sort(a, b, c);
	dfs(0, 0, 0);
	int ans = 0;
	for(int i = 1; i <= 765; i++) ans += vis[i];
	printf("%d\n", ans);
	return 0;
}