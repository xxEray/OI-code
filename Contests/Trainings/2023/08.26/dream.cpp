#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
}
using FIO::read;

typedef long long LL;

const int N = 1e5 + 5;
const int M = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

int n, m, Q, K, Tid;
struct Edge { int to, nxt; LL w; } edge[M * 2];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

LL dis[N];
bool vis[N];
void bfs(int st) {
	std::priority_queue<std::pair<LL, int>, std::vector<std::pair<LL, int>>, std::greater<std::pair<LL, int>>> q;
	for(int i = 1; i <= n; i++) dis[i] = LLINF, vis[i] = false;
	dis[st] = 0, q.push({dis[st], st});
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(dis[v] > dis[u] + edge[i].w) {
				dis[v] = dis[u] + edge[i].w;
				q.push({dis[v], v});
			}
		}
	}
}

int f[3 * N];
int d[3 * N], nxt[N];

std::vector<int> vct;
std::vector<int> to[3 * N];

int main() {
#ifndef DEBUG
	freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);
#endif
	read(n), read(m), read(Q), read(K), read(Tid);
	for(int i = 1; i <= m; i++) {
		int u, v;
		LL w;
		read(u), read(v), read(w);
		if(u != v) add_edge(u, v, w), add_edge(v, u, w);
		else add_edge(u, v, w);
	}
	while(Q--) {
		int s, t;
		read(s), read(t);
		bfs(t);
		for(int i = 1; i <= n; i++) nxt[i] = -1;
		for(int u = 1; u <= n; u++)
			for(int i = head[u]; i; i = edge[i].nxt) {
				int v = edge[i].to;
				if(dis[u] == dis[v] + edge[i].w) {
					if(nxt[u] == -1) nxt[u] = i;
					else nxt[u] = -2;
				}
			}
		// for(int i = 1; i <= n; i++) if(nxt[i] != -1) printf("nxt[%d] = %d\n", i, nxt[i]);
		for(int i = 1; i <= (K ? 3 : 2) * n; i++) to[i].clear();
		for(int u = 1; u <= (K ? 3 : 2) * n; u++)
			if(u <= n) {
				for(int i = head[u]; i; i = edge[i].nxt) {
					int v = edge[i].to;
					if(dis[u] == dis[v] + edge[i].w && nxt[u] == i) to[u].push_back(v);
					else if(dis[u] == dis[v] + edge[i].w && nxt[u] == -2) to[u].push_back(v + n);
					if(i != nxt[u]) { if(K) to[u].push_back(v + 2 * n); }
				}
			} else if(u <= 2 * n) {
				for(int i = head[u - n]; i; i = edge[i].nxt) {
					int v = edge[i].to;
					if(dis[u - n] == dis[v] + edge[i].w) to[u].push_back(v + n);
					else { if(K) to[u].push_back(v + 2 * n); }
				}
			} else {
				for(int i = head[u - 2 * n]; i; i = edge[i].nxt) {
					int v = edge[i].to;
					if(dis[u - 2 * n] == dis[v] + edge[i].w) { if(K) to[u].push_back(v + 2 * n); }
				}
			}
		for(int i = 1; i <= (K ? 3 : 2) * n; i++) d[i] = 0;
		for(int u = 1; u <= (K ? 3 : 2) * n; u++) for(int v : to[u]) d[v]++;
		for(int i = 1; i <= (K ? 3 : 2) * n; i++) f[i] = 0;
		f[s] = 1;
		for(int i = 1; i <= (K ? 3 : 2) * n; i++) if(!d[i]) vct.push_back(i);
		while(!vct.empty()) {
			int u = vct.back();
			vct.pop_back();
			for(int v : to[u]) {
				assert(d[v]);
				d[v]--;
				if(!K || (v != t && v != t + n)) {
					// printf("f[%d] -> f[%d]\n", u, v);
					f[v] += f[u];
					if(f[v] >= MOD) f[v] -= MOD;
				}
				if(!d[v]) vct.push_back(v);
			};
		}
		// for(int i = 1; i <= (K ? 3 : 2) * n; i++) if(f[i]) printf("f[%d] = %d\n", i, f[i]);
		printf("%d\n", K ? f[t + 2 * n] : f[t] + f[t + n]);
	}
	return 0;
} /*
4 7 1 1 0
1 2 1
1 2 1
2 3 1
2 3 1
3 4 1
3 4 2
2 4 3
1 4

4 5 1 1 0
1 2 1
2 3 1
1 3 2
2 4 5
3 4 2
1 4
*/