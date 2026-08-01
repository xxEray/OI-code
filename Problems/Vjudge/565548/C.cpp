#include <bits/stdc++.h>

const int N = 100000 + 5;
const int M = 200000 + 5;

int n, m;
std::vector<int> to[N], rev[N];

bool f[N][2], g[N][2];

int d[N][2];
bool vis[N][2];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v), rev[v].push_back(u); }
	for(int i = 1; i <= n; i++) d[i][0] = d[i][1] = to[i].size();
	std::queue<int> q;
	for(int i = 1; i <= n; i++) if(to[i].empty()) g[i][0] = g[i][1] = true, q.push(i), q.push(-i);
	while(!q.empty()) {
		int u = q.front(), t = 0;
		if(u < 0) t = 1, u = -u;
		q.pop();
		for(int v : rev[u]) if(!g[v][t ^ 1]) {
			d[v][t ^ 1]--;
			// printf("%d -> %d\n", u * (t ? -1 : 1), v * (t ? 1 : -1));
			if(t == 1) g[v][0] = true, q.push(v);
			else if(d[v][1] == 0) g[v][1] = true, q.push(-v);
		}
	}
	for(int i = 1; i <= n; i++) {
		d[i][0] = d[i][1] = 0;
		for(int j : to[i]) d[i][0] += g[j][1], d[i][1] += g[j][0];
	}
	for(int i = 1; i <= n; i++) {
		if(!d[i][0]) { f[i][0] = false, vis[i][0] = true; if(g[i][0]) q.push(i); }
		if(!d[i][1]) { f[i][1] = false, vis[i][1] = true; if(g[i][1]) q.push(-i); }
	}
	while(!q.empty()) {
		int u = q.front(), t = 0;
		if(u < 0) t = 1, u = -u;
		q.pop();
		// printf("(%d, %d) %d\n", u, t, f[u][t]);
		for(int v : rev[u]) if(g[v][t ^ 1]) {
			d[v][t ^ 1]--;
			if((!d[v][t ^ 1] || (!f[v][t ^ 1] && !f[u][t])) && !vis[v][t ^ 1]) {
				q.push(v * ((t ^ 1) ? -1 : 1));
				vis[v][t ^ 1] = true;
			}
			f[v][t ^ 1] |= !f[u][t];
		}
	}
	for(int i = 1; i <= n; i++) {
		if(!vis[i][0]) f[i][0] = false;
		if(!vis[i][1]) f[i][1] = true;
	}
	for(int i = 1; i <= n; i++) putchar(g[i][1] ? (f[i][1] ? 'W' : 'L') : 'D');
	puts("");
	for(int i = 1; i <= n; i++) putchar(g[i][0] ? (f[i][0] ? 'W' : 'L') : 'D');
	puts("");
	return 0;
}