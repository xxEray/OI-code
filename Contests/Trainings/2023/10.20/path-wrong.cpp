#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n, m;
struct Edge { int to, nxt; LL w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

struct XorBase {
	LL t[70];
	XorBase() { memset(t, 0, sizeof(t)); }
	void join(const XorBase &rhs) {
		for(int i = 0; i <= 63; i++) if(rhs.t[i]) insert(rhs.t[i]);
	}
	void insert(LL x) {
		for(int i = 63; i >= 0; i--) if(x >> i & 1) {
			if(t[i]) x ^= t[i];
			else { t[i] = x; break; }
		}
	}
	void xorall(LL x) {
		std::vector<int> vct;
		for(int i = 0; i <= 63; i++) if(t[i]) vct.push_back(t[i] ^ x);
		vct.push_back(x);
		for(int i = 0; i <= 63; i++) t[i] = 0;
		for(LL y : vct)
			for(int i = 63; i >= 0; i--) if(y >> i & 1) {
				if(t[i]) y ^= t[i];
				else { t[i] = y; break; }
			}
	}
	LL getmax() const { 
		LL x = 0;
		for(int i = 63; i >= 0; i--)
			if(t[i] && (~x >> i & 1))
				x ^= t[i];
		return x;
	}
} f[N];

//bool vis[N];
//int dep[N];
//void predfs(int u, int fa) {
//	vis[u] = true;
//	dep[u] = dep[fa] + 1;
//	for(int i = head[u]; i; i = edge[i].nxt) {
//		int v = edge[i].to;
//		if(!vis[v]) predfs(v, u); // , printf("%d -> %d\n", u, v);
//	}
//}
//void dfs(int u, int fa) {
//	vis[u] = true;
//	for(int i = head[u]; i; i = edge[i].nxt) {
//		int v = edge[i].to; LL w = edge[i].w;
//		if(dep[v] == dep[u] + 1) {
//			f[v] = f[u];
//			f[v].xorall(w);
//		}
//	}
//	for(int i = head[u]; i; i = edge[i].nxt) {
//		int v = edge[i].to; LL w = edge[i].w;
//		if(dep[v] > dep[u] + 1) {
//			auto tmp = f[u];
//			tmp.xorall(w);
//			f[v].join(tmp);
//		}
//	}
//	for(int i = head[u]; i; i = edge[i].nxt) {
//		int v = edge[i].to;
//		if(dep[v] == dep[u] + 1) dfs(v, u);
//	}
//}

int main() {
#ifndef DEBUG
	freopen("path.in", "r", stdin);
	freopen("path.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	XorBase ans;
	for(int i = 1; i <= m; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); ans.insert(w); }
//	predfs(1, 0);
//	for(int i = 1; i <= n; i++) vis[i] = false;
//	dfs(1, 0);
//	for(int i = 1; i <= n; i++) {
//		printf("%d: ", i);
//		for(int j = 0; j <= 63; j++)
//			if(f[i].t[j]) printf("%lld ", f[i].t[j]);
//		puts("");
//	}
//	LL ans = 0;
//	for(int i = 1; i <= n; i++) ans = std::max(ans, f[i].getmax());
//	printf("%lld\n", ans);
	printf("%lld\n", ans.getmax());
	return 0;
} /*
5 7
1 2 2
1 3 2
2 4 1
2 5 1
4 5 3
5 3 4
4 3 2
*/
