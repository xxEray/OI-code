#include <bits/stdc++.h>

const int N = 1e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { 
	static int k = 1;
	edge[k] = (Edge){v, head[u]};
	head[u] = k++;
}

Edge rev[N << 1];
int revhead[N];
void add_rev(int u, int v) {
	static int k = 1;
	rev[k] = (Edge){v, revhead[u]};
	revhead[u] = k++;
}
int n, m;

int in[N], cpin[N];
int topo[N], cnttopo;
int stk[N], topstk;
void toposort() {
	for(int i = 1; i <= n; i++)
		if(in[i] == 0) stk[topstk++] = i, topo[++cnttopo] = i;
	while(topstk) {
		int u = stk[--topstk];
		for(int i = revhead[u]; i; i = rev[i].nxt) {
			in[rev[i].to]--;
			if(in[rev[i].to] == 0) stk[topstk++] = rev[i].to, topo[++cnttopo] = rev[i].to;
		}
	}
}

bool vis[N];
long long ans[N][2];

long long gcd(long long x, long long y) { return x % y ? gcd(y, x % y) : y; }

int main() {
#ifndef DEBUG
	std::freopen("water.in", "r", stdin);
	std::freopen("water.out", "w", stdout);
#endif
	std::scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		int x;
		std::scanf("%d", &x);
		while(x--) {
			int y;
			std::scanf("%d", &y);
			add_edge(y, i);
			add_rev(i, y);
			in[y]++, cpin[i]++;
		}
	}
	toposort();
//	for(int i = 1; i <= n; i++) std::printf("topo[%d] = %d\n", i, topo[i]);
	for(int i = 1; i <= n; i++) ans[i][0] = (i <= m), ans[i][1] = 1; 
	for(int i = 1; i <= n; i++) {
		int u = topo[i];
		vis[u] = true;
		for(int j = head[u]; j; j = edge[j].nxt) {
			// ans[edge[j].to] += ans[u]
//			std::printf("%lld/%lld + %lld/%lld = ", ans[edge[j].to][0], ans[edge[j].to][1], ans[u][0], ans[u][1]);
			long long g = gcd(ans[edge[j].to][1], ans[u][1]);
			ans[u][0] *= ans[edge[j].to][1] / g;
			ans[u][1] *= ans[edge[j].to][1] / g;
			ans[u][0] += ans[edge[j].to][0] * (ans[u][1] / ans[edge[j].to][1]);
			g = gcd(ans[u][0], ans[u][1]);
			ans[u][0] /= g, ans[u][1] /= g;
//			std::printf("%lld/%lld\n", ans[u][0], ans[u][1]);
		}
		if(cpin[u]) {
			ans[u][1] *= cpin[u];
			long long g = gcd(ans[u][0], ans[u][1]);
			ans[u][0] /= g, ans[u][1] /= g;
		}
	}
//	for(int u = 1; u <= n; u++) std::printf("ans[%d] = %lld/%lld\n", u, ans[u][0], ans[u][1]);
	for(int i = 1; i <= n; i++)
		if(cpin[i] == 0)
			std::printf("%lld %lld\n", ans[i][0], ans[i][1]);
	return 0;
} /*
5 1
3 2 3 5
2 4 5
2 5 4
0
0
*/
