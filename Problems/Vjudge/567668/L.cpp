#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n, K;
struct Edge { int to, nxt, w; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v, int w) { edge[ek] = (Edge){v, head[u], w}, head[u] = ek++; }

struct Convex {
	std::priority_queue<LL, std::vector<LL>, std::greater<LL>> vl, vr;
	LL vm, cl, cr;
	int sz;
	void clear() {
		while(!vl.empty()) vl.pop();
		while(!vr.empty()) vr.pop();
		vm = cl = cr = sz = 0;
	}
	void swap(Convex &rhs) {
		vl.swap(rhs.vl), vr.swap(rhs.vr);
		std::swap(vm, rhs.vm), std::swap(cl, rhs.cl), std::swap(cr, rhs.cr);
		std::swap(sz, rhs.sz);
	}
	void insert(LL x) {
		if(sz <= K / 2 || x > vm) vl.push(x - cl);
		else vr.push(x - cr);
		sz++;
		if((int)vl.size() > K / 2) {
			if(sz >= K / 2 + 2) vr.push(vm - cr);
			vm = vl.top() + cl, vl.pop();
		}
	}
};
void merge(Convex &p, Convex &q) {
	if(p.sz < q.sz) p.swap(q);
	while(!q.vl.empty()) p.insert(q.vl.top() + q.cl), q.vl.pop();
	if(q.sz > K / 2) p.insert(q.vm);
	while(!q.vr.empty()) p.insert(q.vr.top() + q.cr), q.vr.pop();
	while(p.sz > K) p.sz--, p.vr.pop();
}

Convex f[N];
void dfs(int u, int fa) {
	f[u].insert(0);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to; LL w = 2 * edge[i].w;
		dfs(v, u);
		f[v].cl += w, f[v].cr -= w;
		if(!(K & 1)) f[v].vm -= w;
		merge(f[u], f[v]);
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1;
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= n; i++) head[i] = 0;
		for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
		for(int i = 1; i <= n; i++) f[i].clear();
		dfs(1, 0);
		LL ans = f[1].vm;
		while(!f[1].vl.empty()) ans += f[1].vl.top() + f[1].cl, f[1].vl.pop();
		while(!f[1].vr.empty()) ans += f[1].vr.top() + f[1].cr, f[1].vr.pop();
		printf("%lld\n", ans);
	}
	return 0;
} /*
1
3 2
1 2 574927
2 3 406566
*/