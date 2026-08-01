#include <bits/stdc++.h>

const int N = 3e5 + 5;

int n, m;
struct Node { int atk, def, id; } a[N], b[N];

std::vector<int> to[N * 2];
int d[N * 2], f[N * 2];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i].atk), a[i].id = i;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i].def);
		scanf("%d", &m);
		for(int i = 1; i <= m; i++) scanf("%d", &b[i].atk), b[i].id = i;
		for(int i = 1; i <= m; i++) scanf("%d", &b[i].def);
		for(int i = 1; i <= n + m; i++) to[i].clear();
		std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.def > y.def; });
		std::sort(b + 1, b + m + 1, [&](Node x, Node y) { return x.atk > y.atk; });
		int mx = 0;
		for(int i = 1, j = 0; i <= n; i++) {
			while(j < m && b[j + 1].atk > a[i].def) {
				j++;
				if(b[j].def > b[mx].def) mx = j;
			}
			if(mx) to[b[mx].id + n].push_back(a[i].id);
		}
		std::sort(b + 1, b + m + 1, [&](Node x, Node y) { return x.def > y.def; });
		std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.atk > y.atk; });
		mx = 0;
		for(int i = 1, j = 0; i <= m; i++) {
			while(j < n && a[j + 1].atk > b[i].def) {
				j++;
				if(a[j].def > a[mx].def) mx = j;
			}
			if(mx) to[a[mx].id].push_back(b[i].id + n);
		}
		// for(int i = 1; i <= n + m; i++) for(int j : to[i]) printf("%d -> %d\n", i, j);
		for(int i = 1; i <= n + m; i++) d[i] = f[i] = 0;
		for(int i = 1; i <= n + m; i++) for(int j : to[i]) d[j]++;
		std::vector<int> q;
		for(int i = 1; i <= n + m; i++) if(!d[i]) q.push_back(i), f[i] = (i <= n ? 1 : -1);
		while(!q.empty()) {
			int u = q.back();
			q.pop_back();
			for(int v : to[u]) if(!f[v]) {
				d[v]--;
				if((v <= n && f[u] == 1) || (v > n && f[u] == -1)) q.push_back(v), f[v] = f[u];
				else if(!d[v]) q.push_back(v), f[v] = f[u];
			}
		}
		int cnt[3] = {};
		for(int i = 1; i <= n; i++) cnt[f[i] + 1]++;
		printf("%d %d %d\n", cnt[2], cnt[1], cnt[0]);
	}
	return 0;
}