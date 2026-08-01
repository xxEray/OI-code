#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
struct Edge { int to, nxt; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }

int sz[N];
void dfs1(int u, int fa) {
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs1(v, u);
		sz[u] += sz[v];
	}
}
bool out[N];
void dfs(int u, int fa, int l, int r) {
	assert((l & 1) == (r & 1));
	int sum = 0, mx = 0, scmx = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		sum += sz[v];
		if(sz[v] > mx) scmx = mx, mx = sz[v];
		else if(sz[v] > scmx) scmx = sz[v];
	}
	int vr = std::min(r, mx), vl = std::max(l, mx);
	if((vr & 1) != (r & 1)) vr--;
	if((vl & 1) != (l & 1)) vl++;
	if(l <= mx && vr >= l && 2 * mx <= sum + vr) out[u] |= ((sum + vr) & 1) == 0;
	if(r > mx && vl <= r && vl <= sum) out[u] |= ((sum + vl) & 1) == 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		int x = (sz[v] == mx ? scmx : mx), s = sum - sz[v];
		vr = std::min(r, x), vl = std::max(l, x);
		if((vr & 1) != (r & 1)) vr--;
		if((vl & 1) != (l & 1)) vl++;
		int ll = INF, rr = r + s;
		if(l <= x) {
			if(vr >= l && 2 * x <= s + vr) ll = std::min(ll, (s + vr) & 1);
			if(2 * x > s + l) ll = std::min(ll, 2 * x <= s + vr ? ((2 * x - (s + l)) & 1) : 2 * x - (s + vr));
		}
		if(r > x) {
			if(vl <= r && vl <= s) ll = std::min(ll, (s + vl) & 1);
			if(r > s) ll = std::min(ll, vl <= s ? ((r - s) & 1) : vl - s);
		}
		dfs(v, u, ll, rr);
	}
}

int main() {
	int W, T; scanf("%d%d", &W, &T);
	while(T--) {
		ek = 1;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) head[i] = 0;
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v); }
		for(int i = 1; i <= n; i++) out[i] = false;
		dfs1(1, 0);
		dfs(1, 0, 0, 0);
		if(W == 3) printf("%d\n", out[1]);
		else {
			for(int i = 1; i <= n; i++) printf("%d", out[i]);
			puts("");
		}
	}
	return 0;
} /*
0 1
15
1 2
2 3
3 4
2 5
1 6
1 7
7 8
2 9
7 10
4 11
10 12
8 13
5 14
1 15
*/