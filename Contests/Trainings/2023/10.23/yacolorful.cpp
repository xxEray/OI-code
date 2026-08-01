#include <bits/stdc++.h>

const int N = 1000 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

std::vector<int> ans;

int main() {
#ifndef DEBUG
	freopen("yacolorful.in", "r", stdin);
	freopen("yacolorful.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::reverse(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) ans.push_back(a[i]);
	int cnt = 0;
	for(int i = 2; i <= n; i++) cnt += (a[i] == n - i + 2);
	int p = 2;
	while(cnt < n - 1) {
		if(a[1] == n - p + 2 || (a[1] == 1 && a[p] != n - p + 2)) std::swap(a[1], a[p]), cnt += (a[p] == n - p + 2);
		// printf("%d ", a[p]);
		ans.push_back(a[p]);
		p = (p == n ? 2 : p + 1);
	}
	while(p <= n) ans.push_back(a[p]), p++;
	ans.push_back(a[1]);
	std::reverse(ans.begin(), ans.end());
	printf("%d\n", (int)ans.size());
	for(int x : ans) printf("%d ", x);
	puts("");
	return 0;
}