#include <cstdio>
#include <algorithm>
#include <map>

const int N = 3000 + 5;

int n;
int a[N];

std::map<int, int> next[N];

int f[N][N];

int main() {
#ifndef DEBUG
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = n; i >= 1; i--) next[i] = next[i + 1], next[i][a[i]] = i;
	for(int i = n; i >= 1; i--) for(int j = i + 1; j <= n; j++)
		if(next[j + 1].count(a[i] + a[j])) f[i][j] = f[j][next[j + 1][a[i] + a[j]]] + 1;
		else f[i][j] = 2;
	int ans = 0;
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) ans = std::max(ans, f[i][j]);
	printf("%d\n", ans);
	return 0;
}
