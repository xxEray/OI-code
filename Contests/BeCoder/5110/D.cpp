#pragma GCC optimize(2)

#include <bits/stdc++.h>

const int N = 5e4 + 5;
const int M = 1e5 + 5;
const int D = 1e4;
const int MAXQ = 5e4 + 5;

int n, m, Q;
struct Edge { int to, nxt; } edge[M];
int head[N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }

std::bitset<D> bs[N], qe[M];
int st[MAXQ], ed[MAXQ], ql[MAXQ], qr[MAXQ];

int ind[N], indc[N];
void toposort() {
	for(int i = 1; i <= n; i++) ind[i] = indc[i];
	std::vector<int> vct;
	for(int i = 1; i <= n; i++) if(!ind[i]) vct.emplace_back(i);
	while(!vct.empty()) {
		int u = vct.back();
		vct.pop_back();
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			bs[v] |= bs[u] & qe[i];
			ind[v]--;
			if(!ind[v]) vct.emplace_back(v);
		}
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1;
		scanf("%d%d%d", &n, &m, &Q);
		for(int i = 1; i <= n; i++) head[i] = 0, indc[i] = 0;
		for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), indc[v]++; }
		for(int i = 1; i <= Q; i++) scanf("%d%d%d%d", &st[i], &ed[i], &ql[i], &qr[i]);
		for(int q = 1; q <= Q; q += D) {
			for(int i = 1; i <= n; i++) bs[i].reset();
			for(int i = 1; i <= m; i++) qe[i].reset();
			for(int i = q; i <= std::min(q + D - 1, Q); i++) bs[st[i]].set(i - q), qe[ql[i]].set(i - q), qe[qr[i] + 1].set(i - q);
			for(int i = 1; i <= m; i++) qe[i] ^= qe[i - 1];
			toposort();
			for(int i = q; i <= std::min(q + D - 1, Q); i++) puts(bs[ed[i]][i - q] ? "YES" : "NO");
		}
	}
	return 0;
} /*
1
5 6 5
1 2
1 3
3 4
2 4
2 5
3 5
3 5 1 5
3 5 1 6
1 4 1 6
1 4 2 3
1 4 4 5
*/