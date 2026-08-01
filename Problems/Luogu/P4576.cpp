#include <bits/stdc++.h>

const int N = 20 + 3;
const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int n;
int sr1, sc1, sr2, sc2;

int hash(int r1, int c1, int r2, int c2, int first) { return first * 160000 + (r1 - 1) * 8000 + (c1 - 1) * 400 + (r2 - 1) * 20 + c2; }

std::vector<int> from[N * N * N * N * 2];
int ind[N * N * N * N * 2];
int f[N * N * N * N * 2], g[N * N * N * N * 2];

bool check(int x) { return 1 <= x && x <= n; }

int main() {
	scanf("%d%d%d%d%d", &n, &sr1, &sc1, &sr2, &sc2);
	for(int r1 = 1; r1 <= n; r1++) for(int c1 = 1; c1 <= n; c1++)
		for(int r2 = 1; r2 <= n; r2++) for(int c2 = 1; c2 <= n; c2++) if(std::make_pair(r1, c1) != std::make_pair(r2, c2)) {
			for(int d = 0; d < 4; d++) {
				int nr1 = r1 + dir[d][0], nc1 = c1 + dir[d][1];
				if(check(nr1) && check(nc1)) from[hash(nr1, nc1, r2, c2, 1)].emplace_back(hash(r1, c1, r2, c2, 0));
			}
			for(int d = 0; d < 4; d++) {
				int nr2 = r2 + dir[d][0], nc2 = c2 + dir[d][1];
				if(check(nr2) && check(nc2)) from[hash(r1, c1, nr2, nc2, 0)].emplace_back(hash(r1, c1, r2, c2, 1));
				nr2 = r2 + 2 * dir[d][0], nc2 = c2 + 2 * dir[d][1];
				if(check(nr2) && check(nc2)) from[hash(r1, c1, nr2, nc2, 0)].emplace_back(hash(r1, c1, r2, c2, 1));
			}
		}
	for(int r1 = 1; r1 <= n; r1++) for(int c1 = 1; c1 <= n; c1++)
		for(int r2 = 1; r2 <= n; r2++) for(int c2 = 1; c2 <= n; c2++) if(std::make_pair(r1, c1) != std::make_pair(r2, c2))
			for(int k : {0, 1}) {
				int u = hash(r1, c1, r2, c2, k);
				for(int v : from[u]) ind[v]++;
			}
	std::queue<int> q;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) {
		f[hash(i, j, i, j, 0)] = 1, f[hash(i, j, i, j, 1)] = 1;
		g[hash(i, j, i, j, 0)] = 0, g[hash(i, j, i, j, 1)] = 0;
		q.push(hash(i, j, i, j, 0)), q.push(hash(i, j, i, j, 1));
	}
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : from[u]) if(!f[v]) {
			ind[v]--;
			if(!g[u] || !ind[v]) f[v] = f[u] + 1, g[v] = g[u] ^ 1, q.push(v);
		}
	}
	int dst = hash(sr1, sc1, sr2, sc2, 0);
	if(!f[dst]) puts("DRAW");
	else printf("%s %d\n", g[dst] ? "WHITE" : "BLACK", f[dst] - 1);
	return 0;
}