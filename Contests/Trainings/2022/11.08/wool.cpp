#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

typedef long long LL;

const int N = 1000 + 5;
const int M = 2000 + 5;
const LL MOD = 998244353;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m, Q;
struct Edge { int to, nxt, w; } edge[M << 1];
int head[N], ek;
void add_edge(int u, int v, int w) { edge[ek] = (Edge){v, head[u], w}, head[u] = ek++; }

LL dis[N][N];
LL maxw[N];

struct Segment { LL k, b; } q[N];
bool operator<(Segment x, Segment y) { return x.k == y.k ? x.b > y.b : x.k < y.k; }
std::vector<int> stk;

bool compare(int i, int j, int k) {
	LL p1 = q[i].b - q[j].b, q1 = q[j].k - q[i].k;
	LL p2 = q[i].b - q[k].b, q2 = q[k].k - q[i].k;
	return p1 * q2 >= p2 * q1;
}
LL intersect(int i, int j) { return (q[i].b - q[j].b) / (q[j].k - q[i].k); }
LL sum(LL l, LL r) { return (l + r) * (r - l + 1) / 2 % MOD; }

LL mod(LL x) { return (x % MOD + MOD) % MOD; }

int main() {
#ifndef DEBUG
	// freopen("wool.in", "r", stdin);
	// freopen("wool.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1, stk.clear();
		scanf("%d%d%d", &n, &m, &Q);
		for(int i = 1; i <= n; i++) head[i] = 0, maxw[i] = 0;
		for(int i = 0; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = -LLINF;
		for(int i = 1; i <= m; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
		for(int u = 1; u <= n; u++) for(int i = head[u]; i; i = edge[i].nxt) maxw[u] = std::max(maxw[u], (LL)edge[i].w);
		dis[0][1] = 0;
		for(int i = 1; i <= n; i++)
			for(int u = 1; u <= n; u++)
				for(int j = head[u]; j; j = edge[j].nxt) {
					int v = edge[j].to;
					dis[i][u] = std::max(dis[i][u], dis[i - 1][v] + edge[j].w);
				}
		LL ans = 0;
		for(int i = 1; i <= std::min(n, Q); i++) {
			LL ret = -LLINF;
			for(int j = 1; j <= n; j++) ret = std::max(ret, dis[i][j]);
			(ans += mod(ret)) %= MOD;
		}
		for(int u = 1; u <= n; u++) {
			LL k = maxw[u], b = -LLINF;
			for(int i = 1; i <= n; i++) b = std::max(b, dis[i][u] - k * i);
			q[u] = {k, b};
		}
		std::sort(q + 1, q + n + 1);
		for(int i = 1; i <= n; i++) {
			if(i > 1 && q[i].k == q[i - 1].k) continue;
			while(stk.size() >= 2 && compare(stk.end()[-2], stk.back(), i)) stk.pop_back();
			stk.push_back(i);
		}
		int sz = stk.size();
		LL last = n + 1;
		for(int i = 0; i < sz; i++) {
			LL now = (i == sz - 1 ? Q : intersect(stk[i], stk[i + 1]));
			now = std::min(now, (LL)Q);
			if(last > now) continue;
			(ans += mod(q[stk[i]].k) * sum(last, now) % MOD + mod(q[stk[i]].b) * (now - last + 1) % MOD) %= MOD;
			last = now + 1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
