#include <bits/stdc++.h>

const int N = 5e4 + 5;

int n;
int a[N];
std::vector<int> to[N];

int vis[N][2];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) to[i].clear(), vis[i][0] = vis[i][1] = 0, a[i] = 0;
		for(int i = 1; i <= n * 3 / 2; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v), to[v].push_back(u); }
		if(n == 4) {
			puts("BWWW");
			continue;
		}
		bool flag = false;
		for(int u1 = 1; u1 <= n; u1++)
			for(int u2 : to[u1]) if(u1 < u2)
				for(int u3 : to[u2]) if(u3 != u1 && u3 != u2 && u3 > u1)
					for(int u4 : to[u3]) if(u4 != u1 && u4 != u2 && u4 != u3 && u4 > u2) {
						bool reach = false;
						for(int v : to[u4]) if(v == u1) reach = true;
						if(!reach) continue;
						int v1 = 0, v3 = 0;
						for(int v : to[u1]) if(v != u2 && v != u4) v1 = v;
						for(int v : to[u3]) if(v != u2 && v != u4) v3 = v;
						// printf("%d %d %d %d (%d %d)\n", u1, u2, u3, u4, v1, v3);
						if(!vis[v1][0] || vis[v1][0] == u1 || vis[v1][1] == u3) vis[v1][0] = u1, vis[v1][1] = u3;
						else { a[u1] = 0, a[u3] = 1, a[vis[v1][0]] = 1, a[vis[v1][1]] = 0, flag = true; goto end; }
						if(!vis[v3][0] || vis[v3][0] == u3 || vis[v3][1] == u1) vis[v3][0] = u3, vis[v3][1] = u1;
						else { a[u3] = 0, a[u1] = 1, a[vis[v3][0]] = 1, a[vis[v3][1]] = 0, flag = true; goto end; }
					}
		end:
		if(flag) {
			// for(int i = 1; i <= n; i++) printf("%d", a[i]);
			for(int i = 1; i <= n; i++) putchar(a[i] ? 'B' : 'W');
			puts("");
		} else puts("-1");
	}
	return 0;
}