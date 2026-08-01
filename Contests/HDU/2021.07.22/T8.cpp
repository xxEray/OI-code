#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <vector>
#include <string>

const int N = 50 + 5;
const int M = 15000 + 5;
const int T = 500 + 5;
const int P = 3 + 2;
const int INF = 0x3f3f3f3f;

std::vector<std::pair<int, int>> cost[N]; // time, value
int n, m, t, p;

std::map<std::string, int> subject;
int f[N][T];
int g[N][P][T];

inline void updt(int &a, int b) { if(a < b) a = b; }

int main() {
	int Tcase;
	scanf("%d", &Tcase);
	while(Tcase--) {
		subject.clear();
		for(int i = 0; i < N; i++) cost[i].clear();
		memset(f, 0, sizeof(f));
		memset(g, -INF, sizeof(g));
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			char s[20];
			scanf("%s", s);
			if(subject.find(s) == subject.end()) subject[s] = i;
		}
		scanf("%d", &m);
		for(int i = 1; i <= m; i++) {
			char s[20]; int a, b;
			scanf("%s%d%d", s, &a, &b);
			cost[subject[s]].push_back({b, a});
		}
		scanf("%d%d", &t, &p);
		for(int i = 1; i <= n; i++)
			for(int j = 0; j < (int)cost[i].size(); j++)
				for(int k = t; k >= cost[i][j].first; k--)
					f[i][k] = std::min(std::max(f[i][k], f[i][k - cost[i][j].first] + cost[i][j].second), 100);
		g[0][0][0] = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j <= p; j++)
				for(int k = 0; k <= t; k++)
					for(int r = 0; r + k <= t; r++)
						updt(g[i + 1][j + (f[i + 1][r] < 60)][r + k], g[i][j][k] + f[i + 1][r]);
		// for(int i = 1; i <= p; i++)
		// 	for(int j = 0; j <= t; j++)
		// 		printf("f[%d][%d][%d] = %d\n",  n, i, j, g[n][i][j]);
		int ans = -1;
		for(int i = 0; i <= p; i++)
			for(int j = 0; j <= t; j++)
				ans = std::max(ans, g[n][i][j]);
		printf("%d\n", ans);
	}	
	return 0;
} /*
2
1
math
1
math 70 10
9 03
mathematics physics signals
20
physics 10 1
physics 10 1
physics 10 1
physics 10 1
physics 10 1
physics 10 1
physics 10 1
mathematics 10 1
mathematics 10 1
mathematics 10 1
mathematics 10 1
mathematics 10 1
mathematics 10 1
mathematics 10 1
signals 10 1
signals 10 1
signals 10 1
signals 10 1
signals 10 1
signals 10 2
19 1

*/