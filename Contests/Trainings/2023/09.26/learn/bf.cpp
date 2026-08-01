#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n, m;

int *a[N], *b[N];
bool vis[N];
int now[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) a[i] = new int[m + 1], b[i] = new int[m + 1];
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &b[i][j]);
	int ans = 0;
	while(true) {
		int id = 0;
		for(int i = 1; i <= n; i++) if(!vis[i]) {
			bool flag = true;
			for(int j = 1; j <= m; j++) flag &= a[i][j] <= now[j];
			if(flag) { id = i; break; }
		}
		if(!id) break;
		ans++, vis[id] = true;
		for(int j = 1; j <= m; j++) now[j] += b[id][j], now[j] = std::min(now[j], 1000000000);
	}
	printf("%d\n", ans);
	return 0;
}