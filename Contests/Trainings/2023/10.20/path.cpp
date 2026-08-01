#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n, m;

struct XorBase {
	LL t[70];
	void insert(LL x) {
		for(int i = 63; i >= 0; i--) if(x >> i & 1) {
			if(t[i]) x ^= t[i];
			else { t[i] = x; break; }
		}
	}
	LL getmax(LL x) const { 
		for(int i = 63; i >= 0; i--)
			if(t[i] && (~x >> i & 1))
				x ^= t[i];
		return x;
	}
};

namespace Solve_bf {
	struct Edge { int to, nxt; LL w; bool disabled; } edge[N << 1];
	int head[N];
	void add_edge(int u, int v, LL w) { static int k = 2; edge[k] = (Edge){v, head[u], w, false}, head[u] = k++; }
	
	LL out[N];
	void dfs(int u, LL val) {
		out[u] = std::max(out[u], val);
		for(int i = head[u]; i; i = edge[i].nxt) if(!edge[i].disabled) {
			edge[i].disabled = edge[i ^ 1].disabled = true;
			dfs(edge[i].to, val ^ edge[i].w);
			edge[i].disabled = edge[i ^ 1].disabled = false;
		}
	}

	void main() {
		for(int i = 1; i <= m; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
		std::vector<LL> vct;
		XorBase t;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) out[j] = 0;
			dfs(i, 0);
			for(int j = 1; j <= n; j++) vct.push_back(out[j]);
			t.insert(out[i]);
		}
		LL ans = t.getmax(0);
		for(LL x : vct) ans = std::max(ans, t.getmax(x));
		printf("%lld\n", ans);
	}

}

int main() {
#ifndef DEBUG
	freopen("path.in", "r", stdin);
	freopen("path.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	if(n <= 10 && m <= 20) { Solve_bf::main(); return 0; }
	XorBase ans;
	for(int i = 1; i <= m; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); ans.insert(w); }
	printf("%lld\n", ans.getmax(0));
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
