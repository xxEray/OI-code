#include <bits/stdc++.h>

const int N = 3000 + 5;

int n;
int a[N];

std::vector<int> ans;

int main() {
#ifndef DEBUG
	freopen("butterfly.in", "r", stdin);
	freopen("butterfly.out", "w", stdout);
#endif
	scanf("%d%*d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) for(int j = 1; j < n; j++) if(a[j] > a[j + 1]) ans.push_back(j), std::swap(a[j], a[j + 1]);
	printf("%d\n", (int)ans.size());
	for(int x : ans) printf("%d 2\n", x - 1);
	return 0;
}