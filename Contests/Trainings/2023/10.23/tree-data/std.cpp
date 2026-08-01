#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
struct Edge { int to, nxt, id; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int id) { static int k = 2; edge[k] = (Edge){v, head[u], id}, head[u] = k++; }

struct BIT {
	LL t[N];
	void add(int x, LL v) { x++; while(x <= n + 1) t[x] += v, x += x & -x; }
	LL query(int r) { LL ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	LL query(int l, int r) { return l > r ? 0 : query(r + 1) - query(l); }
} bitc, bitmx, bitsc;

LL sumall, sum1, sum2;
LL sum[N], sz[N], mx[N], sc[N];
void dfs(int i) {
	// printf("dfs %d\n", i);
	int u = edge[i].to;
	for(int j = head[u]; j; j = edge[j].nxt) if(j != (i ^ 1)) {
		int v = edge[j].to;
		dfs(j);
		sum[u] += sum[v];
		sz[u] += sz[v] + 1;
		if(sz[v] + 1 > mx[u]) sc[u] = mx[u], mx[u] = sz[v] + 1;
		else if(sz[v] + 1 > sc[u]) sc[u] = sz[v] + 1;
	}
	if(mx[u]) sum[u] += sz[u] - mx[u] + 1;
}

LL out[N];
LL cnt;
void dfs2(int i) {
	cnt++;
	int u = edge[i].to;
	for(int j = head[u]; j; j = edge[j].nxt) if(j != (i ^ 1)) {
		int v = edge[j].to;
		if(!sc[u]) out[edge[j].id] = sumall - sum[u] - (cnt - 1) * (sz[v] + 1) - bitmx.query(sz[v] + 2, n) + bitc.query(sz[v] + 2, n) * (sz[v] + 1) - bitsc.query(0, sz[v] + 1) + std::min(sum1 - sz[v] - 1, sum2);
		if(sz[v] + 1 == mx[u]) sumall += mx[u], bitc.add(mx[u] - sc[u], 1), bitmx.add(mx[u] - sc[u], mx[u]), bitsc.add(mx[u] - sc[u], sc[u]);
		if(sc[u]) out[edge[j].id] = sumall - sum[v] - cnt * (sz[v] + 1) - bitmx.query(sz[v] + 2, n) + bitc.query(sz[v] + 2, n) * (sz[v] + 1) - bitsc.query(0, sz[v] + 1) + std::min(sum1 - sz[v] - 1, sum2);
		dfs2(j);
		if(sz[v] + 1 == mx[u]) sumall -= mx[u], bitc.add(mx[u] - sc[u], -1), bitmx.add(mx[u] - sc[u], -mx[u]), bitsc.add(mx[u] - sc[u], -sc[u]);
	}
	cnt--;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v, i), add_edge(v, u, i); }
	dfs(2), dfs(3);
	sumall = sum[edge[2].to] + sum[edge[3].to];
	// for(int i = 1; i <= n; i++) printf("%d: sz=%lld, sum=%lld, mx=%lld, sc=%lld\n", i, sz[i], sum[i], mx[i], sc[i]);
	sum1 = sz[edge[2].to], sum2 = sz[edge[3].to], dfs2(2);
	sum1 = sz[edge[3].to], sum2 = sz[edge[2].to], dfs2(3);
	for(int i = 2; i < n; i++) printf("%lld\n", out[i]);
	return 0;
}