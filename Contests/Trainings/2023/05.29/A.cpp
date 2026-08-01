#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
std::array<int, 6> a[N], b[N];

int main() {
#ifndef DEBUG
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int x;
		for(int j = 0; j < 6; j++) scanf("%d", &x), a[i][j] += x;
		for(int j = 0; j < 6; j++) scanf("%d", &x), a[i][j] -= x;
	}
	for(int i = 1; i <= n; i++) {
		int x;
		for(int j = 0; j < 6; j++) scanf("%d", &x), b[i][j] += x;
		for(int j = 0; j < 6; j++) scanf("%d", &x), b[i][j] -= x;
	}
	for(int i = 1; i <= n; i++) for(int j = 0; j < 6; j++) a[i][j] += a[i - 1][j], b[i][j] += b[i - 1][j];
	// puts("a"); for(int i = 1; i <= n; i++) printf("%d %d %d %d %d %d\n", a[i][0], a[i][1], a[i][2], a[i][3], a[i][4], a[i][5]);
	// puts("b"); for(int i = 1; i <= n; i++) printf("%d %d %d %d %d %d\n", b[i][0], b[i][1], b[i][2], b[i][3], b[i][4], b[i][5]);
	std::sort(a + 1, a + n), std::sort(b + 1, b + n);
	bool flag = true;
	for(int i = 1; i <= n; i++) flag &= (a[i] == b[i]);
	puts(flag ? "Yes" : "No");
	return 0;
}