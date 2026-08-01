#include <bits/stdc++.h>

const int N = (1 << 20) + 5;

int n;
int a[N];

std::vector<int> ans;
void dfs(int id, int prefix) {
	// printf("dfs %d %d:\n", id, prefix);
	// for(int i = 0; i < (1 << n); i++) printf("  a[%d] = %d\n", i, a[i]);
	if(id == n + 1) {
		if(a[0] & 1) ans.emplace_back(prefix);
		return;
	}
	std::vector<int> b(1 << (n - id));
	for(int suffix = 0; suffix < (1 << (n - id)); suffix++) b[suffix] = a[suffix];
	for(int suffix = 0; suffix < (1 << (n - id)); suffix++)
		a[suffix] = a[suffix | (1 << (n - id))] & b[suffix];
	// printf("  (0)\n", id, prefix);
	// for(int i = 0; i < (1 << n); i++) printf("    a[%d] = %d\n", i, a[i]);
	dfs(id + 1, prefix);
	for(int suffix = 0; suffix < (1 << (n - id)); suffix++)
		a[suffix] = (a[suffix | (1 << (n - id))] >> 1) & b[suffix];
	// printf("  (1)\n", id, prefix);
	// for(int i = 0; i < (1 << n); i++) printf("    a[%d] = %d\n", i, a[i]);
	dfs(id + 1, prefix | (1 << (n - id)));
	for(int suffix = 0; suffix < (1 << (n - id)); suffix++) a[suffix] = b[suffix];
}

int main() {
	scanf("%d", &n);
	a[0] = 1;
	for(int i = 1; i < (1 << n); i++) scanf("%d", &a[i]);
	dfs(1, 0);
	printf("%d\n", (int)ans.size());
	for(int x : ans) printf("%d\n", x);
	return 0;
}