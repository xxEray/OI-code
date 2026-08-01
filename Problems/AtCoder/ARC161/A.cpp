#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
int a[N], b[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1, [&](int x, int y) { return x > y; });
	int j = 1;
	for(int i = 2; i <= n; i += 2) b[i] = a[j++];
	for(int i = 1; i <= n; i += 2) b[i] = a[j++];
	bool flag = true;
	for(int i = 2; i <= n; i += 2) flag &= (b[i] > b[i - 1] && b[i] > b[i + 1]);
	puts(flag ? "Yes" : "No");
	return 0;
}