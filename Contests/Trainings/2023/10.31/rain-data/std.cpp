#include <bits/stdc++.h>

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

typedef long long LL;

const int N = 2500 + 5;
const int M = N * N;
const int INF = 0x3f3f3f3f;

int n, m, K;
int a[N], b[N];
bool e[N][N];

std::vector<int> ta[2 * N], tb[2 * N];

struct Edge { int to, nxt, r; } edge[(M + N * 4) << 1];
int head[N * 2], cur[N * 2], ek;
void add_one_edge(int u, int v, int c) { edge[ek] = (Edge){v, head[u], c}, head[u] = ek++; }
void add_edge(int u, int v, int c) { add_one_edge(u, v, c), add_one_edge(v, u, 0); }
int dep[N * 2];
int dinic(int cn, int s, int t) {
	auto bfs = [&]() -> bool {
		std::queue<int> q;
		for(int i = 1; i <= cn; i++) dep[i] = 0;
		dep[s] = 1, q.push(s);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].r && !dep[edge[i].to]) {
				int v = edge[i].to;
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
		for(int i = 1; i <= cn; i++) cur[i] = head[i];
		return dep[t];
	};
	std::function<int(int, int)> dfs = [&](int u, int in) -> int {
		if(u == t) return in;
		int out = 0;
		for(int &i = cur[u]; i; i = edge[i].nxt) if(edge[i].r && dep[edge[i].to] == dep[u] + 1) {
			int v = edge[i].to;
			int val = dfs(v, std::min(in, edge[i].r));
			in -= val, out += val;
			edge[i].r -= val, edge[i ^ 1].r += val;
			if(!in) return out;
		}
		if(!out) dep[u] = 0;
		return out;
	};
	int flow = 0;
	while(bfs()) flow += dfs(s, INF);
	return flow;
}

int main() {
	read(n), read(m), read(K);
	LL sum = 0;
	std::vector<int> vals;
	for(int i = 1; i <= n; i++) read(a[i]), vals.push_back(a[i]);
	for(int i = 1; i <= n; i++) read(b[i]), vals.push_back(b[i]);
	std::sort(vals.begin(), vals.end());
	vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
	for(int i = 1; i <= n; i++) {
		ta[std::lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin()].push_back(i), sum += a[i];
		tb[std::lower_bound(vals.begin(), vals.end(), b[i]) - vals.begin()].push_back(i), sum += b[i];
	}
	for(int i = 1; i <= m; i++) {
		int u, v;
		read(u), read(v);
		if(a[u] == b[v]) e[u][v] = true;
	}
	for(int t = 0; t < (int)vals.size(); t++) {
		int cn = ta[t].size() + tb[t].size();
		if(!cn) continue;
		for(int i = 1; i <= cn + 2; i++) head[i] = 0;
		ek = 2;
		for(int i = 0; i < (int)ta[t].size(); i++)
			for(int j = 0; j < (int)tb[t].size(); j++)
				if(e[ta[t][i]][tb[t][j]]) add_edge(i + 1, j + 1 + (int)ta[t].size(), 1);
		for(int i = 0; i < (int)ta[t].size(); i++) add_edge(cn + 1, i + 1, 1);
		for(int j = 0; j < (int)tb[t].size(); j++) add_edge(j + 1 + (int)ta[t].size(), cn + 2, 1);
		sum -= (LL)vals[t] * dinic(cn + 2, cn + 1, cn + 2);
	}
	// for(int u = 1; u <= 2 * n + 2; u++)
	// 	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i ^ 1].r) printf("%d -> %d (r=%lld, w=%lld)\n", u, edge[i].to, edge[i ^ 1].r, edge[i].w);
	write(sum, '\n');
	return 0;
}