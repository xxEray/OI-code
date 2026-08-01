#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>

const int N = 3e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

bool isprm[N];
int g[N];
std::vector<int> prime;
void sieve(int mx) {
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	for(int i = 2; i <= mx; i++) {
		if(isprm[i]) prime.push_back(i), g[i] = i;
		for(int p : prime) {
			if((long long)p * i > mx) break;
			isprm[p * i] = false;
			g[i * p] = p;
			if(i % p == 0) break;
		}
	}
}

int st, ed;
std::vector<std::pair<int, int>> to[N * 2];
bool vis[N * 2];
std::deque<int> q;
int dis[N * 2], last[N * 2];
void bfs() {
	for(int i = 1; i <= n + 300000; i++) dis[i] = INF;
	dis[st] = 0, vis[st] = true, q.push_back(st);
	while(!q.empty()) {
		int u = q.front();
		q.pop_front();
		for(auto &e : to[u]) {
			int v = e.first, w = e.second;
			if(vis[v]) continue;
			vis[v] = true, dis[v] = dis[u] + w;
			if(w) q.push_back(v);
			else q.push_front(v);
			last[v] = u;
		}
	}
}
void print(int u) {
	if(u == st) { printf("%d ", u); return; }
	print(last[last[u]]);
	printf("%d ", u);
}

int main() {
	sieve(3e5);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) {
		int x = a[i];
		while(x > 1) {
			int v = g[x];
			to[i].push_back({n + v, 1}), to[n + v].push_back({i, 0});
			while(x % v == 0) x /= v;
		}
	}
	scanf("%d%d", &st, &ed);
	bfs();
	if(dis[ed] >= INF) { puts("-1"); return 0; }
	printf("%d\n", dis[ed] + 1);
	print(ed);
	puts("");
	return 0;
}