#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long LL;

const int N = 1e6 + 5;
const int INF = 0x3f3f3f3f;
const LL MOD = 1e9 + 7;

int n;
std::vector<int> to[N];

int dis[N];
void bfs(int st) {
	std::queue<int> q;
	for(int i = 1; i <= n; i++) dis[i] = INF;
	q.push(st), dis[st] = 0;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : to[u]) if(dis[v] == INF) {
			dis[v] = dis[u] + 1;
			q.push(v);
		}
	}
}

int disu[N], disv[N];
int cnt[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

int main() {
	scanf("%d", &n);
	if(n == 2) { puts("2"); return 0; }
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v), to[v].push_back(u); }
	bfs(1);
	int du = std::max_element(dis + 1, dis + n + 1) - dis;
	bfs(du);
	int dv = std::max_element(dis + 1, dis + n + 1) - dis;
	for(int i = 1; i <= n; i++) disu[i] = dis[i];
	int d = dis[dv];
	bfs(dv);
	for(int i = 1; i <= n; i++) disv[i] = dis[i];
	// printf("u = %d, v = %d, d = %d\n", du, dv, d);
	// for(int i = 1; i <= n; i++) printf("%d: disu = %d, disv = %d\n", i, disu[i], disv[i]);
	d++;
	int mx = 0;
	for(int i = 1; i <= n; i++) mx = std::max(mx, std::min(disu[i], disv[i]) + 1);
	for(int i = 1; i <= n; i++) cnt[std::max(disu[i], disv[i]) + 1]++;
	cnt[d] -= 2;
	LL ans = 0;
	(ans += (d - 1) * 2 % MOD * qpow(2, n - 2) % MOD) %= MOD;
	LL last = 0, ret = 0, tot = 0;
	for(int i = 1; i <= d; i++) {
		tot += cnt[i];
		if(i < mx) continue;
		ret = qpow(2, tot);
		// printf("%d: %lld -> ", i, ans);
		(ans += (i - 1) * 2 % MOD * (ret - last + MOD) % MOD) %= MOD;
		// printf("%lld\n", ans);
		last = ret;
	}
	printf("%lld\n", ans);
	return 0;
}