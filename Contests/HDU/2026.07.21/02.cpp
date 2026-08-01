#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n;
int fa[N];
int ls[N], rs[N];

int x[N], y[N];
int tot = 0;
void dfs(int u) {
	if(ls[u]) {
		y[ls[u]] = y[u] + 1;
		dfs(ls[u]);
	}
	x[u] = ++tot;
	if(rs[u]) {
		y[rs[u]] = y[u] + 1;
		dfs(rs[u]);
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		tot = 0;
		for(int i = 1; i <= n; i++) fa[i] = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%d%d", &ls[i], &rs[i]);
			if(ls[i]) fa[ls[i]] = i;
			if(rs[i]) fa[rs[i]] = i;
		}
		dfs(1);
		for(int i = 1; i <= n; i++) printf("%d %d\n", x[i], y[i]);
	}
	return 0;
}