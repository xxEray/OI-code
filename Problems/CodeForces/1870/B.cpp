#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m;
int a[N], b[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
		int val = 0;
		for(int i = 1; i <= m; i++) val |= b[i];
		int v1 = 0, v2 = 0;
		for(int i = 1; i <= n; i++) v1 ^= a[i], v2 ^= a[i] | val;
		printf("%d %d\n", std::min(v1, v2), std::max(v1, v2));
	}
	return 0;
}