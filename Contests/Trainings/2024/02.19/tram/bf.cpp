#include <bits/stdc++.h>

typedef std::pair<int, int> Pos;

const int N = 1000 + 5;
const int INF = 0x3f3f3f3f;

int n, m;

int a[N][2];
Pos pos[N];
std::vector<Pos> vct;
int dist(const Pos &x, const Pos &y) { return (x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second); }

int main() {
	scanf("%d%d", &n, &m);
	for(int qid = 1; qid <= m; qid++) {
		int t;
		scanf("%d", &t);
		if(t == 1) {
			Pos p{1, 0};
			int opt = 0;
			for(int i = 1; i <= n; i++) for(int j : {0, 1}) if(!a[i][j]) {
				int mn = INF;
				for(auto q : vct) mn = std::min(mn, dist(q, {i, j}));
				if(mn > opt) opt = mn, p = {i, j};
			}
			vct.emplace_back(p);
			printf("%d %d\n", p.first, p.second + 1);
			a[p.first][p.second] = 1;
			pos[qid] = p;
		} else {
			int x;
			scanf("%d", &x);
			Pos p = pos[x];
			vct.erase(std::find(vct.begin(), vct.end(), p));
			a[p.first][p.second] = 0;
		}
	}
	return 0;
}