#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, m;
int e[N][2];

int cu, cv;
int d[N];

struct DSU {
	int fa[N];
	void init() { for(int i = 1; i <= n; i++) fa[i] = i; }
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }
} dsu;

bool oku[N], okv[N], eu[N], ev[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); d[u]++, d[v]++, e[i][0] = u, e[i][1] = v; }
	bool flag = true, ok = false;
	int sum = 0;
	for(int i = 1; i <= n; i++) flag &= (d[i] % 2 == 0), sum += d[i] - 2, ok |= (d[i] >= 6);
	if(!flag || sum <= 2) { puts("No"); return 0; }
	else if(sum >= 6 || ok) { puts("Yes"); return 0; }
	// Now, sum = 4, ok = false
	for(int i = 1; i <= n; i++) if(d[i] == 4) (cu ? cv : cu) = i;
	dsu.init();
	for(int i = 1; i <= m; i++)
		if(e[i][0] == cu || e[i][1] == cu) eu[e[i][0] == cu ? e[i][1] : e[i][0]] = true;
		else if(e[i][0] == cv || e[i][1] == cv) ev[e[i][0] == cv ? e[i][1] : e[i][0]] = true;
		else dsu.merge(e[i][0], e[i][1]);
	// for(int i = 1; i <= n; i++) printf("%d: eu = %d, ev = %d, leader = %d\n", i, eu[i], ev[i], dsu.find(i));
	bool flagu = false, flagv = false;
	for(int i = 1; i <= n; i++) oku[dsu.find(i)] = okv[dsu.find(i)] = true;
	for(int i = 1; i <= n; i++) oku[dsu.find(i)] &= !ev[i], okv[dsu.find(i)] &= !eu[i];
	for(int i = 1; i <= n; i++) if(i != cu && i != cv) flagu |= oku[i], flagv |= okv[i];
	puts(flagu && flagv ? "Yes" : "No");
	return 0;
} /*
7 9
1 2
1 3
2 3
2 4
3 4
2 5
3 7
5 6
6 7
*/