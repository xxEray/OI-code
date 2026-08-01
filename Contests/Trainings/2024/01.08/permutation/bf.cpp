#include <bits/stdc++.h>

const int N = 100 + 5;

int n;
int a[N];

int gcd[N][N];

int ans;
bool vis[N];
void dfs(int id) {
	if(id == n + 1) {
		// for(int i = 1; i <= n; i++) printf("%d ", a[i]);
		// puts("");
		ans++;
		return;
	}
	if(a[id]) {
		bool flag = true;
		for(int j = 1; j < id; j++) flag &= ((gcd[j][id] == 1) == (gcd[a[j]][a[id]] == 1));
		if(flag) dfs(id + 1);
		return;
	}
	for(int i = 1; i <= n; i++) if(!vis[i]) {
		bool flag = true;
		for(int j = 1; j < id; j++) flag &= ((gcd[j][id] == 1) == (gcd[a[j]][i] == 1));
		if(flag) {
			vis[i] = true, a[id] = i;
			dfs(id + 1);
			vis[i] = false, a[id] = 0;
		}
	}
}

int main() {
	// freopen("out.txt", "w", stdout);
	scanf("%d", &n);
	// for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) gcd[i][j] = std::__gcd(i, j);
	for(int i = 1; i <= n; i++) if(a[i]) vis[a[i]] = true;
	dfs(1);
	printf("%d\n", ans);
	return 0;
}