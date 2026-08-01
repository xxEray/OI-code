#include <cstdio>
#include <algorithm>

const int N = 6e5 + 5;

int a[N];
int n;

int c;
int b[N];

int main() {
#ifndef DEBUG
	freopen("interval.in", "r", stdin);
	freopen("interval.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%1d", &a[i]);
	int last = 0;
	for(int i = 1; i <= n; i++) if(i == n || a[i] != a[i + 1]) b[++c] = i - last, last = i;
	int ans = 0;
	for(int i = 1; i <= c; i++) ans = std::max(ans, b[i]);
	for(int i = 1; i <= c - 2; i++) ans = std::max(ans, b[i] + b[i + 2]);
	printf("%d\n", ans);
	return 0;
}
