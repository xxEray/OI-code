#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D, out[D], *O = out;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
	void wrtc(char c) { (O == out + D ? fwrite(O = out, 1, D, stdout) : 0), *O++ = c; }
	template<typename T> void write(T x, char ch = 0) {
		static char c[60]; int top = 0;
		if(x < 0) wrtc('-'), x = -x;
		do c[++top] = x % 10, x /= 10; while(x);
		while(top) wrtc(c[top--] + '0');
		if(ch) wrtc(ch);
	}
	void flush() { fwrite(out, 1, O - out, stdout); }
	struct Flusher { ~Flusher() { flush(); } } flusher;
}
using FIO::rdc;
using FIO::wrtc;
using FIO::write;
using FIO::read;

const int N = 250 + 5;
const int M = 30000 + 5;
const int FLOW_N = 2 * N + 2;
const int FLOW_M = N * N + 2 * N;
const int LINF = 0x3f3f3f3f;

int n, m, Q;

int vcost[N], vflow[N];
int vct[N];
int tot;

struct Dinic {
private:
	struct Edge { int to, nxt; int r, w; } edge[FLOW_M << 1];
	int head[FLOW_N], cur[FLOW_N], ek;
	int n, s, t;
	int dep[FLOW_N];
	bool inq[FLOW_N];
	std::queue<int> q;
	int flow, cost;
	void add_one_edge(int u, int v, int c, int w) { edge[ek] = (Edge){v, head[u], c, w}, head[u] = ek++; }
	bool spfa() {
		for(int i = 1; i <= n; i++) dep[i] = LINF, inq[i] = false;
		dep[s] = 1, q.push(s), inq[s] = true;
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			inq[u] = false;
			for(int i = head[u]; i; i = edge[i].nxt) if(dep[edge[i].to] > dep[u] + edge[i].w && edge[i].r) {
				int v = edge[i].to;
				dep[v] = dep[u] + edge[i].w;
				if(!inq[v]) q.push(v), inq[v] = true;
			}
		}
		return dep[t] != LINF;
	}
	int dfs(int u, int in, int now_cost) {
		if(u == t) {
			tot++;
			vct[tot] = now_cost;
			vflow[tot] = in;
			vcost[tot] = vct[tot] * in;
			return in;
		}
		inq[u] = true;
		int out = 0;
		for(int &i = cur[u]; i; i = edge[i].nxt) if(!inq[edge[i].to] && dep[edge[i].to] == dep[u] + edge[i].w && edge[i].r) {
			int v = edge[i].to;
			int ret = dfs(v, std::min(in, edge[i].r), now_cost + edge[i].w);
			if(!ret) continue;
			edge[i].r -= ret, edge[i ^ 1].r += ret;
			in -= ret, out += ret;
			cost += ret * edge[i].w;
			if(!in) return out;
		}
		if(!out) dep[u] = 0;
		inq[u] = false;
		return out;
	}
public:
	Dinic() : ek(2) {}
	void init(int n_) { n = n_; ek = 2; for(int i = 1; i <= n; i++) head[i] = 0; }
	void add_edge(int u, int v, int c, int w) { add_one_edge(u, v, c, w), add_one_edge(v, u, 0, -w); }
	std::pair<int, int> mincost(int s_, int t_) {
		s = s_, t = t_;
		flow = cost = 0;
		while(spfa()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i], inq[i] = false;
			flow += dfs(s, LINF, 0);
		}
		return {flow, cost};
	}
} dinic;

int e[N][N];

int main() {
	read(n), read(m), read(Q);
	int src = 2 * n + 1, dst = 2 * n + 2;
	dinic.init(2 * n + 2);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) e[i][j] = (i == j ? 0 : LINF);
	for(int i = 1; i <= m; i++) { int u, v; int w; read(u), read(v), read(w); e[u][v] = std::min(e[u][v], w); }
	for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) e[i][j] = std::min(e[i][j], e[i][k] + e[k][j]);
	for(int i = 1; i <= n; i++) dinic.add_edge(src, i, 1, 0), dinic.add_edge(i + n, dst, 1, 0);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(i != j && e[i][j] < LINF) dinic.add_edge(i, j + n, 1, e[i][j]);
	dinic.mincost(src, dst);
	for(int i = 1; i <= tot; i++) vcost[i] += vcost[i - 1], vflow[i] += vflow[i - 1];
	while(Q--) {
		int C;
		read(C);
		int i = std::upper_bound(vct + 1, vct + tot + 1, C) - vct - 1;
		write(n * C - vflow[i] * C + vcost[i], '\n');
	}
	return 0;
}