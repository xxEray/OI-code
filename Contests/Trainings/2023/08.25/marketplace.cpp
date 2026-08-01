#include <bits/stdc++.h>

const int N = 1e5 + 5;
const int M = 1e6 + 5;

int n, m;
int a[2][N], b[N];

bool vis[M], vis2[M];
int seq[2 * N];

int nxt[2 * N], last[M];
int ans[N];

int main() {
#ifndef DEBUG
	freopen("marketplace.in", "r", stdin);
	freopen("marketplace.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[0][i], &a[1][i]);
	int c = 0;
	for(int _ = 1; _ <= 2; _++)
		for(int i = 1; i <= n; i++) {
			if(b[i] == 0 && vis[a[0][i]]) b[i] = 1;
			if(b[i] <= 1 && !vis[a[b[i]][i]]) vis[a[b[i]][i]] = true, seq[++c] = n * b[i] + i;
			else goto _Break_;
		}
_Break_:
	// for(int i = 1; i <= c; i++) printf("%d ", seq[i]);
	// puts("");
	for(int i = c; i >= 1; i--) {
		if(seq[i] > n) nxt[i] = seq[i] - n;
		else {
			if(!vis2[a[1][seq[i]]] && vis[a[1][seq[i]]]) nxt[i] = seq[i];
			else nxt[i] = last[a[1][seq[i]]];
		}
		vis2[seq[i] > n ? a[1][seq[i] - n] : a[0][seq[i]]] = true;
		last[seq[i] > n ? a[1][seq[i] - n] : a[0][seq[i]]] = nxt[i];
	}
	// for(int i = 1; i <= n; i++) printf("nxt[%d] = %d\n", i, nxt[i]);
	for(int i = 1; i <= m; i++) ans[last[i] ? last[i] : (seq[c] + 1) % n]++;
	ans[n] += ans[0];
	for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}