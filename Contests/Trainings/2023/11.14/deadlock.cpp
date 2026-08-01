#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n, m;

int fa[N];
void init() { for(int i = 1; i <= n; i++) fa[i] = i; }
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int sz[N];

int main() {
#ifndef DEBUG
	freopen("deadlock.in", "r", stdin);
	freopen("deadlock.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		init();
		for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); merge(u, v), merge(v, u); /*if(T == 2) printf("%d %d\n", u, v);*/ }
		if(find(1) == find(n)) { puts("Deadlock"); continue; }
		for(int i = 1; i <= n; i++) sz[i] = 0;
		for(int i = 1; i <= n; i++) sz[find(i)]++;
		int cnt[2] = {};
		for(int i = 1; i <= n; i++) if(find(i) == i) cnt[sz[i] & 1]++;
//		printf("cnt = %d, %d; [1]=%d, [n]=%d\n", cnt[0], cnt[1], sz[find(1)] & 1, sz[find(n)] & 1);
		int tot = (((LL)n * (n - 1) / 2) & 1);
		if(~cnt[1] & 1) {
			int val = 0, win = (tot ^ (m & 1));
			if((~sz[find(1)] & 1) && (~sz[find(n)] & 1)) val = 0;
			else if((sz[find(1)] & 1) && (sz[find(n)] & 1)) val = 1;
			else val = !win;
			puts((tot ^ (m & 1) ^ val) ? "Cypher" : "Deadlock");
		} else {
			puts((tot ^ (m & 1)) ? "Cypher" : "Deadlock");
		}
	}
	return 0;
} /*
1
100 10
53 1
52 23
96 97
56 68
87 49
21 14
35 80
4 58
61 10
53 100
*/
