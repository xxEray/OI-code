#include <cstdio>
#include <algorithm>
#include <set>

const int N = 1000 + 5;

char a[N][N];

int n, m;

int fa[N << 1];
void init(int tot) { for(int i = 1; i <= tot; i++) fa[i] = i; }
int leader(int x) { return x == fa[x] ? x : fa[x] = leader(fa[x]); }
void merge(int x, int y) { fa[leader(x)] = leader(y); }

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
	a[1][1] = a[1][m] = a[n][1] = a[n][m] = '#';
	init(n + m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(a[i][j] == '#')
				merge(i, n + j);
	std::set<int> row, col;
	for(int i = 1; i <= n; i++) row.insert(leader(i));
	for(int i = 1; i <= m; i++) col.insert(leader(n + i));
	printf("%d\n", std::min((int)row.size() - 1, (int)col.size() - 1));
	return 0;
}