#include <bits/stdc++.h>

typedef long long LL;

const int N = 20 + 5;
const int MAXS = (1 << 20) + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
LL dis[N][N];
int cnt[N];
bool useful[N];

LL f[MAXS];

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int main() {
#ifndef DEBUG
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = (i == j ? 0 : LLINF);
	for(int i = 1; i <= n; i++) fa[i] = i;
	LL sum = 0;
	for(int i = 1; i <= m; i++) {
		int u, v; LL w;
		scanf("%d%d%lld", &u, &v, &w);
		dis[u][v] = dis[v][u] = std::min(dis[u][v], w);
		cnt[u] ^= 1, cnt[v] ^= 1;
		sum += w;
		merge(u, v);
		useful[u] = useful[v] = true;
	}
	for(int i = 1; i <= n; i++) if(useful[i] && find(i) != find(1)) { puts("-1"); return 0; }
	for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
	int U = (1 << n) - 1;
	for(int s = 0; s <= U; s++) f[s] = LLINF;
	f[0] = 0;
	for(int s = 0; s <= U; s++)
		for(int i = 1; i <= n; i++) if(s >> (i - 1) & 1)
			for(int j = 1; j <= n; j++) if(j != i && (s >> (j - 1) & 1))
				f[s] = std::min(f[s], f[s ^ (1 << (i - 1)) ^ (1 << (j - 1))] + dis[i][j]);
	int s = 0;
	for(int i = 1; i <= n; i++) if(cnt[i]) s |= (1 << (i - 1));
	if(f[s] == LLINF) puts("-1");
	else printf("%lld\n", sum + f[s]);
	return 0;
}