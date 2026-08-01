#include <bits/stdc++.h>

const int N = 5e5 + 5;

int n;

int a[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); a[x]++; }
	std::sort(a + 1, a + n + 1, std::greater<int>());
	int cnt = n, ans = 0;
	for(int i = 1; i <= n && cnt > 0; i++) {
		cnt -= 2 * a[i] - 1;
		ans++;
	}
	printf("%d\n", ans);
	return 0;
}