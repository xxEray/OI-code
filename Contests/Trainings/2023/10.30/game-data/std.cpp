#include <bits/stdc++.h>

const int D = 75;
const int N = 2e7 + D + 5;
const int INF = 0x3f3f3f3f;

int n, m;

bool vis[N];
unsigned char dis[N];
std::vector<int> q[D + 5];
int w;

const int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73/* , 79, 83, 89, 97 */};

int main() {
	scanf("%d", &n);
	m = n + D;
	memset(dis, 0x3f, sizeof(dis));
	dis[1] = 0;
	q[dis[1]].push_back(1), w = 0;
	while(true) {
		while(w <= D && q[w].empty()) w++;
		if(w > D) break;
		int u = q[w].back();
		q[w].pop_back();
		if(vis[u]) continue;
		vis[u] = true;
		for(int p : prime) {
			int v = u * p;
			if(v > m) break;
			if(dis[v] > dis[u] + p) {
				dis[v] = dis[u] + p;
				if(dis[v] <= D) q[dis[v]].push_back(v);
			}
		}
		if(dis[u - 1] > dis[u] + 1) {
			dis[u - 1] = dis[u] + 1;
			if(dis[u - 1] <= D) q[dis[u - 1]].push_back(u - 1);
		}
	}
	printf("%d\n", (int)dis[n]);
	return 0;
}