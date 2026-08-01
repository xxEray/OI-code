#include <bits/stdc++.h>

const int N = 12 + 3;

int n, m;
int a[N];
int e[N][N];

int p[N], q[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); e[u][v] = e[v][u] = true; }
	q[1] = 1;
	for(int i = 1; i <= n - 2; i++) p[i] = i;
	int ans = 0x3f3f3f3f;
	do {
		for(int t = 2; t <= n; t++) {
			for(int i = 2; i <= t - 1; i++) q[i] = p[i - 1] + 1;
			q[t] = n;
			// printf("q: "); for(int i = 1; i <= t; i++) printf("%d ", q[i]); puts("");
			bool flag = true;
			for(int i = 1; i < t; i++) flag &= e[q[i]][q[i + 1]];
			if(!flag) continue;
			// puts("hi");
			int l = 0, r = 0, ret = 0;
			for(int i = 2; i <= t; i++) {
				int u = q[i];
				if(a[u] < l) l--, r++, ret++;
				else if(a[u] <= r) l = a[u], r++, ret++;
				else ret += a[u] - r, l = r = a[u];
			}
			ret += l;
			ans = std::min(ans, ret);
		}
	} while(std::next_permutation(p + 1, p + n - 1));
	printf("%d\n", ans);
	return 0;
}