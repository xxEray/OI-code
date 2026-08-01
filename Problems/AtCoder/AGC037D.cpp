#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 100 + 5;

int a[N][N], b[N][N], c[N][N];
int n, m;

std::vector<int> edge[N];
int to[N], from[N];
bool vis[N][N], instk[N];

inline int color(int x) { return (x - 1) / m + 1; }

bool match(int x) {
	instk[x] = true;
	for(int y : edge[x])
		if(!from[y] || (!instk[from[y]] && match(from[y])))
			return to[x] = y, from[y] = x, true;
	return false;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	for(int col = 1; col <= m; col++) {
		// printf("column = %d\n", col);
		for(int i = 1; i <= n; i++) from[i] = to[i] = 0, edge[i].clear();
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				if(!vis[i][j])
					edge[i].push_back(color(a[i][j]));
		// for(int i = 1; i <= n; i++) {
		// 	printf("edge[%d]: ", i);
		// 	for(int x : edge[i]) printf("%d ", x);
		// 	puts("");
		// }
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) instk[j] = false;
			if(!match(i)) return 1;
		}
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				if(!vis[i][j] && color(a[i][j]) == to[i])
					{ b[i][col] = a[i][j], vis[i][j] = true; break; }
		// for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) printf("%d%c", b[i][j], j == m ? '\n' : ' ');
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			c[color(b[i][j])][j] = b[i][j];
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) printf("%d%c", b[i][j], j == m ? '\n' : ' ');
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) printf("%d%c", c[i][j], j == m ? '\n' : ' ');
	return 0;
}