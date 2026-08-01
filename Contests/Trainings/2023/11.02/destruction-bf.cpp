#include <bits/stdc++.h>

const int N = 2e6 + 5;

int n;
int a[N];

void dfs(int id, int vis, int gapvis) {
	if(id == n + 1) {
		for(int i = 1; i <= n; i++) printf("%d ", a[i]);
		puts("");
		// return;
		exit(0);
	}
	int maxgap = 0;
	for(int i = n - 1; i >= 0; i--) if(~gapvis >> i & 1) { maxgap = i; break; }
	int mn = n, mx = 1;
	for(int i = 1; i <= n; i++) if(~vis >> i & 1) { mn = i; break; }
	for(int i = n; i >= 1; i--) if(~vis >> i & 1) { mx = i; break; }
	if(n - mn < maxgap && mx - id < maxgap) return;
	for(int i = 1; i <= n; i++) if((~vis >> i & 1) && (~gapvis >> std::abs(i - id) & 1)) {
		a[id] = i;
		dfs(id + 1, vis | (1 << i), gapvis | (1 << std::abs(i - id)));
		a[id] = 0;
	}
}

int main() {
	scanf("%d", &n);
	dfs(1, 0, 0);
	// puts("No solution");
	return 0;
}