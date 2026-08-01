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

const int N = 300 + 5;
const int FLOW_N = N * 2 + 2;
const int FLOW_M = N * N + 2 * N;
const int INF = 0x3f3f3f3f;

struct Dinic {
	struct Edge { int to, nxt; int r; } edge[FLOW_M << 1];
	int head[FLOW_N], cur[FLOW_N], ek;
	int n, s, t;
	int dep[FLOW_N];
	std::queue<int> q;
	void add_one_edge(int u, int v, int c) { edge[ek] = (Edge){v, head[u], c}, head[u] = ek++; }
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
	int dfs(int u, int in) {
		if(u == t) return in;
		int out = 0;
		for(int &i = cur[u]; i; i = edge[i].nxt) if(dep[u] + 1 == dep[edge[i].to] && edge[i].r) {
			int v = edge[i].to;
			int ret = dfs(v, std::min(in, edge[i].r));
			if(!ret) continue;
			edge[i].r -= ret, edge[i ^ 1].r += ret;
			in -= ret, out += ret;
			if(!in) return out;
		}
		if(!out) dep[u] = 0;
		return out;
	}
	Dinic() : ek(2) {}
	void init(int n_) { n = n_; ek = 2; for(int i = 1; i <= n; i++) head[i] = 0; }
	void add_edge(int u, int v, int c) { add_one_edge(u, v, c), add_one_edge(v, u, 0); }
	int maxflow(int s_, int t_) {
		s = s_, t = t_;
		int ret = 0;
		while(bfs()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			ret += dfs(s, INF);
		}
		return ret;
	}
	inline int mincut(int s_, int t_) { return maxflow(s_, t_); } // mincut = maxflow
} dinic;

int n, m, Q;
int d1[N], d2[N];

int main() {
#ifndef DEBUG
	freopen("trade.in", "r", stdin);
	freopen("trade.out", "w", stdout);
#endif
	read(n), read(m), read(Q);
	int src = n + m + 1, dst = n + m + 2;
	dinic.init(n + m + 2);
	// mf_graph<int> dinic(n + m + 3);
	for(int i = 1; i <= Q; i++) { int u, v; read(u), read(v); dinic.add_edge(u, v + n, 1); d1[u]++, d2[v]++; }
	for(int i = 1; i <= n; i++)
		if(d1[i] < 2) { wrtc('-'), wrtc('1'), wrtc('\n'); return 0; }
		else dinic.add_edge(src, i, d1[i] - 2);
	for(int i = 1; i <= m; i++)
		if(d2[i] < 2) { wrtc('-'), wrtc('1'), wrtc('\n'); return 0; }
		else dinic.add_edge(i + n, dst, d2[i] - 2);
	int ans = Q - dinic.maxflow(src, dst);
	// int ans = Q - dinic.flow(src, dst);
	write(ans, '\n');
	for(int i = 2; i <= 2 * Q; i += 2) if(!dinic.edge[i ^ 1].r) write(i >> 1, ' ');
	// for(int i = 0; i < Q; i++) if(!dinic.get_edge(i).flow) write(i + 1, ' ');
	wrtc('\n');
	return 0;
}