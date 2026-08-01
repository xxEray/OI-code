#include <bits/stdc++.h>

const int N = 200 + 5;
const int M = N * N;
const int FLOW_N = N + 4;
const int FLOW_M = N * N * 2 + N + 2;
const double eps = 1e-8;
const double FINF = 1e18;

int n, m;
struct GraphEdge { int u, v; double w; } e[M];
double fe[M];
double V, A;

struct Dinic {
	struct Edge { int to, nxt; double r; } edge[FLOW_M << 1];
	int head[FLOW_N], cur[FLOW_N], ek;
	int n, s, t;
	int dep[FLOW_N];
	std::queue<int> q;
	void add_one_edge(int u, int v, double c) { edge[ek] = (Edge){v, head[u], c}, head[u] = ek++; }
	bool bfs() {
		for(int i = 1; i <= n; i++) dep[i] = 0;
		dep[s] = 1, q.push(s);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int i = head[u]; i; i = edge[i].nxt) if(!dep[edge[i].to] && edge[i].r > eps) {
				int v = edge[i].to;
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
		return dep[t];
	}
	double dfs(int u, double in) {
		if(u == t) return in;
		double out = 0;
		for(int &i = cur[u]; i; i = edge[i].nxt) if(dep[u] + 1 == dep[edge[i].to] && edge[i].r > eps) {
			int v = edge[i].to;
			double ret = dfs(v, std::min(in, edge[i].r));
			if(ret < eps) continue;
			edge[i].r -= ret, edge[i ^ 1].r += ret;
			in -= ret, out += ret;
			if(in < eps) return out;
		}
		if(out < eps) dep[u] = 0;
		return out;
	}
	Dinic() : ek(2) {}
	void init(int n_) { n = n_; ek = 2; for(int i = 1; i <= n; i++) head[i] = 0; }
	void add_edge(int u, int v, double c) { add_one_edge(u, v, c), add_one_edge(v, u, 0); }
	double maxflow(int s_, int t_) {
		s = s_, t = t_;
		double ret = 0;
		while(bfs()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			ret += dfs(s, FINF);
		}
		return ret;
	}
} dinic;

int main() {
	scanf("%d%d%lf%lf", &n, &m, &V, &A);
	for(int i = 1; i <= m; i++) scanf("%d%d%lf", &e[i].u, &e[i].v, &e[i].w);
	int src = n + 1, dst = n + 2;
	dinic.init(n + 2);
	for(int i = 1; i <= m; i++) dinic.add_edge(e[i].u, e[i].v, e[i].w), dinic.add_edge(e[i].v, e[i].u, e[i].w);
	dinic.add_edge(src, 2, FINF), dinic.add_edge(src, 1, FINF), dinic.add_edge(3, dst, FINF);
	double flow = dinic.maxflow(src, dst);
	dinic.init(n + 2);
	for(int i = 1; i <= m; i++) dinic.add_edge(e[i].u, e[i].v, e[i].w), dinic.add_edge(e[i].v, e[i].u, e[i].w);
	dinic.add_edge(src, 1, FINF), dinic.add_edge(3, dst, FINF);
	double Fmax = dinic.maxflow(src, dst);
	dinic.init(n + 2);
	for(int i = 1; i <= m; i++) dinic.add_edge(e[i].u, e[i].v, e[i].w), dinic.add_edge(e[i].v, e[i].u, e[i].w);
	dinic.add_edge(src, 2, FINF), dinic.add_edge(3, dst, FINF);
	double Wmax = dinic.maxflow(src, dst);
	double F = std::max(std::min(A * flow, Fmax), flow - Wmax);
	double W = flow - F;
	// printf("flow = %.3f, Fmax = %.3f, Wmax = %.3f, F = %.3f\n", flow, Fmax, Wmax, F);
	dinic.init(n + 2);
	for(int i = 1; i <= m; i++) dinic.add_edge(e[i].u, e[i].v, e[i].w), dinic.add_edge(e[i].v, e[i].u, e[i].w);
	dinic.add_edge(src, 2, W), dinic.add_edge(src, 1, F), dinic.add_edge(3, dst, FINF);
	double ff1 = dinic.maxflow(src, dst);
	assert(std::abs(ff1 - flow) <= eps);
	for(int i = 2; i <= 4 * m + 1; i += 4) fe[(i + 2) / 4] = dinic.edge[i ^ 1].r - dinic.edge[(i + 2) ^ 1].r;
	// for(int i = 1; i <= m; i++) printf("(%d, %d) %.4f\n", e[i].u, e[i].v, fe[i]);
	dinic.init(n + 2);
	for(int i = 1; i <= m; i++) dinic.add_edge(e[i].u, e[i].v, std::max(fe[i], 0.)), dinic.add_edge(e[i].v, e[i].u, std::max(-fe[i], 0.));
	dinic.add_edge(src, 1, F), dinic.add_edge(3, dst, FINF);
	double ff2 = dinic.maxflow(src, dst);
	// printf("ff = %.3f\n", ff2);
	assert(std::abs(ff2 - F) <= eps);
	for(int i = 2; i <= 4 * m + 1; i += 4) {
		double f = dinic.edge[i ^ 1].r - dinic.edge[(i + 2) ^ 1].r;
		printf("%.11f %.11f\n", f / V, fe[(i + 2) / 4] - f);
	}
	printf("%.11f\n", pow(F / V, A) * pow(flow - F, 1 - A));
	return 0;
}