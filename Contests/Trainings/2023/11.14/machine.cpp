#include <bits/stdc++.h>

typedef long long LL;

const int N = 100 + 5;
const int FLOW_N = 2 * N;
const int FLOW_M = N * N + 3 * N;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int mapping[300];

int m;
bool a[N];
char s[1005];
struct Edge { int to, nxt; } edge[N * N << 1];
int head[N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }

int vis[N], dfn[N], low[N], bl[N];
int stk[N], top;
int cc, time_stamp;
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	stk[top++] = u;
	vis[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(vis[v] == 0 && a[v]) tarjan(v), low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
	}
	if(dfn[u] == low[u]) {
		cc++;
		// printf("::: ");
		do {
			top--;
			// printf("%d ", stk[top]);
			bl[stk[top]] = cc;
			vis[stk[top]] = 2;
		} while(stk[top] != u);
		// puts("");
	}
}

struct Dinic {
	struct Edge { int to, nxt; LL r; } edge[FLOW_M << 1];
	int head[FLOW_N], cur[FLOW_N], ek;
	int n, s, t;
	int dep[FLOW_N];
	std::queue<int> q;
	void add_one_edge(int u, int v, LL c) { edge[ek] = (Edge){v, head[u], c}, head[u] = ek++; }
	bool bfs() {
		for(int i = 1; i <= n; i++) dep[i] = 0;
		dep[s] = 1, q.push(s);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int i = head[u]; i; i = edge[i].nxt) if(!dep[edge[i].to] && edge[i].r) {
				int v = edge[i].to;
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
		return dep[t];
	}
	LL dfs(int u, LL in) {
		if(u == t) return in;
		LL out = 0;
		for(int &i = cur[u]; i; i = edge[i].nxt) if(dep[u] + 1 == dep[edge[i].to] && edge[i].r) {
			int v = edge[i].to;
			LL ret = dfs(v, std::min(in, edge[i].r));
			if(!ret) continue;
			edge[i].r -= ret, edge[i ^ 1].r += ret;
			in -= ret, out += ret;
			if(!in) return out;
		}
		if(!out) dep[u] = 0;
		return out;
	}
public:
	Dinic() : ek(2) {}
	void init(int n_) { n = n_; ek = 2; for(int i = 1; i <= n; i++) head[i] = 0; }
	void add_edge(int u, int v, LL c) { /* printf("%d -> %d (c=%lld)\n", u, v, c);  */add_one_edge(u, v, c), add_one_edge(v, u, 0); }
	LL maxflow(int s_, int t_) {
		s = s_, t = t_;
		LL ret = 0;
		while(bfs()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			ret += dfs(s, LLINF);
		}
		return ret;
	}
	inline LL mincut(int s_, int t_) { return maxflow(s_, t_); } // mincut = maxflow
} dinic;

void get_mapping() {
	int c = 0;
	for(int i = '0'; i <= '9'; i++) mapping[i] = ++c;
	for(int i = 'a'; i <= 'z'; i++) mapping[i] = ++c;
	for(int i = 'A'; i <= 'Z'; i++) mapping[i] = ++c;
}

std::bitset<N> reach[N];
int sz[N], outd[N], outd2[N];

int main() {
	get_mapping();
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1, cc = 0, time_stamp = 0, top = 0;
		scanf("%s%d", s, &m);
		for(int i = 1; i <= 62; i++) a[i] = false, head[i] = 0, outd[i] = 0, sz[i] = 0;
		int len = strlen(s);
		for(int i = 0; i < len; i++) a[mapping[s[i]]] = true;
		for(int i = 1; i <= m; i++) {
			scanf("%s", s);
			add_edge(mapping[s[0]], mapping[s[1]]);
			// printf("%d %d\n", mapping[s[0]], mapping[s[1]]);
			outd[mapping[s[0]]]++;
		}
		for(int i = 1; i <= 62; i++) vis[i] = 0;
		for(int i = 1; i <= 62; i++) if(a[i] && !vis[i]) tarjan(i);
		// printf("cc = %d\n", cc);
		int cc2 = cc;
		for(int i = 1; i <= 62; i++) if(!a[i]) bl[i] = ++cc2;
		for(int i = 1; i <= 62; i++) if(a[i]) sz[bl[i]]++, outd2[bl[i]] = outd[i];
		// printf("cc2 = %d\n", cc2);
		for(int i = 1; i <= cc2; i++) reach[i].reset();
		for(int i = 1; i <= cc2; i++) reach[i][i] = true;
		for(int u = 1; u <= 62; u++) for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(bl[u] != bl[v]) reach[bl[u]][bl[v]] = true;
		}
		for(int k = 1; k <= cc2; k++) for(int i = 1; i <= cc2; i++) if(reach[i][k]) reach[i] |= reach[k];
		dinic.init(cc + cc2 + 2);
		int src = cc + cc2 + 1, dst = cc + cc2 + 2;
		for(int i = 1; i <= cc; i++) for(int j = 1; j <= cc2; j++) if(i != j && reach[i][j]) dinic.add_edge(i, cc + j, 1);
		for(int i = 1; i <= cc; i++) if(sz[i] == 1 && outd2[i] == 0) dinic.add_edge(i, cc + i, 1);
		for(int i = 1; i <= cc; i++) dinic.add_edge(src, i, 1);
		for(int i = 1; i <= cc2; i++) dinic.add_edge(cc + i, dst, 1);
		int ans = 0;
		for(int i = 1; i <= 62; i++) ans += a[i];
		ans -= cc - dinic.maxflow(src, dst);
		// for(int i = 1; i <= cc; i++) ok[i] = false;
		// for(int i = dinic.head[src]; i; i = dinic.edge[i].nxt) if(dinic.edge[i ^ 1].r) ok[dinic.edge[i].to] = true;
		// for(int i = 1; i <= 62; i++) if(a[i] && !ok[bl[i]] && outd[i] == 0) ans++;
		printf("%d\n", ans);
	}
	return 0;
} /*
1
UWw 3
uR Ze Uw
*/