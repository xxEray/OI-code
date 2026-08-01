#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long LL;

const int N = 20 + 5;
const int M = 100 + 5;
const int S = (1 << 20) + 5;
const int INF = 0x3f3f3f3f;

int a[N];
int b1[M], b2[M], f1[M], f2[M];
int n, m;

int dis[S], inq[S];
std::queue<int> q;
void bfs(int st) {
	for(int i = 0; i < (1 << n); i++) dis[i] = INF;
	dis[st] = 0, q.push(st), inq[st] = true;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(int i = 1; i <= m; i++)
			if(((u & b1[i]) == b1[i]) && ((u & b2[i]) == 0)) {
				int v = (u & ~f1[i]) | f2[i];
				if(dis[v] <= dis[u] + a[i]) continue;
				dis[v] = dis[u] + a[i];
				if(!inq[v]) q.push(v), inq[v] = true;
			}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		scanf("%d", &a[i]);
		for(int j = 0; j < n; j++) {
			char s[2]; scanf("%1s", s);
			if(s[0] == '+') b1[i] |= 1 << j;
			if(s[0] == '-') b2[i] |= 1 << j;
		}
		for(int j = 0; j < n; j++) {
			char s[2]; scanf("%1s", s);
			if(s[0] == '-') f1[i] |= 1 << j;
			if(s[0] == '+') f2[i] |= 1 << j;
		}
	}
	bfs((1 << n) - 1);
	printf("%d\n", dis[0] == INF ? 0 : dis[0]);
	return 0;
}