#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

typedef long long LL;

const int N = 1e7 + 5;
const int MAXN = 1e7;
const int INF = 0x3f3f3f3f;

int A, B;

int dis[N];
std::queue<int> q;
void bfs(int st) {
	dis[st] = 0;
	q.push(st);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		if((LL)u * A <= MAXN) {
			int v = u * A;
			if(dis[v] == INF) dis[v] = dis[u] + 1, q.push(v);
		}
		if(u > 10 && u % 10) {
			int r = u % 10, t = u / 10;
			while(t) t /= 10, r *= 10;
			t = u / 10 + r;
			if(t <= MAXN && dis[t] == INF) dis[t] = dis[u] + 1, q.push(t);
		}
	}
}

int main() {
	memset(dis, 0x3f, sizeof(dis));
	scanf("%d%d", &A, &B);
	bfs(1);
	printf("%d\n", dis[B] == INF ? -1 : dis[B]);
	return 0;
}