#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n;
int d[N];

int p[N];

int main() {
#ifndef DEBUG
	freopen("fire.in", "r", stdin);
	freopen("fire.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) d[i] = 0;
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); d[u]++, d[v]++; }
		std::vector<int> vx, vy;
		for(int i = 1; i <= n; i++)
			if(d[i] == 1) vx.emplace_back(i);
			else vy.emplace_back(i);
		if(vx.size() < vy.size()) puts("No");
		else {
			puts("Yes");
			for(int i = 1; i <= n; i++) p[i] = i;
			for(int i = 0; i < (int)vy.size(); i++) p[vy[i]] = vx[i], p[vx[i]] = vy[i];
			for(int i = 1; i <= n; i++) printf("%d ", p[i]);
			puts("");
		}
	}
	return 0;
}