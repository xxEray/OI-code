#include <bits/stdc++.h>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

int f[N], g[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) f[i] = 0, g[i] = -INF;
		for(int i = 1; i <= n; i++)
			f[i] = std::max(g[a[i]] + i, f[i - 1]), g[a[i]] = std::max(g[a[i]], f[i - 1] - (i - 1));
		printf("%d\n", f[n]);
	}
	return 0;
}