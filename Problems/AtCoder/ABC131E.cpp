#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 100 + 5;

int edge[N][N];
int n, K;

int main() {
	scanf("%d%d", &n, &K);
	if(K > (n - 1) * (n - 2) / 2) { puts("-1"); return 0; }
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) edge[i][j] = (i != j);
	for(int i = 2; i <= n; i++) for(int j = i + 1; j <= n; j++) if(K) edge[i][j] = edge[j][i] = false, K--;
	int cnt = 0;
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) if(edge[i][j]) cnt++;
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) if(edge[i][j]) printf("%d %d\n", i, j);
	return 0;
}