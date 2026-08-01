#include <cstdio>
#include <algorithm>
#include <set>

const int N = 3e5 + 5;

int n, m;
std::set<std::pair<int, int>> e;

int prv[N], nxt[N];

int edge(int u, int v) { return !u || !v ? -1 : e.count({u, v}); }

int main() {
	scanf("%d%d", &n, &m);
	if(n == 1) { puts("1"); return 0; }
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); e.insert({u, v}), e.insert({v, u}); }
	int now = 2;
	nxt[1] = 2, prv[2] = 1;
	while(now < n && edge(now - 1, now) == edge(now, now + 1)) nxt[now] = now + 1, prv[now + 1] = now, now++;
	for(int i = now + 1; i <= n; i++) {
		if(edge(now, i) == edge(prv[now], now)) {
			prv[nxt[now]] = i, nxt[i] = nxt[now], prv[i] = now, nxt[now] = i;
			prv[0] = nxt[0] = 0;
			now = nxt[now];
			if(edge(prv[now], now) == edge(now, nxt[now])) now = nxt[now];
		} else {
			nxt[prv[now]] = i, prv[i] = prv[now], nxt[i] = now, prv[now] = i;
			prv[0] = nxt[0] = 0;
			now = prv[now];
			if(edge(prv[now], now) == edge(now, nxt[now])) now = prv[now];
		}
		if(now == 1) while(nxt[now]) now = nxt[now];
		// printf("now = %d: ", now);
		// int t = now;
		// while(prv[t]) t = prv[t];
		// while(t) printf("%d ", t), t = nxt[t];
		// puts("");
	}
	while(prv[now]) now = prv[now];
	while(now) printf("%d ", now), now = nxt[now];
	return 0;
}