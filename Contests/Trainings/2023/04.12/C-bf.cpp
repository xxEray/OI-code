#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e6 + 5;
const int INF = 0x3f3f3f3f;
const LL MOD = 1e9 + 7;

int n;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int d[N];

int dep[N];
void dfs(int u, int fa) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL C(LL x, LL y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }

namespace Subtask1 {
	const int N = 10 + 5;
	int dis[N][N];
	void main() {
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = (i == j ? 0 : INF);
		for(int u = 1; u <= n; u++)
			for(int i = head[u]; i; i = edge[i].nxt)
				dis[u][edge[i].to] = 1;
		for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
			dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
		int U = (1 << n) - 1;
		LL ans = 0;
		for(int s = 0; s <= U; s++) {
			int ret = 0;
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= n; j++) if((s >> (i - 1) & 1) == (s >> (j - 1) & 1))
					ret = std::max(ret, dis[i][j]);
			ans += ret;
		}
		printf("%lld\n", ans % MOD);
	}
}

namespace Subtask2 {
	void main() {
		if(n == 3) { puts("12"); return; }
		LL ans = 0;
		for(int i = (n + 1) / 2 + 1; i < n; i++) (ans += (i - 1) * 2 * qpow(2, 2 * i - n - 2) * 3) %= MOD;
		if(~n & 1) (ans += 2 * (n / 2 - 1)) %= MOD;
		else (ans += 4 * (n / 2)) %= MOD;
		(ans += (n - 1) * 2 % MOD * qpow(2, n - 2)) %= MOD;
		printf("%lld\n", ans);
	}
}

namespace Subtask3 {
	void main() {
		if(n == 3) { puts("12"); return; }
		printf("%lld\n", 2 * qpow(2, n) % MOD);
	}
}

namespace Subtask4 {
	void main() {
		int mx = 0;
		for(int i = 1; i <= n; i++) mx = std::max(mx, dep[i]);
		printf("%lld\n", mx * qpow(2, n) % MOD);
	}
}

int main() {
	scanf("%d", &n);
	if(n == 2) { puts("2"); return 0; }
	bool isA = true, isB = true, isC = true;
	for(int i = 1; i < n; i++) {
		int u, v; scanf("%d%d", &u, &v);
		isA &= (u == i && v == i + 1);
		add_edge(u, v), add_edge(v, u);
		d[u]++, d[v]++;
	}
	isB &= d[1] == n - 1;
	isC &= d[1] > 2;
	dfs(1, 0);
	int tmp = -1;
	for(int i = 2; i <= n; i++) isC &= (d[i] <= 2 && (dep[i] == 2 || (tmp == -1 ? (tmp = dep[i], true) : tmp == dep[i])));
	fac[0] = 1;
	for(int i = 1; i <= 1000000; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[1000000] = qpow(fac[1000000], MOD - 2);
	for(int i = 1000000; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
	if(n <= 10) Subtask1::main();
	else if(isA) Subtask2::main();
	else if(isB) Subtask3::main();
	else if(isC) Subtask4::main();
	return 0;
}