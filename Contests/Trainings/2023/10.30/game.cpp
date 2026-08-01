// #pragma GCC optimize("Ofast", "inline", "-ffast-math")
// #pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <bits/stdc++.h>

const int D = 60;
const int N = 2e7 + D + 5;
const int INF = 0x3f3f3f3f;

int n, m;

bool vis[N];
uint8_t dis[N];
std::vector<int> q[D + 5];
int w;

const int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59/* , 61, 67, 71, 73, 79, 83, 89, 97 */};

const int MAX_SIZE[] = {
  1,       1,       1,       1,       1,       2,      2,      3,       4,       5,
  10,      11,      15,      25,      31,      46,     60,     86,      115,     157,
  222,     305,     414,     579,     800,     1091,   1505,   2079,    2846,    3927,
  5412,    7440,    10267,   14122,   19441,   26837,  36930,  50864,   70238,   96761,
  133147,  183746,  253143,  348826,  481116,  662934, 913825, 1260282, 1736263, 2387389,
  3223600, 4031600, 4103401, 2918739, 1466347, 810509, 658288, 542620,  426999,  387894,
  405220,
};

int main() {
// #ifndef DEBUG
// 	freopen("game.in", "r", stdin);
// 	freopen("game.out", "w", stdout);
// #endif
	freopen("game.in", "r", stdin);
	freopen("std.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 0; i <= D; i++) q[i].reserve(MAX_SIZE[i]);
	m = n + D;
	memset(dis, 0x7f, m + 1);
	dis[1] = 0;
	q[dis[1]].push_back(1);
	while(true) {
		while(w <= D && q[w].empty()) w++;
		if(w > D) break;
		auto u = q[w].back();
		q[w].pop_back();
		if(vis[u]) continue;
		vis[u] = true;
		for(auto p : prime) {
			if(w + p > D || u * p > m) break;
			auto v = u * p;
			if(dis[v] > w + p) {
				dis[v] = w + p;
				q[w + p].push_back(v);
			}
		}
		if(dis[u - 1] > w + 1) {
			dis[u - 1] = w + 1;
			q[w + 1].push_back(u - 1);
		}
	}
	for(int i = 1; i <= n; i++) printf("%d\n", (int)dis[i]);
	return 0;
}